#ifndef _USER
#define _USER

#include <string>
#include <memory>
#include <iostream>
#include "TypingStatsV2.h"
#include "nlohmann/json.hpp"

/*
    This class encapsulates basic information about the user. The class also supports
    storing its values into a stream (or stream actually) to be later reconstructed
    from that stream. This is used for retrieving user information from disk.
*/
class User 
{
    public:
        const std::string user_name;
        TypingStats user_typing_stats;
        int difficulty_level;

        User(std::string user_name);

        User(const User & another_user);

        User(nlohmann::json j);

        User operator=(const User & user)
        {
            if(this == &user)
                return *this;
            else
                throw std::invalid_argument("This assignment style is not intended");
        }

        nlohmann::json to_json() const;

};

std::ostream & operator<< (std::ostream & st, const User & user);

User* user_from_string(const std::string & user_str);

#endif