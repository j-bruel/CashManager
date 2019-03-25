//!
//! @file ChequeInformationGenerator.hpp
//! @author jbruel
//! @date 24/12/18
//!

#ifndef CASH_MANAGER_CLIENT_CORE_CHEQUEINFORMATIONGENERATOR_HPP
# define CASH_MANAGER_CLIENT_CORE_CHEQUEINFORMATIONGENERATOR_HPP

#include <string>
#include <vector>
#include <ctime>
#include <cstring>

//!
//! @namespace cash
//!
namespace cash
{
//!
//! @namespace core
//!
namespace core
{

    //!
    //! @class ChequeInfoGenerator
    //! @brief Cheque information generator.
    //!
    class   ChequeInfoGenerator
    {
    private:
        //!
        //! @var const std::vector<std::string>  mNames
        //! @brief All names handle by the generator.
        //!
        const std::vector<std::string>  mNames = {
                "Myles Kennedy",
                "Mark Tremonti",
                "Brian Marshall",
                "Scott Phillips",
                "Oliver Sykes",
                "Jordan Fish",
                "Lee Malia",
                "Matthew Nicholls",
                "Matt Kean",
                "Curtis Ward",
                "Jona Weinhofen",
                "Brent Smith",
                "Zach Myers",
                "Eric Bass",
                "Barry Kerch",
                "Jasin Todd",
                "Brad Stewart",
                "Nick Perri",
                "Jasen Rauch",
                "Anthony Armstrong",
                "Joe Rickard",
                "Jen Ledger",
                "John Cooper",
                "Korey Cooper",
                "Seth Morrison,",
                "Corey Taylor",
                "Joey Jordison",
                "Paul Gray",
                "James Root",
                "Winston McCall",
                "Jeff Ling",
                "Luke Kilpatrick",
                "Ben Gordon",
                "Jia O'Connor",
                "Shaun Cash",
                "Brett Versteeg"
        };

    public:
        //!
        //! @brief Default constructor
        //! @warning Not available.
        //!
        ChequeInfoGenerator() = default;
        //!
        //! @brief Copy constructor.
        //! @warning Not available.
        //!
        ChequeInfoGenerator(ChequeInfoGenerator &) = delete;
        //!
        //! @brief Equal operator overload.
        //! @return Generator copy.
        //! @warning Not available.
        //!
        ChequeInfoGenerator &operator=(const ChequeInfoGenerator &) = delete;
        //!
        //! @brief Destructor.
        //!
        ~ChequeInfoGenerator() = default;

    public:
        //!
        //! @brief Generate a cheque name.
        //! @return User name.
        //!
        const std::string   generateName() const;
        //!
        //! @brief Get current time.
        //! @return Time.
        //!
        const std::string   getCurrentTime() const;
        //!
        //! @brief Generate a cheque number.
        //! @return Cheque number.
        //!
        const std::string   generateChequeNumber() const;

    private:
        //!
        //! @brief Generate a random number.
        //! @param max Max generated number.
        //! @return Random generated number.
        //!
        size_t  generateRandomNumber(size_t max) const;
    };

}
}

#endif //CASH_MANAGER_CLIENT_CORE_CHEQUEINFORMATIONGENERATOR_HPP
