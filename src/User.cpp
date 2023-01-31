#include "User.h"

#define USER_STR_HEADER "USER:\n"


User::User(std::string user_name) : user_name(user_name)
{
    difficulty_level = 1;
    user_typing_stats = std::make_shared<TypingStats>(); 
}

User::User(const User & another_user) : user_name(another_user.user_name)
{
    user_typing_stats = another_user.user_typing_stats;
    difficulty_level = another_user.difficulty_level;
}

User::User(nlohmann::json j) : user_name(j["user_name"])
{
    difficulty_level = j["difficulty_level"];
    user_typing_stats = std::make_shared<TypingStats>(j["typing_stats"]);
}

void User::set_difficulty(int d)
{
    user_typing_stats->flush();
    difficulty_level = d;
}

nlohmann::json User::to_json() const
{
    nlohmann::json j;
    j["user_name"] = user_name;
    j["difficulty_level"] = difficulty_level;
    j["typing_stats"] = user_typing_stats->to_json();
    
    return j;
}

int User::get_difficulty() const
{
    return difficulty_level;
}