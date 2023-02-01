/*************************************************

TypingStatsV2.cpp
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

For detailed documentation, please refer to
TypingStatsV2.h.

**************************************************/

#include "TypingStatsV2.h"
#include "utils.h"

using json = nlohmann::json;

template<typename T>
concept Addable = requires(T x) { x += x; };

template<Addable T1, Addable T2>
std::pair<T1, T2>& operator+=(std::pair<T1, T2>& pair1, const std::pair<T1, T2>& pair2)
{
    pair1.first += pair2.first;
    pair1.second += pair2.second;

    return pair1;
}

TypingStats::TypingStats()
{
    total_num_correctly_typed_chars = 0;
    total_num_wrongly_typed_chars = 0;
    total_time_typed_ms = 0;

    for(int i = 1; i <= 10; i++)
        errors_per_finger[i] = 0;

    for(int i = 1; i <= 5; i++)
        errors_per_row[i] = 0;

    for(int i = 1; i <= 10; i++)
        typings_per_finger[i] = 0;

    for(int i = 1; i <= 5; i++)
        typings_per_row[i] = 0;
}

TypingStats::TypingStats(nlohmann::json j)
{
    total_num_correctly_typed_chars = j["num_of_correct_chars"];
    total_num_wrongly_typed_chars = j["num_of_wrong_chars"];
    total_time_typed_ms = j["time_typed_ms"];

    num_of_correct_char_typings = j["chars_correct"];
    num_of_errors_for_expected_char = j["chars_wrong"];
    num_and_time_betw_typed_chars = j["char_pairs_num_and_time"];
    errors_per_row = j["errors_per_row"];
    typings_per_row = j["typings_per_row"];
    errors_per_finger = j["errors_per_finger"];
    typings_per_finger = j["typings_per_finger"];
}

template<typename T1, typename T2>
inline void merge_map_to_map(std::map<T1, T2>& to_merge_into, const std::map<T1, T2>& to_merge_from)
{
    for(const auto& tmf_map_entry : to_merge_from)
    {
        to_merge_into[tmf_map_entry.first] += tmf_map_entry.second;
    }
}

void TypingStats::add_correctly_typed(char c)
{
    num_of_correct_char_typings[c]++;

    total_num_correctly_typed_chars++;

    // Besides adding to the correct array, we also always want to make sure
    // that the "error-array" contains equally many entries:
    if(num_of_errors_for_expected_char.find(c) == num_of_errors_for_expected_char.end())
        num_of_errors_for_expected_char[c] = 0;

    // Add to the per row statistic
    int row = get_row_for_key(c);
    typings_per_row[row]++;

    // Add to the per finger statistic
    int finger = get_finger_for_key(c);
    typings_per_finger[finger]++;
}

void TypingStats::add_wrongly_typed(char c)
{
    num_of_errors_for_expected_char[c]++;

    total_num_wrongly_typed_chars++;

    // Besides adding to the error-array, we also always want to make sure
    // that the "correct-array" contains equally many entries:
    if(num_of_correct_char_typings.find(c) == num_of_correct_char_typings.end())
        num_of_correct_char_typings[c] = 0;

    // Add to the per row statistic
    int row = get_row_for_key(c);
    errors_per_row[row]++;
    typings_per_row[row]++;

    // Add to the per finger statistic
    int finger = get_finger_for_key(c);
    errors_per_finger[finger]++;
    typings_per_finger[finger]++;
}

void TypingStats::add_char_pair_typed(char prev_char, char current_char, long elapsed_ms_between_both)
{
    std::pair<char, char> chars(prev_char, current_char);

    // If map has no entry for the pair
    if(num_and_time_betw_typed_chars.find(chars) == num_and_time_betw_typed_chars.end())
        num_and_time_betw_typed_chars[chars] = std::pair(1, elapsed_ms_between_both);
    // If map does have an entry for the pair
    else
    {
        std::pair<int, long>& from_map = num_and_time_betw_typed_chars[chars];
        from_map.first++;
        from_map.second += elapsed_ms_between_both;
    }

    total_time_typed_ms += elapsed_ms_between_both;
}

int TypingStats::get_num_of_correct_typings_of_char(char c) const
{
    return num_of_correct_char_typings.at(c);
}

int TypingStats::get_num_of_errors_for_expected_char(char c) const
{
    return num_of_errors_for_expected_char.at(c);
}

void TypingStats::flush()
{
    total_num_correctly_typed_chars = 0;
    total_num_wrongly_typed_chars = 0;
    total_time_typed_ms = 0;

    num_of_correct_char_typings.clear();
    num_of_errors_for_expected_char.clear();
    num_and_time_betw_typed_chars.clear();
    typings_per_row.clear();
    typings_per_finger.clear();
    errors_per_row.clear();
    errors_per_finger.clear();

    for(int i = 1; i <= 10; i++)
        errors_per_finger[i] = 0;

    for(int i = 1; i <= 5; i++)
        errors_per_row[i] = 0;

    for(int i = 1; i <= 10; i++)
        typings_per_finger[i] = 0;

    for(int i = 1; i <= 5; i++)
        typings_per_row[i] = 0;
}

