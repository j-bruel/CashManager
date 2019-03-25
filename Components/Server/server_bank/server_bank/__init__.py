import time
import atexit

from pytz import utc
from flask import Flask
from flask_restful import Api
from flask_sqlalchemy import SQLAlchemy
from flask_admin import Admin
from apscheduler.schedulers.background import BackgroundScheduler
from datetime import datetime, timedelta

app = Flask(__name__)

DBUSER = 'cashmanager'
DBPASS = 'cashmanager'
DBNAME = 'cashmanager'
DBHOST = 'postgres'
DBPORT = '5432'

app.config['SQLALCHEMY_DATABASE_URI'] = \
        'postgresql+psycopg2://{user}:{passwd}@{host}:{port}/{db}'.format(
        user=DBUSER,
        passwd=DBPASS,
        host=DBHOST,
        port=DBPORT,
        db=DBNAME)
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
app.config['FLASK_ADMIN_SWATCH'] = 'cerulean'
app.secret_key = 'cashmanager_bank'


db = SQLAlchemy(app)
api = Api(app)
admin = Admin(app, name=__name__, template_mode='bootstrap3')

@app.route("/clear_data")
def clear():
    db.drop_all()
    db.create_all()
    db.session.add(models.Banned.Banned(account="0000000000000000"))
    db.session.add(models.Banned.Banned(account="00000000AAA"))
    db.session.commit()
    return "Database clear !"

from server_bank import views
from server_bank import models

api.add_resource(views.PaymentToken, '/token')
api.add_resource(views.CheckPayment, '/payment/check')
api.add_resource(views.CardPayment, '/payment/card')
api.add_resource(views.CardPaymentContactless, '/payment/contactless')

admin.add_view(models.BannedAdmin(db.session))
admin.add_view(models.TransactionTokenAdmin(db.session))
admin.add_view(models.TransactionAdmin(db.session))

db.create_all()
clear()


def invalidate_token():
    query = models.TransactionToken.TransactionToken.query.filter(models.TransactionToken.TransactionToken.free == True).filter(models.TransactionToken.TransactionToken.expire < datetime.now())
    for token in query.all():
        token.free = False
    db.session.commit()


scheduler = BackgroundScheduler(timezone=utc)
scheduler.add_job(func=invalidate_token, trigger="interval", seconds=3)
scheduler.start()
# Shut down the scheduler when exiting the app
atexit.register(lambda: scheduler.shutdown())
