#ifndef _TYPING_TRAINER_SESSION
#define _TYPING_TRAINER_SESSION

#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "TypingStatsV2.h"
#include "TypingStatsRecorder.h"

class TypingTrainerSession
{

private:

    static std::shared_ptr<std::vector<User>> users_vec;

    std::unique_ptr<TypingStatsRecorder> stats_recorder;
    std::string _training_text;
    int _pos_in_training_text;
    User* current_user = nullptr;

    void end_training();

public:

    static std::shared_ptr<std::vector<User>> users();

    static void init();

    static void write_users();

    static void read_users();

    std::string training_text();

    int pos_in_training_text();

    std::shared_ptr<TypingStats> get_training_stats();

    void run_typing_trainer(User* user);

    bool char_typed(char c);

    bool training_running();

    void abort_typing_training();
};

#endif
