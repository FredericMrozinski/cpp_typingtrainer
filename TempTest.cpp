#include "User.cpp"
#include <iostream>
#include <sstream>
#include <memory>

int main()
{
    User user = User("Test user 1234");
    user.user_typing_stats.chars_typed = 12345;
    std::cout << user << std::endl;
    std::stringstream ss;
    ss << user;

    std::unique_ptr<User> user2 = user_from_string(ss.str());
    user2->user_typing_stats.elapsed_time_sec = 1;
    std::cout << *user2 << std::endl;
}