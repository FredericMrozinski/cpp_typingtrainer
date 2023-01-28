#include "TypingTrainerUI.h"
#include <map>
#include <tuple>
#include "nlohmann/json.hpp"

int main()
{

    TypingTrainerUI::init();
    TypingTrainerUI::show_program_menu();

    // std::map<std::pair<char, char>, std::pair<int, int>> test_map;
    // test_map[{'a', 'b'}] = {1, 2};
    // test_map[{'b', 'c'}] = {2, 3};
    // test_map[{'c', 'd'}] = {3, 4};

    // nlohmann::json j;
    // j["test"] = test_map;
    // std::cout << j << std::endl;

    // nlohmann::json j = nlohmann::json::parse(R"(
    //     {"test":[[[97,98],[1,2]],[[98,99],[2,3]],[[99,100],[3,4]]]}
    // )");

    // auto test = j["test"];
    // test_map = j["test"];

    // User u = User(static_cast<std::string>("Pimmelberger"));

    // std::cout << u.to_json() << std::endl;

    return 0;
}