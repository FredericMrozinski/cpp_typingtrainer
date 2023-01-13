#include <string>
#include <memory>
#include <iostream>
#include "TypingStats.cpp"

#define USER_STR_HEADER "USER:\n"

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

        User(std::string user_name) : user_name(user_name)
        {
            difficulty_level = 1;

        }

        User(const User & another_user) : user_name(another_user.user_name)
        {
            user_typing_stats = another_user.user_typing_stats;
            difficulty_level = another_user.difficulty_level;
        }

        User operator=(const User & user)
        {
            if(this == &user)
                return *this;
        }

};

std::ostream & operator<< (std::ostream & st, const User & user)
{
    return st << USER_STR_HEADER << user.user_name << std::endl << user.difficulty_level << std::endl
        << user.user_typing_stats << std::endl;
}

User* user_from_string(const std::string & user_str)
{
    std::string str = user_str;

    // Check if the string to create the user from has proper "syntax"
    int header_pos = str.find(USER_STR_HEADER);
    if (header_pos != 0) 
    {
        throw std::invalid_argument("Error in string format: User cannot be created.");
    }
    str = str.substr(std::string(USER_STR_HEADER).length());

    // Parse user name
    int new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: User cannot be created.");
    }
    std::string user_name = str.substr(0, new_line_pos);
    str = str.substr(new_line_pos + 1);
    User* to_build = new User(user_name);

    // Parse difficulty
    new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: User cannot be created.");
    }
    to_build->difficulty_level = std::stoi(str.substr(0, new_line_pos));
    str = str.substr(new_line_pos + 1);

    to_build->user_typing_stats = *stats_from_string(str);

    return to_build;
}