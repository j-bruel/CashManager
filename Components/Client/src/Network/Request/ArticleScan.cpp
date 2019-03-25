//
// Created by grosso_a on 02/01/19.
//
#include <Network/Request/ArticleScan.hpp>

namespace cash
{
    namespace network
    {
        bool ArticleScan::deserialize(std::shared_ptr<QJsonDocument> json) {
            QJsonObject obj = json->object();
            if (obj.value(QString("error")).isNull()) {
                this->set_error(obj.value(QString("error")).toString().toStdString(),
                                obj.value(QString("error_code")).toInt(0));
                return false;
            }
            this->_article = new Article(obj);
            return true;
        }

        ArticleScan::ArticleScan(): cash::network::ARequest("/scan") {}

        Article *ArticleScan::article()
        {
            return _article;
        }

        ArticleScan::~ArticleScan() {};
    }
}
