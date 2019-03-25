//!
//! @file ChequeInformationGenerator.cpp
//! @author jbruel
//! @date 24/12/18
//!

#include "Core/ChequeInformationGenerator.hpp"
#include <random>

namespace cash
{
namespace core
{

    const std::string   ChequeInfoGenerator::generateName() const
    {
        size_t  idx = generateRandomNumber(mNames.size());

        if (idx >= mNames.size())
            return ("Myles Kennedy");
        return (mNames[idx]);
    }

    const std::string   ChequeInfoGenerator::getCurrentTime() const
    {
        time_t      rawtime;
        struct tm   *timeinfo;
        char buffer [80];

        std::memset(buffer, '\0', 80);
        time(&rawtime);
        timeinfo = localtime (&rawtime);
        strftime(buffer, 80, "%d/%m/%Y", timeinfo);
        return (buffer);
    }

    const std::string   ChequeInfoGenerator::generateChequeNumber() const
    {
        std::string nb;

        for (size_t i = 0; i < 11; ++i)
            nb += std::to_string(generateRandomNumber(9));
        return (nb);
    }

    size_t  ChequeInfoGenerator::generateRandomNumber(size_t max) const
    {
        std::random_device seeder;

        std::mt19937 engine(seeder());
        std::uniform_int_distribution<int> dist(0, max);
        return (dist(engine));
    }

}
}