from flask_admin.contrib.sqla import ModelView
from server_warehouse import db

class Article(db.Model):
    __tablename__ = 'article'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(250), unique=False, nullable=False)
    price = db.Column(db.Float, nullable=False)
    stock_size = db.Column(db.Integer, nullable=False)

    def __repr__(self):
        return '<Article id:{} name:{} price:{} stock_size:{}>'.format(self.id, self.name, self.price, stock_size)

    def to_json(self):
        return {
            "id": self.id,
            "name": self.name,
            "price": self.price,
            "stock_size": self.stock_size,
        }

class ArticleAdmin(ModelView):
    form_columns = ['name', 'price', 'stock_size']

    def __init__(self, session, **kwargs):
        super(ArticleAdmin, self).__init__(Article, session, **kwargs)
