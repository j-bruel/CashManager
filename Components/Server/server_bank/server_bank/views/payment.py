from flask_restful import Resource, reqparse
from server_bank.models.TransactionToken import TransactionToken, get_token
from server_bank.models.Banned import Banned
from server_bank.models.Transaction import Transaction
from server_bank import db
from datetime import datetime, timedelta
import hashlib

ERRORS = {
    'CARD_BANNED': 101,
    'CHECK_BANNED': 102,
    'PIN': 103,
    'CARD_NUMBER': 104,
    'CHECK_NUMBER': 105,
    'AMOUNT': 106,
    'TOKEN': 107,
    'MAX_TRY': 108,
}

BANNED_PIN = [
    '1234',
    '0000',
    '1111',
    '2222',
    '3333',
    '4444',
    '5555',
    '6666',
    '7777',
    '8888',
    '9999',
]

ARGUMENTS = {
    'token': dict(type=str, required=True, help="Missing: token"),
    'card_type': dict(choices=('VISA', 'MASTER', 'ELECTRON'), required=True, help="Missing: card_type (VISA, MASTER, ELECTRON)"),
    'card_number': dict(type=str, required=True, help="Missing: card_number"),
    'check_number': dict(type=str, required=True, help="Missing: check_number"),
    'pin': dict(type=str, required=True, help="Missing: pin"),
    'amount': dict(type=float, required=True, help="Missing: amount"),
    'try_count': dict(type=int, required=True, help="Missing: try_count"),
    'type': dict(choices=('CARD', 'CHECK', 'CONTACTLESS'), required=True),
}


class PaymentToken(Resource):
    def get(self):
        parser = reqparse.RequestParser(bundle_errors=True)
        parser.add_argument('type', choices=('CARD', 'CHECK', 'CONTACTLESS'), required=True)
        parser.add_argument('try_count', type=int, required=True, help="Missing: try_count")
        args = parser.parse_args()
        token = TransactionToken(
            type=args['type'],
            token=get_token(),
            created=datetime.now(),
            expire=datetime.now() + timedelta(seconds=180),
            free=True,
            try_count=args['try_count'])
        db.session.add(token)
        db.session.commit()
        return token.to_json()


def card_payment_limit(card_type, payment_type):
    return {
        'VISA': {'CARD': 2500.0, 'CONTACTLESS': 30.0},
        'MASTER': {'CARD': 3000.0, 'CONTACTLESS': 30.0},
        'ELECTRON': {'CARD': 1700.0, 'CONTACTLESS': 30.0},
    }.get(card_type, {'CARD': 1700.0, 'CONTACTLESS': 30.0}).get(payment_type, 30.0)


def parser_arguments(arguments):
    parser = reqparse.RequestParser(bundle_errors=True)
    for argument in arguments:
        parser.add_argument(argument, **(ARGUMENTS[argument]))
    args = parser.parse_args()
    return args


class CardPayment(Resource):
    def get(self):
        args = parser_arguments(['token', 'card_type', 'card_number', 'pin', 'amount'])
        token = TransactionToken.query.filter(TransactionToken.token == args['token']).filter(TransactionToken.type == 'CARD').filter(TransactionToken.free == True).first()
        if token is None:
            return {'error': 'Wrong token', 'error_code': ERRORS['TOKEN']}
        if token.try_count == 0:
            return {'error': 'Max try', 'error_code': ERRORS['MAX_TRY']}
        if token.try_count > 0:
            token.try_count -= 1
            db.session.commit()
        if not args['card_number'].isnumeric() or len(args['card_number']) != 16:
            return {'error': 'Invalid card_number 0000000000000000', 'error_code': ERRORS['CARD_NUMBER']}
        banned = Banned.query.filter(Banned.account == args['card_number']).first()
        if banned is not None:
            return {'error': 'Card banned', 'error_code': ERRORS['CARD_BANNED']}
        if not args['pin'].isnumeric() or len(args['pin']) != 4 or args['pin'] in BANNED_PIN:
            return {'error': 'Invalid pin', 'error_code': ERRORS['PIN']}
        if float(args['amount']) > card_payment_limit(args['card_type'], 'CARD'):
            return {'error': 'Card max amount {}'.format(card_payment_limit(args['card_type'], 'CARD')), 'error_code': ERRORS['AMOUNT']}
        transaction = Transaction(type='CARD', account=args['card_number'], transactiontoken=token, amount=args['amount'])
        db.session.add(transaction)
        token.free = False
        db.session.commit()
        return {
            'type': 'CARD',
            'token': args['token'],
            'card_type': args['card_type'],
            'card_number': args['card_number'],
            'transaction': transaction.id,
            'amount': args['amount']
        }


class CardPaymentContactless(Resource):
    def get(self):
        args = parser_arguments(['token', 'card_type', 'card_number', 'amount'])
        token = TransactionToken.query.filter(TransactionToken.token == args['token']).filter(TransactionToken.type == 'CONTACTLESS').filter(TransactionToken.free == True).first()
        if token is None:
            return {'error': 'Wrong token', 'error_code': ERRORS['TOKEN']}
        if token.try_count == 0:
            return {'error': 'Max try', 'error_code': ERRORS['MAX_TRY']}
        if token.try_count > 0:
            token.try_count -= 1
            db.session.commit()
        if not args['card_number'].isnumeric() or len(args['card_number']) != 16:
            return {'error': 'Invalid card_number 0000000000000000', 'error_code': ERRORS['CARD_NUMBER']}
        banned = Banned.query.filter(Banned.account == args['card_number']).first()
        if banned is not None:
            return {'error': 'Card banned', 'error_code': ERRORS['CARD_BANNED']}
        if float(args['amount']) > card_payment_limit(args['card_type'], 'CONTACTLESS'):
            return {'error': 'Contactless max amount {}'.format(card_payment_limit(args['card_type'], 'CONTACTLESS')), 'error_code': ERRORS['AMOUNT']}
        transaction = Transaction(type='CONTACTLESS', account=args['card_number'], transactiontoken=token, amount=args['amount'])
        db.session.add(transaction)
        token.free = False
        db.session.commit()
        return {
            'type': 'CONTACTLESS',
            'token': args['token'],
            'card_type': args['card_type'],
            'card_number': args['card_number'],
            'transaction': transaction.id,
            'amount': args['amount']
        }


class CheckPayment(Resource):
    def get(self):
        args = parser_arguments(['token', 'check_number', 'amount'])
        token = TransactionToken.query.filter(TransactionToken.token == args['token']).filter(TransactionToken.type == 'CHECK').filter(TransactionToken.free == True).first()
        if token is None:
            return {'error': 'Wrong token', 'error_code': ERRORS['TOKEN']}
        if token.try_count == 0:
            return {'error': 'Max try', 'error_code': ERRORS['MAX_TRY']}
        if token.try_count > 0:
            token.try_count -= 1
            db.session.commit()
        if len(args['check_number']) != 11:
            return {'error': 'Invalid check_number', 'error_code': ERRORS['CHECK_NUMBER']}
        banned = Banned.query.filter(Banned.account == args['check_number']).first()
        if banned is not None:
            return {'error': 'Check banned', 'error_code': ERRORS['CHECK_BANNED']}
        transaction = Transaction(type='CHECK', account=args['check_number'], transactiontoken=token, amount=args['amount'])
        db.session.add(transaction)
        token.free = False
        db.session.commit()
        return {
            'type': 'CHECK',
            'token': args['token'],
            'check_number': args['check_number'],
            'transaction': transaction.id,
            'amount': args['amount']
        }
