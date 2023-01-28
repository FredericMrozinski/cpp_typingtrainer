#include <iostream>
#include <memory>

#include "TypingStatsV2.h"
#include "TypingStatsRecorder.cpp"

int main()
{
    std::cout << "Begin testing" << std::endl;

    TypingStatsRecorder rec;

    rec.begin_stats_recording();

    rec.record_char_typed('a', 'a');
    rec.record_char_typed('b', 'c');
    rec.record_char_typed('a', 'a');
    rec.record_char_typed('c', 'c');

    std::shared_ptr<TypingStats> stats = rec.end_stats_recording();

    std::cout << stats->get_num_of_correct_typings_of_char('a') << std::endl;
    std::cout << stats->get_num_of_correct_typings_of_char('b') << std::endl;
    std::cout << stats->get_num_of_correct_typings_of_char('c') << std::endl;

    std::cout << stats->get_num_of_errors_for_expected_char('a') << std::endl;
    std::cout << stats->get_num_of_errors_for_expected_char('b') << std::endl;
    std::cout << stats->get_num_of_errors_for_expected_char('c') << std::endl;

    std::cout << "End testing" << std::endl;

    return 0;
}