//
// Created by grosso_a on 02/01/19.
//

//
// Created by grosso_a on 26/12/18.
//
#include <Network/Request/Article.hpp>

namespace cash
{
    namespace network
    {
        Article::Article(const QJsonObject &object)
        {
            this->_id = object.value(QString("id")).toInt();
            this->_name = object.value(QString("name")).toString().toStdString();
            this->_price = object.value(QString("price")).toDouble();
            this->_stock_size = object.value(QString("stock_size")).toInt();
        }

        int Article::id()
        {
            return _id;
        }

        const std::string &Article::name()
        {
            return _name;
        }

        double Article::price()
        {
            return _price;
        }

        int Article::stock_size()
        {
            return _stock_size;
        }
    }
}
