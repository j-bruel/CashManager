from flask_restful import Resource, reqparse
from server_warehouse.models.Article import Article
from server_warehouse import db

class ArticleList(Resource):
    def get(self):
        articles = Article.query.filter(Article.stock_size > 0).all()
        return {
            "articles": [article.to_json() for article in articles],
        }


class Scan(Resource):
    def get(self):
        parser = reqparse.RequestParser(bundle_errors=True)
        parser.add_argument('id', type=int, required=False, help="Missing: ")
        parser.add_argument('name', type=str, required=False, help="Missing: ")
        args = parser.parse_args()
        if args['id'] is not None:
            article = Article.query.filter(Article.id == args['id']).first()
            if article is None:
                return {"error": "Wrong article id"}
        elif args['name'] is not None:
            article = Article.query.filter(Article.name == args['name']).first()
            if article is None:
                return {"error": "Wrong article name"}
        else:
            return {"error": "'name' or 'id' request parameter missing !"}
        if article.stock_size <= 0:
            return {"error": "Article stock is empty"}
        article.stock_size -= 1
        db.session.commit()
        return article.to_json()
