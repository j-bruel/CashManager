//!
//! @file ArticleGenerator.cpp
//! @author jbruel
//! @date 25/12/18
//!

#include "Core/ArticleGenerator.hpp"
#include <random>

namespace cash
{
namespace core
{

    QString ArticleGenerator::generate(double &articlePrice)
    {
        network::ArticleList            *articleList = mDBAPI.articles();
        std::list<network::Article *>   articles = articleList->articles();
        size_t                          articleNb = articles.size();
        size_t                          articleIdx = 0;
        std::string                     quantity("1    ");
        std::string                     name;
        std::string                     price;
        std::stringstream               stream;

        if ((articleIdx = generateRandomNumber(articleNb)) >= articleNb)
        {
            name = "USB Cable";
            price = "10€";
            articlePrice = 10;
            return ((quantity + price + "    " + name).c_str());
        }

        std::list<network::Article *>::iterator it = articles.begin();

        std::advance(it, articleIdx);
        name = (*it)->name();
        articlePrice = (*it)->price();
        stream << std::fixed << std::setprecision(2) << (*it)->price();

        std::string     priceValue = stream.str();

        price = std::string(priceValue.replace(priceValue.find_first_of('.'), 1, ",") + "€");
        return ((quantity + price + "    " + name).c_str());
    }

    size_t  ArticleGenerator::generateRandomNumber(size_t max) const
    {
        std::random_device seeder;

        std::mt19937 engine(seeder());
        std::uniform_int_distribution<int> dist(0, max);
        return (dist(engine));
    }

/*    void    ArticleGenerator::addSpacesToArticleName(const std::string &quantity, std::string &article, const std::string &price) const
    {
        size_t  articleSize = ArticleRef.size() - quantity.size() - std::string("    ").size() - price.size();

        while (article.size() < articleSize)
            article += " ";
    }*/

}
}