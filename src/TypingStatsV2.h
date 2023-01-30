/*************************************************

TypingStatsV2.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

This file defines a class that represents statistics
for typing session(s).

Upon View/GUI adaption, the developer might want
to use this class to show information to the user.
However, the developer will not have to use this class
for other purposes than reading and flushing. To
record typing data into this class, use 
TypingTrainerSession or if lower-level adaptions are
necessary TypingStatsRecorder.

**************************************************/

#ifndef _TYPING_STATS
#define _TYPING_STATS

#include <map>
#include <tuple>
#include <iostream>
#include "nlohmann/json.hpp"

class TypingStats
{
    private:
        
        // The following three maps are the only "true" data that
        // this class holds. All other values of interest can
        // be derived from those.

        /*
            For each character, the amount of times this char has
            been typed where it was expected.
        */
        std::map<char, int> num_of_correct_char_typings;

        /*
            For each character, the amount of times where the
            character was expected but a different char was typed.
        */
        std::map<char, int> num_of_errors_for_expected_char;

        /*
            For each two consecutively typed characters, the
            amount of typings of that pair (first element of pair)
            and the amount of milliseconds between the typing of the
            two letters (second element of pair). 

            In case of incorrect typed chars, this map should not be
            altered until the correct char has been entered. It's semantic
            is to only contain the spans between correct chars. This 
            behavior is not actually enforced here but assured by using
            TypingStatsRecorder for statistics recording.
        */
        std::map<std::pair<char, char>, std::pair<int, long>> num_and_time_betw_typed_chars;

        // The following variables could indeed be fully derived from the above
        // maps. However, for ease of implementation and to avoid iterating over
        // maps too much, we also track these values separately. One could argue 
        // about this approach but since there is barely any memory overhead and
        // less code computation, we frankly consider this part of optimization 
        // through efficiency by laziness ;)

        /*
            The total number of correct char typings, i.e. sum over the map
            num_of_correct_char_typings.
        */
        int total_num_correctly_typed_chars;

        /*
            The total number of incorrect char typings, i.e. sum over the map
            num_of_errors_for_expected_char.
        */
        int total_num_wrongly_typed_chars;

        /*
            The total amount of time spent typing (in milliseconds),
            i.e. sum over the second element of the pair in the map 
            num_and_time_betw_typed_chars.
        */
        long total_time_typed_ms;

        /*
            Number of characters that have been typed for a certain
            row on the keyboard (see utils.h). This includes incorrect characters
            as well, i.e. number of total key strokes. Note that if 
            we type an incorrect character, the typing will count for the expected
            character, as the errors always count for the exptected character.
        */
        std::map<int, int> typings_per_row;

        /*
            Number of characters that have been typed (ideally) by a certain
            finger on the keyboard (see utils.h). This includes incorrect characters
            as well, i.e. number of total key strokes. Note that if 
            we type an incorrect character, the typing will count for the expected
            character, as the errors always count for the exptected character.
        */
        std::map<int, int> typings_per_finger;

        /*
            Number of characters that have been wrongly typed for a certain
            row on the keyboard (see utils.h). Note that if 
            we type an incorrect character, the typing will count for the expected
            character, as the errors always count for the exptected character.
        */
        std::map<int, int> errors_per_row;

        /*
            Number of characters that have been wrongly typed by a certain
            finger on the keyboard (see utils.h). Note that if 
            we type an incorrect character, the typing will count for the expected
            character, as the errors always count for the exptected character.
        */
        std::map<int, int> errors_per_finger;


    public:

        TypingStats();

        /*
            This constructor can be used to create an instance of TypingStats
            based on JSON-input. This is used to retrieve saved information
            from disk.

            SEE_ALSO:
                nlohmann::json to_json()

            ARGS:
                nlohmann::json j: 
                                A json object. The json structure will not be
                                specified here, as it can be inferred from the
                                method implementation.                                
        */
        TypingStats(nlohmann::json j);

        /*
            Populates all object members (maps and counters) with the information
            of the correctly typed character.

            ARGS:
                char c:         The character that has been correctly typed.
        */
        void add_correctly_typed(char c);

        /*
            Populates all object members (maps and counters) with the information
            of the incorrectly typed character.

            ARGS:
                char c:         The character that has been EXPTECTED. The actual
                                incorrect keystroke is not being recorded.
        */
        void add_wrongly_typed(char c);

        /*
            Populates num_and_time_betw_typed_chars. See the map's documentation
            for further details.

            ARGS:
                char prev_char: Last/previous correct character
                char current_char:
                                Current correct character
                long elapsed_ms_between_both:
                                The time (in milliseconds) that passed between this
                                and last correctly input char.
        */
        void add_char_pair_typed(char prev_char, char current_char, long elapsed_ms_between_both);

