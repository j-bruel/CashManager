from flask_admin.contrib.sqla import ModelView
from server_bank import db
from datetime import datetime

class Transaction(db.Model):
    __tablename__ = 'transaction'
    id = db.Column(db.Integer, primary_key=True)
    type = db.Column(db.String(20), unique=False, nullable=False)
    date = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
    account = db.Column(db.String(20), unique=False, nullable=False)
    transactiontoken_id = db.Column(db.Integer, db.ForeignKey('transactiontoken.id'), nullable=False)
    transactiontoken = db.relationship("TransactionToken", backref=db.backref("transaction", uselist=False))
    amount = db.Column(db.Float, nullable=False)

    def __repr__(self):
        return '<Account id:{} name:{}>'.format(self.id, self.name_holder)


class TransactionAdmin(ModelView):
    form_columns = ['type', 'account', 'date', 'amount', 'transactiontoken']
    can_create = False
    can_edit = False

    def __init__(self, session, **kwargs):
        super(TransactionAdmin, self).__init__(Transaction, session, **kwargs)
