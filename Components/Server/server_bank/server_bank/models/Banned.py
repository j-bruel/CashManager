from flask_admin.contrib.sqla import ModelView
from server_bank import db

class Banned(db.Model):
    __tablename__ = 'banned'
    id = db.Column(db.Integer, primary_key=True)
    account = db.Column(db.String(20), unique=True, nullable=False)

    def __repr__(self):
        return '<Ban id:{} account:{}>'.format(self.id, self.account)

class BannedAdmin(ModelView):
    form_columns = ['account']

    def __init__(self, session, **kwargs):
        super(BannedAdmin, self).__init__(Banned, session, **kwargs)
