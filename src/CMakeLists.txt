cmake_minimum_required (VERSION 3.1)

project(TypingTrainer VERSION 0.3.0 LANGUAGES CXX)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# find_package(nlohmann_json 3.2.0 REQUIRED)


# Only for debugging purposes!
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_executable(TypingTrainer main.cpp TypingTrainerUI.cpp TypingTrainerSession.cpp User.cpp
TypingStatsV2.cpp TypingStatsRecorder.cpp utils.cpp TrainingTextGenerator.cpp)
target_link_libraries(TypingTrainer ncurses tinfo)
# target_link_libraries(TypingTrainer ncurses tinfo PRIVATE nlohmann_json::nlohmann_json)