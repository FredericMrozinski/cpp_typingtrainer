#ifndef _TYPING_STATS
#define _TYPING_STATS

#include <map>
#include <tuple>
#include <iostream>
#include "nlohmann/json.hpp"

class TypingStats
{
    private:
        std::map<char, int> num_of_correct_char_typings;
        std::map<char, int> num_of_errors_for_expected_char;
        std::map<std::pair<char, char>, std::pair<int, long>> num_and_time_betw_typed_chars;

        // The following variables could indeed be fully derived from the above
        // maps. However, for ease of implementation and to avoid iterating over
        // maps too much, we also track these values separately. 
        int total_num_correctly_typed_chars;
        int total_num_wrongly_typed_chars;
        long total_time_typed_ms;
        std::map<int, int> typings_per_row;
        std::map<int, int> typings_per_finger;
        std::map<int, int> errors_per_row;
        std::map<int, int> errors_per_finger;


    public:

        TypingStats();

        TypingStats(nlohmann::json j);

        void add_correctly_typed(char c);

        void add_wrongly_typed(char c);

        void add_char_pair_typed(char prev_char, char current_char, long elapsed_ms_between_both);

        void flush();

        TypingStats& operator+=(const TypingStats & other_stats);

        int get_num_of_correct_typings_of_char(char c) const;

        int get_num_of_errors_for_expected_char(char c) const;

        std::unique_ptr<std::vector<std::pair<char, float>>> get_errors_for_char_sorted(bool relative_error) const;

        std::unique_ptr<std::vector<std::tuple<char, char, float>>> get_duration_for_letter_combinations_sorted() const;

        int get_num_of_errors() const;

        int get_num_of_correct_chars() const;

        // including errors
        int get_num_of_typed_chars() const;

        long get_total_elapsed_time_ms() const;

        std::unique_ptr<std::map<int, float>> get_errors_per_finger(bool relative_error) const;

        std::unique_ptr<std::map<int, float>> get_errors_per_row(bool relative_error) const;

        nlohmann::json to_json() const;

};

std::ostream & operator<< (std::ostream & st, const TypingStats & stats);

TypingStats stats_from_string(const std::string & stat_str);

#endif