long TypingStats::get_total_elapsed_time_ms() const
{
    return total_time_typed_ms;
}

int TypingStats::get_num_of_errors() const
{
    return total_num_wrongly_typed_chars;
}

TypingStats& TypingStats::operator+=(const TypingStats & other_stats)
{
    total_num_correctly_typed_chars += other_stats.total_num_correctly_typed_chars;
    total_num_wrongly_typed_chars += other_stats.total_num_wrongly_typed_chars;
    total_time_typed_ms += other_stats.total_time_typed_ms;
    merge_map_to_map(num_of_correct_char_typings, other_stats.num_of_correct_char_typings);
    merge_map_to_map(num_of_errors_for_expected_char, other_stats.num_of_errors_for_expected_char);
    merge_map_to_map(num_and_time_betw_typed_chars, other_stats.num_and_time_betw_typed_chars);
    merge_map_to_map(errors_per_row, other_stats.errors_per_row);
    merge_map_to_map(errors_per_finger, other_stats.errors_per_finger);
    merge_map_to_map(typings_per_row, other_stats.typings_per_row);
    merge_map_to_map(typings_per_finger, other_stats.typings_per_finger);

    return *this;
}

int TypingStats::get_num_of_typed_chars() const
{
    return total_num_correctly_typed_chars + total_num_wrongly_typed_chars;
}

int TypingStats::get_num_of_correct_chars() const
{
    return total_num_correctly_typed_chars;
}

std::unique_ptr<std::map<int, float>> TypingStats::get_errors_per_finger(bool relative_error) const
{
    std::unique_ptr<std::map<int, float>> to_return = std::make_unique<std::map<int, float>>();

    for(const auto& [key, val] : errors_per_finger)
    {
        if(relative_error)
        {
            // To avoid division by 0
            if(errors_per_finger.at(key) == 0)
                (*to_return)[key] = 0;
            else
                (*to_return)[key] = (float) errors_per_finger.at(key) / typings_per_finger.at(key);
        }
        else
            (*to_return)[key] = errors_per_finger.at(key);
    }

    return to_return;
}

std::unique_ptr<std::map<int, float>> TypingStats::get_errors_per_row(bool relative_error) const
{
    std::unique_ptr<std::map<int, float>> to_return = std::make_unique<std::map<int, float>>();

    for(const auto& [key, val] : errors_per_row)
    {
        if(relative_error)
        {
            // To avoid division by 0
            if(errors_per_row.at(key) == 0)
                (*to_return)[key] = 0;
            else
                (*to_return)[key] = (float) errors_per_row.at(key) / typings_per_row.at(key);
        }
        else
            (*to_return)[key] = errors_per_row.at(key);
    }

    return to_return;
}

std::unique_ptr<std::vector<std::pair<char, float>>> 
    TypingStats::get_errors_for_char_sorted(bool relative_error) const
{
    std::unique_ptr<std::vector<std::pair<char, float>>> to_return;

    if(relative_error)
    {
        to_return = std::make_unique<std::vector<std::pair<char, float>>>(num_of_correct_char_typings.size());
        int ind = 0;
        for (auto const& [key, val] : num_of_correct_char_typings)
        {
            to_return->at(ind++) = {key, (float) num_of_errors_for_expected_char.at(key) / val};
        }
    }
    else
    {
        to_return = std::make_unique<std::vector<std::pair<char, float>>>(
            num_of_errors_for_expected_char.begin(), num_of_errors_for_expected_char.end());
    }

    std::sort(to_return->begin(), to_return->end(), [] (std::pair<char, float> a, std::pair<char, float> b) 
    {
        return a.second > b.second;
    });

    return to_return;
}

std::unique_ptr<std::vector<std::tuple<char, char, float>>> 
    TypingStats::get_duration_for_letter_combinations_sorted() const
{
    std::unique_ptr<std::vector<std::tuple<char, char, float>>> to_return 
        = std::make_unique<std::vector<std::tuple<char, char, float>>>(num_and_time_betw_typed_chars.size());
    
    int ind = 0;
    for (auto const& [key, val] : num_and_time_betw_typed_chars)
    {
        to_return->at(ind++) = {key.first, key.second, (float) val.second / val.first / 1e3};
    }

    std::sort(to_return->begin(), to_return->end(), [] (std::tuple<char, char, float> a, std::tuple<char, char, float> b)
    {
        return std::get<2>(a) > std::get<2>(b);
    });

    return to_return;
}

json TypingStats::to_json() const
{
    json j;

    j["num_of_correct_chars"] = total_num_correctly_typed_chars;
    j["num_of_wrong_chars"] = total_num_wrongly_typed_chars;
    j["time_typed_ms"] = total_time_typed_ms;

    j["chars_correct"] = num_of_correct_char_typings;
    j["chars_wrong"] = num_of_errors_for_expected_char;
    j["char_pairs_num_and_time"] = num_and_time_betw_typed_chars;
    j["errors_per_row"] = errors_per_row;
    j["typings_per_row"] = typings_per_row;
    j["errors_per_finger"] = errors_per_finger;
    j["typings_per_finger"] = typings_per_finger;

    return j;
}