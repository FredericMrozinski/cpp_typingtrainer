#ifndef _TYPING_STATS_RECORDER
#define _TYPING_STATS_RECORDER

#include <chrono>
#include <memory>
#include <iostream>

#include "TypingStatsV2.h"


#define TIMING_CLOCK std::chrono::system_clock

class TypingStatsRecorder
{
    private:

        bool is_recording{false};
        std::shared_ptr<TypingStats> session_stats{nullptr};

        std::chrono::time_point<TIMING_CLOCK> session_begin_ms;
        std::chrono::time_point<TIMING_CLOCK> last_event_ms;

        char last_typed_char;

    public:
        
        /*
            This function starts a statistics recording session. 
            It should be called when the user begins a typing training
            session.
        */
        void begin_stats_recording();

        void end_stats_recording();

        std::shared_ptr<TypingStats> get_typing_stats();

        void record_char_typed(char typed, char expected);

};

#endif