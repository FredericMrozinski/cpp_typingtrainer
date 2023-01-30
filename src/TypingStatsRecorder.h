/*************************************************

TypingStatsRecorder.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

This file defines a class that can be used to 
conveniently record training statistics during
a training session.

This class is being used by TypingTrainerSession.
Sole View/GUI adaptions or replacements will not
have to work this class.

**************************************************/

#ifndef _TYPING_STATS_RECORDER
#define _TYPING_STATS_RECORDER

#include <chrono>
#include <memory>
#include <iostream>

#include "TypingStatsV2.h"


#define CLOCK std::chrono::system_clock

class TypingStatsRecorder
{
    private:

        /*
            Whether the stats recording is currently running.
            In fact, this does not add any functionality besides
            ensuring that member functions are called in correct order.
            Thus is serves as a "program-flow-controller".
        */
        bool is_recording;

        /*
            A pointer to the statistic object that is being recorded into.
        */
        std::shared_ptr<TypingStats> session_stats;

        std::chrono::time_point<CLOCK> session_begin_ms;
        std::chrono::time_point<CLOCK> last_event_ms;

        char last_typed_char;

    public:

        TypingStatsRecorder();
        
        /*
            This function starts a statistics recording session. 
            It should be called when the user begins a typing training
            session.
        */
        void begin_stats_recording();

        /*
            When the user is done training and we want to mark the
            recording as inactive, this method should be called.
        */
        void end_stats_recording();

        /*
            When the user enters a character, this method will log
            all necessary information into the underlying TrainingStats.

            Since this method also takes care of tracking time-statistics
            it should be called with as little delay as possible after
            user input.

            ARGS:
                char typed:     The character that the user input
                char expected:  The character that was expected in
                                place of 'char typed'.
        */
        void record_char_typed(char typed, char expected);

        /*
            RETURNS:
                shared_ptr<TypingStats>:    
                                Current TypingStats that is being
                                recorded into.
        */
        std::shared_ptr<TypingStats> get_typing_stats() const;

};

#endif