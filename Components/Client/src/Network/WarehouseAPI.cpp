//
// Created by grosso_a on 16/12/18.
//
#include <Network/WarehouseAPI.hpp>
#include <Network/Request/RequestFactory.hpp>
#include <chrono>

namespace cash
{
    namespace network
    {
        cash::network::ArticleList *WarehouseAPI::articles()
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "ARTICLE_LIST";
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::ARTICLE_LIST);
            this->get(req);
            req->wait();
            return dynamic_cast<cash::network::ArticleList*>(req);
        }

        cash::network::ArticleScan *WarehouseAPI::scan(const std::string &id, const std::string &name)
        {
            LOG_(cash::tool::log::IN_FILE_AND_CONSOLE, plog::info) << "ARTICLE_SCAN";
            cash::network::ARequest *req = RequestFactory::build_request(RequestID::ARTICLE_SCAN);
            req->set_parameter("id", id);
            req->set_parameter("name", name);
            this->get(req);
            req->wait();
            return dynamic_cast<cash::network::ArticleScan*>(req);
        }
    }
}
