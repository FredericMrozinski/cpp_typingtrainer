#include "TypingStatsRecorder.h"

/*
    This function starts a statistics recording session. 
    It should be called when the user begins a typing training
    session.
*/
void TypingStatsRecorder::begin_stats_recording()
{
    session_stats = std::make_shared<TypingStats>();
    session_begin_ms = TIMING_CLOCK::now();
    last_event_ms = session_begin_ms;
    is_recording = true;
}

void TypingStatsRecorder::end_stats_recording()
{
    is_recording = false;
}

std::shared_ptr<TypingStats> TypingStatsRecorder::get_typing_stats()
{
    return session_stats;
}

void TypingStatsRecorder::record_char_typed(char typed, char expected)
{
    if(!is_recording)
    {
        throw std::runtime_error("Typing statistics cannot be logged when not recording."
            "Call begin_stats_recording() first.");
    }

    std::chrono::time_point<TIMING_CLOCK> current_event_ms = TIMING_CLOCK::now();
    long time_since_last_event_ms = std::chrono::duration_cast<std::chrono::milliseconds>
        (current_event_ms - last_event_ms).count();

    session_stats->add_char_pair_typed(last_typed_char, expected, time_since_last_event_ms); 
    if(typed == expected)
        session_stats->add_correctly_typed(typed);
    else
        session_stats->add_wrongly_typed(expected);

    last_typed_char = typed;
    last_event_ms = current_event_ms;
}
