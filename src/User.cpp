#include "User.h"

#define USER_STR_HEADER "USER:\n"


User::User(std::string user_name) : user_name(user_name)
{
    difficulty_level = 1;

}

User::User(const User & another_user) : user_name(another_user.user_name)
{
    user_typing_stats = another_user.user_typing_stats;
    difficulty_level = another_user.difficulty_level;
}

User::User(nlohmann::json j) : user_name(j["user_name"])
{
    difficulty_level = j["difficulty_level"];
    user_typing_stats = TypingStats(j["typing_stats"]);
}

nlohmann::json User::to_json() const
{
    nlohmann::json j;
    j["user_name"] = user_name;
    j["difficulty_level"] = difficulty_level;
    j["typing_stats"] = user_typing_stats.to_json();
    
    return j;
}

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

    to_build->user_typing_stats = stats_from_string(str);

    return to_build;
}