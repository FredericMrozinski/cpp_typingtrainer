/*************************************************

TypingTrainerSession.cpp
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

For detailed documentation, please refer to
TypingTrainerSession.h.

**************************************************/

#include <string>
#include <fstream>
#include "TypingTrainerSession.h"
#include "TypingStatsRecorder.h"
#include "TrainingTextGenerator.h"
#include "nlohmann/json.hpp"
#include "utils.h"

std::shared_ptr<std::vector<User>> TypingTrainerSession::users_vec 
    = std::make_shared<std::vector<User>>();

void TypingTrainerSession::init()
{
    TrainingTextGenerator::read_sample_words_from_files();
    read_users();
    init_utils();
}

void TypingTrainerSession::read_users()
{
    TypingTrainerSession::users_vec->erase(TypingTrainerSession::users_vec->begin(), 
        TypingTrainerSession::users_vec->end());
    
    std::ifstream istr("../res/user_data/users.json");

    if(istr.is_open())
    {
        try
        {
            nlohmann::json j;
            istr >> j;

            for(const auto& json_u : j)
            {
                User u = User(json_u);
                users_vec->push_back(u);
            }

        }
        catch(const std::exception& e) {}
    }

    istr.close();
}

void TypingTrainerSession::write_users()
{
    std::ofstream outstr;
    outstr.open ("../res/user_data/users.json");

    nlohmann::json j_arr = nlohmann::json::array();

    for(const User & u : *TypingTrainerSession::users_vec)
    {
        //outstr << u << std::endl;
        j_arr.push_back(u.to_json());
    }

    outstr << j_arr << std::endl;

    outstr.close();
}

std::shared_ptr<std::vector<User>> TypingTrainerSession::users()
{
    return TypingTrainerSession::users_vec;
}

void TypingTrainerSession::run_typing_trainer(User* user)
{
    current_user = user;
    stats_recorder = std::make_unique<TypingStatsRecorder>();
    stats_recorder->begin_stats_recording();

    _training_text = TrainingTextGenerator::get_sample_text(user->get_difficulty(), 10);

    _pos_in_training_text = 0;
}

bool TypingTrainerSession::char_typed(char c)
{
    if(_pos_in_training_text >= _training_text.length())
        throw std::runtime_error("The training has ended. No chars can be input anymore.");

    stats_recorder->record_char_typed(c, _training_text[_pos_in_training_text]);

    bool correct_char_given = c == _training_text[_pos_in_training_text];
    // Only move on to next char if the correct char was typed
    if(correct_char_given)
        _pos_in_training_text++;

    if(_pos_in_training_text == _training_text.length())
        end_training();

    return correct_char_given;
}

void TypingTrainerSession::end_training()
{
    *(current_user->user_typing_stats) += *get_training_stats();
    _training_text = "";
    _pos_in_training_text = 0;
    current_user = nullptr;
}

bool TypingTrainerSession::training_running()
{
    return _pos_in_training_text < _training_text.length();
}

std::shared_ptr<TypingStats> TypingTrainerSession::get_training_stats()
{
    return stats_recorder->get_typing_stats();
}

std::string TypingTrainerSession::training_text()
{
    return _training_text;
}

int TypingTrainerSession::pos_in_training_text()
{
    return _pos_in_training_text;
}

void TypingTrainerSession::abort_typing_training()
{
    end_training();
}
