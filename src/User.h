/*************************************************

TypingTrainerUI.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 25, 2023

This file contains the User-class, a class representing
all information related to a user for the TypingTrainer.

A user formally has a name, typing statistics (overall 
performance measure) and an assigned difficulty level.

The file further supports converting and parsing
a user to and from a JSON object for information
saving and retrieval.

**************************************************/

#ifndef _USER
#define _USER

#include <string>
#include <memory>
#include <iostream>
#include "TypingStatsV2.h"
#include "nlohmann/json.hpp"

class User 
{
    private:    

        /*
            The set difficulty level for typing.
        */
        int difficulty_level;


    public:

        /*
            Name of the user, arbitrary string.
        */
        const std::string user_name;

        /*
            The overall statistics/progress of the user.
        */
        std::shared_ptr<TypingStats> user_typing_stats;

        User(std::string user_name);

        User(const User & another_user);

        /*
            Constructs a user based on a given JSON object

            SEE ALSO:
                nlohmann::json to_json()
        */
        User(nlohmann::json j);

        /*
            Copy assignment operator. We do not need it generally,
            but only for very specific cases. Thus, we only implement
            this version as a functionality workaround for a couple
            of things.
        */
        User operator=(const User & user)
        {
            if(this == &user)
                return *this;
            else
                throw std::invalid_argument("This assignment style is not intended");
        }

        /*
            A setter for the difficulty_level with a little caveat:
            When we change the difficulty, the training statistics
            will be deleted. This is because the training statistics
            do not differentiate between the difficulty levels
            and therefore it does make sense to keep "old" statistics
            when the "environment" (i.e. difficulty) changes.
        */
        void set_difficulty(int difficulty);

         /*
            Writes the state of this User into a json object, that can
            later be used to e.g. save this object to disk for later retrieval.

            SEE ALSO:
                User(nlohmann::json j)

            RETURNS:
                nlohmann::json: We do not specify the json strucutre here, as 
                                it can be inferred from the implementation in the
                                corresponding cpp file.
        */
        nlohmann::json to_json() const;

        /*
            Trivial setter for difficulty_level.
        */
        int get_difficulty() const;

};

#endif