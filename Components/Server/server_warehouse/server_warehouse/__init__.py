import time
import atexit

from pytz import utc
from flask import Flask
from flask_restful import Api
from flask_sqlalchemy import SQLAlchemy
from flask_admin import Admin

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
app.secret_key = 'cashmanager_warehouse'


db = SQLAlchemy(app)
api = Api(app)
admin = Admin(app, name=__name__, template_mode='bootstrap3')

@app.route("/clear_data")
def clear():
    db.drop_all()
    db.create_all()
    db.session.add(models.Article(name="Apple iPad Pro 11\" Wi-Fi 256 Go", price=1211.94, stock_size=100))
    db.session.add(models.Article(name="Apple Watch Series 2 Noir", price=395.0, stock_size=100))
    db.session.add(models.Article(name="iMac 27'; A1312 922-9223 Nappe Sensor", price=17.0, stock_size=100))
    db.session.add(models.Article(name="CD-R 700 Mo - 10 (10CDQ80SS)", price=11.96, stock_size=100))
    db.session.add(models.Article(name="Apple iPad Air 16Go", price=199.0, stock_size=100))
    db.session.add(models.Article(name="iPod touch 6G - 64 Go", price=302.02, stock_size=100))
    db.session.add(models.Article(name="iPod touch 6G - 32 Go", price=261.52, stock_size=100))
    db.session.add(models.Article(name="Storeva Xslim 1 To USB 3.0", price=59.21, stock_size=100))
    db.session.add(models.Article(name="PNY Hook 3.0 16 Go - USB 3.0", price=14.99, stock_size=100))
    db.session.add(models.Article(name="Sandisk Ultra USB 3.0 - USB 16 Go", price=8.71, stock_size=100))
    db.session.add(models.Article(name="iProtector Silicone protector Hard Disk 3.5\" smoke", price=9.99, stock_size=100))
    db.session.add(models.Article(name="Storage structure for Storeva HDD Box", price=4.99, stock_size=100))
    db.session.add(models.Article(name="Novodio Imitation Leather Case for 2.5\" External Hard Disk Drive", price=4.99, stock_size=100))
    db.session.add(models.Article(name="LOGIC CASE - Case for external hard disk 2.5 - Semi rigid black", price=14.73, stock_size=100))
    db.session.add(models.Article(name="TrendNet TK-209K White 2-Port KVM Switch - USB + Audio", price=25.99, stock_size=100))
    db.session.add(models.Article(name="Apple MagSafe-Adapter 85 watts for MacBook Pro 15\"/17\"", price=89.0, stock_size=100))
    db.session.add(models.Article(name="Novodio C-Charge Pro - Charger iPhone & Macbook Pro USB-C, 4x USB-A QC 3.0 80 W", price=39.99, stock_size=100))
    db.session.add(models.Article(name="Novodio USB-C Charger - Charger MacBook USB-C 29 W", price=14.99, stock_size=100))
    db.session.add(models.Article(name="Novodio C-Charge Pro 100 - Charger MacBook Pro USB-C 100 W", price=49.99, stock_size=100))
    db.session.add(models.Article(name="Novodio C-Charge 45 - Charger MacBook Pro USB-C 45 W", price=29.99, stock_size=100))
    db.session.add(models.Article(name="Power Supply Apple iMac 21&#34; A1418 - 661-7111 2012/2013/2014", price=129.0, stock_size=100))
    db.session.add(models.Article(name="Allocacoc PowerCube Original USB - Bloc Multiprise Compact (4 Prises + 2 USB)", price=14.99, stock_size=100))
    db.session.add(models.Article(name="Dual white USB mains charger for Ipad, Iphone, Ipod", price=9.99, stock_size=100))
    db.session.add(models.Article(name="Universal wireless charging station Qi induction phone charger white black", price=12.89, stock_size=100))
    db.session.add(models.Article(name="Lightning MD819ZM to USB 2m cable - white", price=21.28, stock_size=100))
    db.session.add(models.Article(name="Li-Ion 4800mAh (7.3V) Li-Ion Battery for notebook, Apple MacBook Air 11&#34;", price=72.28, stock_size=100))
    db.session.add(models.Article(name="RJ45 Ethernet cable category 6 grey shielded (1 m)", price=3.9, stock_size=100))
    db.session.add(models.Article(name="RJ45 Ethernet cable category 6 grey shielded (20 m)", price=14.53, stock_size=100))
    db.session.add(models.Article(name="LMP USB-C to HDMI 2.0 4K cable @ 60Hz 1.8 m black", price=24.99, stock_size=100))
    db.session.add(models.Article(name="HDMI cable 2.0 4K @ 60Hz 1m Male / Male", price=4.99, stock_size=100))
    db.session.add(models.Article(name="5W AC Adapter - Apple", price=17.99, stock_size=100))
    db.session.commit()
    return "Database clear !"

from server_warehouse import views
from server_warehouse import models

api.add_resource(views.ArticleList, '/list')
api.add_resource(views.Scan, '/scan')

admin.add_view(models.ArticleAdmin(db.session))

db.create_all()
clear()
