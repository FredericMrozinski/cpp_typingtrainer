/*************************************************

TypingStatsRecorder.cpp
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

For functionality documentation, refer to
TrainingTextGenerator.h

**************************************************/

#include "TypingStatsRecorder.h"


TypingStatsRecorder::TypingStatsRecorder()
{
    is_recording = false;
}

void TypingStatsRecorder::begin_stats_recording()
{
    session_stats = std::make_shared<TypingStats>();
    session_begin_ms = CLOCK::now();
    last_event_ms = session_begin_ms;
    is_recording = true;
}

void TypingStatsRecorder::end_stats_recording()
{
    is_recording = false;
}

void TypingStatsRecorder::record_char_typed(char typed, char expected)
{
    if(!is_recording)
    {
        throw std::runtime_error("Typing statistics cannot be logged when not recording."
            "Call begin_stats_recording() first.");
    }

    std::chrono::time_point<CLOCK> current_event_ms = CLOCK::now();
    long time_since_last_event_ms = std::chrono::duration_cast<std::chrono::milliseconds>
        (current_event_ms - last_event_ms).count();

    if(typed == expected)
    {
        session_stats->add_correctly_typed(typed);
        session_stats->add_char_pair_typed(last_typed_char, expected, time_since_last_event_ms); 
        last_typed_char = typed;
    }
    else
        session_stats->add_wrongly_typed(expected);

    last_event_ms = current_event_ms;
}

std::shared_ptr<TypingStats> TypingStatsRecorder::get_typing_stats() const
{
    return session_stats;
}
