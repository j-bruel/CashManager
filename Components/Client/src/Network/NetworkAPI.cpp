//
// Created by grosso_a on 02/01/19.
//
#include <Network/NetworkAPI.hpp>

namespace cash
{
    namespace network
    {
        NetworkAPI::NetworkAPI(std::string url, unsigned int port) {
            this->_url = std::move(url);
            this->_port = port;
        }


        NetworkAPI::~NetworkAPI() {
            while (!_requests.empty()) {
                std::tuple<ARequest *, QNetworkAccessManager*> elem = _requests.back();
                delete std::get<0>(elem);
                delete std::get<1>(elem);
                _requests.pop_back();
            }
        }

        const std::string &NetworkAPI::url()
        {
            return this->_url;
        }

        unsigned int NetworkAPI::port()
        {
            return this->_port;
        }

        void NetworkAPI::get(ARequest* req) {
            RequestParameters           &parameters = req->parameters();
            RequestParameters::iterator it;
            QUrl                        url;
            QUrlQuery                   query;
            QNetworkAccessManager       *manager = new QNetworkAccessManager(this);

            req->reset();
            url.setUrl(this->_url.c_str());
            url.setPort(this->_port);
            url.setPath(req->path().c_str());
            for (it = parameters.begin(); it != parameters.end(); it++)
            {
                query.addQueryItem(QString::fromStdString(it->first), QString::fromStdString(it->second));
            }
            url.setQuery(query.query());
            manager->get(QNetworkRequest(url));
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "NetworkRequest get " << url.toString().toStdString() << " " << req;
            connect(manager, SIGNAL(finished(QNetworkReply *)), req, SLOT(onResult(QNetworkReply *)));
            this->_requests.push_back(std::tuple<ARequest *, QNetworkAccessManager*>(req, manager));
        }
    }
}