        /*
            Resets all the statistic's values to zero/an initial state. This can
            be called when requesting to delete the progress for a certain user.
            It is safe to call this method from the View/GUI.
        */
        void flush();

        /*
            Enables the functionality of adding other statistics to this statistic.
            This is helpful when we want to combine just recorded statistics from 
            a training session with the user's overall statistics.

            ARGS:
                const TypingStats & other_stats:
                                The TypingStats that will be added to these statistics
            RETURNS:
                reference to this.
        */
        TypingStats& operator+=(const TypingStats & other_stats);

        /*
            Writes the state of this statistic into a json object, that can
            later be used to e.g. save this object to disk for later retrieval.

            SEE ALSO:
                TypingStats(nlohmann::json j)

            RETURNS:
                nlohmann::json: We do not specify the json strucutre here, as 
                                it can be inferred from the implementation in the
                                corresponding cpp file.
        */
        nlohmann::json to_json() const;

        /*
            This method provides a sorted vector of char-wise-errors. It can
            retrieve these errors absolutely or relative to the number of total
            typings of that character. 

            This method performs array copying and sorting on the call and does
            NOT store the result for faster retrieval upon another call. However,
            the latency resulting from this should be negligible because the 
            underlying map does not contain more entries than keys on the keyboard.

            ARGS:
                bool relative error:
                                Whether the result will be on a relative or absolute
                                error scale.
            
            RETURNS:
                std::unique_ptr<std::vector<std::pair<char, float>>>:
                                The first element in the pair (char) represents the 
                                char for which the second element (float) is the 
                                error. The array is sorted from large to small error.
        */
        std::unique_ptr<std::vector<std::pair<char, float>>> get_errors_for_char_sorted(bool relative_error) const;

        /*
            This method provides a sorted vector of char-pair-wise-typing-time.

            This method performs array copying and sorting on the call and does
            NOT store the result for faster retrieval upon another call. However,
            the latency resulting from this should be negligible because the 
            underlying map does not contain more entries than keys on the keyboard
            squared. The negligibility is assumed for the case in which this software
            is not used for critical infrastructural real-time performance (e.g. 
            sending rockets to Mars or self driving vehicles...you see where this is
            going - optimization is not always necessary ;) )
            
            RETURNS:
                std::unique_ptr<std::vector<std::tuple<char, char, float>>>:
                                The first two elements in the tuple are the characters
                                for which the third element is the number of avg. SECONDS
                                that the user took to type these chars consecutively (ignoring
                                errors in between).
        */
        std::unique_ptr<std::vector<std::tuple<char, char, float>>> get_duration_for_letter_combinations_sorted() const;

        /*
            Returns the (absolute or relative) error rate for each finger. See 'utils.h'
            for interpreting the fingers as integers.

            ARGS:
                bool relative error:
                                Whether the result will be on a relative or absolute
                                error scale.
            
            RETURNS:
                std::unique_ptr<std::map<int, float>>:
                                The first element in the pair (int) represents the 
                                finger for which the second element (float) is the 
                                error rate.
        */
        std::unique_ptr<std::map<int, float>> get_errors_per_finger(bool relative_error) const;

        /*
            Returns the (absolute or relative) error rate for each row on the keyboard.
            See 'utils.h' for interpreting the rows as integers.

            ARGS:
                bool relative error:
                                Whether the result will be on a relative or absolute
                                error scale.
            
            RETURNS:
                std::unique_ptr<std::map<int, float>>:
                                The first element in the pair (int) represents the 
                                row for which the second element (float) is the 
                                error rate.
        */
        std::unique_ptr<std::map<int, float>> get_errors_per_row(bool relative_error) const;

        /*
            Trivial getter, see documentation of num_of_correct_char_typings 
            for details.
        */
        int get_num_of_correct_typings_of_char(char c) const;

        /*
            Trivial getter, see documentation of num_of_errors_for_expected_char 
            for details.
        */
        int get_num_of_errors_for_expected_char(char c) const;

        /*
            Trivial getter, see documentation of total_num_wrongly_typed_chars
            for details.
        */
        int get_num_of_errors() const;

        /*
            Trivial getter, see documentation of total_num_correctly_typed_chars
            for details.
        */
        int get_num_of_correct_chars() const;

        /*
            Equivalent to calling 'get_num_of_correct_chars() + get_num_of_errors()'.

            RETURNS:
                int:            The total number of typed characters, including
                                incorrect typings.
        */
        int get_num_of_typed_chars() const;

        /*
            Trivial getter, see documentation of total_time_typed_ms for details.
        */
        long get_total_elapsed_time_ms() const;

};

#endif