from flask_admin.contrib.sqla import ModelView
from sqlalchemy.sql import func
from server_bank import db
import uuid


def get_token():
    return uuid.uuid4().hex

class TransactionToken(db.Model):
    __tablename__ = 'transactiontoken'
    id = db.Column(db.Integer, primary_key=True)
    type = db.Column(db.String(20), unique=False, nullable=False)
    token = db.Column(db.String(32), unique=True, nullable=False)
    created = db.Column(db.DateTime(timezone=True), nullable=False)
    expire = db.Column(db.DateTime(timezone=True), nullable=False)
    try_count = db.Column(db.Integer, nullable=False)
    free = db.Column(db.Boolean, default=True)

    def __repr__(self):
        return '<TransactionToken id:{} type:{}, created:{} expire:{} try:{}>'.format(self.id, self.type,
            self.created.strftime("%Y-%m-%dT%H:%M:%S"), self.expire.strftime("%Y-%m-%dT%H:%M:%S"), self.try_count)

    def to_json(self):
        return {
            'token': self.token,
            'created': self.created.strftime("%Y-%m-%dT%H:%M:%S"),
            'expire': self.expire.strftime("%Y-%m-%dT%H:%M:%S"),
            'type': self.type,
            'try_count': self.try_count,
        }


class TransactionTokenAdmin(ModelView):
    form_columns = ['type', 'created', 'expire', 'free', 'try_count']
    can_create = False
    can_edit = False
    can_delete = False

    def __init__(self, session, **kwargs):
        super(TransactionTokenAdmin, self).__init__(TransactionToken, session, **kwargs)
