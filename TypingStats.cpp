#include <string>
#include <iostream>

#define STATS_STR_HEADER "TYPING_STATS:\n"

/*
    This class encapsulates basic typing statistics. The class also supports
    storing its values into a stream (or stream actually) to be later reconstructed
    from that stream. This is used for retrieving user information from disk.
*/
class TypingStats
{
    public:
        int chars_typed = 0;
        float elapsed_time_sec = 0;
        int num_of_mistakes = 0;
        float type_rate = 0;

        TypingStats operator+(const TypingStats & other_stats)
        {
            TypingStats new_stats;
            new_stats.chars_typed = other_stats.chars_typed + chars_typed;
            new_stats.elapsed_time_sec = other_stats.elapsed_time_sec + elapsed_time_sec;
            new_stats.num_of_mistakes = other_stats.num_of_mistakes + num_of_mistakes;
            new_stats.type_rate = new_stats.chars_typed / new_stats.elapsed_time_sec * 60.;

            return new_stats;
        }

        // Resets all the values to a default state. It's being called
        // when we reset the statistics for a user.
        void flush()
        {
            chars_typed = 0;
            elapsed_time_sec = 0;
            num_of_mistakes = 0;
            type_rate = 0;
        }
};

std::ostream & operator<< (std::ostream & st, const TypingStats & stats)
{
    return st << STATS_STR_HEADER << 
        stats.chars_typed << std::endl << 
        stats.elapsed_time_sec << std::endl << 
        stats.num_of_mistakes << std::endl <<
        stats.type_rate << std::endl;
}

std::unique_ptr<TypingStats> stats_from_string(const std::string & stat_str)
{
    std::string str = stat_str;
    std::unique_ptr<TypingStats> to_build = std::make_unique<TypingStats>();

    // Check if the string to create the typing stats from has proper (header) "syntax"
    int header_pos = str.find(STATS_STR_HEADER);
    if (header_pos != 0) 
    {
        throw std::invalid_argument("Error in string format: TypingStats cannot be created.");
    }
    str = str.substr(std::string(STATS_STR_HEADER).length());

    // Parse chars_typed
    int new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: TypingStats cannot be created.");
    }
    to_build->chars_typed = std::stoi(str.substr(0, new_line_pos));
    str = str.substr(new_line_pos + 1);

    // Parse elapsed_time_sec
    new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: TypingStats cannot be created.");
    }
    to_build->elapsed_time_sec = std::stof(str.substr(0, new_line_pos));
    str = str.substr(new_line_pos + 1);

    // Parse num_of_mistakes
    new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: TypingStats cannot be created.");
    }
    to_build->num_of_mistakes = std::stoi(str.substr(0, new_line_pos));
    str = str.substr(new_line_pos + 1);

    // Parse type_rate
    new_line_pos = str.find('\n');
    if (new_line_pos == str.npos)
    {
        throw std::invalid_argument("Error in string format: TypingStats cannot be created.");
    }
    to_build->type_rate = std::stof(str.substr(0, new_line_pos));
    str = str.substr(new_line_pos + 1);

    return to_build;
}
