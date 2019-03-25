//
// Created by grosso_a on 02/01/19.
//
#include <Network/Request/ArticleList.hpp>

namespace cash
{
    namespace network
    {
        bool ArticleList::deserialize(std::shared_ptr<QJsonDocument> json)
        {
            QJsonObject obj = json->object();
            if (obj.value(QString("error")).isNull()) {
                this->set_error(obj.value(QString("error")).toString().toStdString(),
                                obj.value(QString("error_code")).toInt(0));
                return false;
            }
            QJsonArray articles = obj.value(QString("articles")).toArray();
            for (QJsonValue article : articles) {
                this->_articles.push_back(new Article(article.toObject()));
            }
            return true;
        }

        ArticleList::ArticleList(): cash::network::ARequest("/list")
        {
        }

        std::list<Article*>  &ArticleList::articles()
        {
            return _articles;
        }

        ArticleList::~ArticleList()
        {
        };
    }
}
