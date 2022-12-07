#include <ncurses.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <array>
#include <memory>
using namespace std;

// Ncurses defines values for the enter and backspace key that
// do not work. Thus, we redefine their values to work on Linux machines.
// (Tested on Ubuntu & Fedora Linux)
#ifdef KEY_BACKSPACE
    #undef KEY_BACKSPACE
#endif
#ifdef KEY_ENTER
    #undef KEY_ENTER
#endif
#define KEY_BACKSPACE 127
#define KEY_ENTER 10

struct typing_stats
{
    int chars_typed;
    float elapsed_time_sec;
    int num_of_mistakes;
    float type_rate;
};

/*
    The start menu will be shown to the user, right in the beginning.
    It gives the user the ability to read through a short tutorial.
*/
void show_start_menu()
{
    initscr();

    addstr("==========================================================\n");
    addstr("|                                                        |\n");
    addstr("|              Welcome to Typing Trainer!                |\n");
    addstr("|               Press any key to continue.               |\n");
    addstr("|                                                        |\n");
    addstr("==========================================================\n");

    getch();

    clear();
    addstr("==========================================================\n");
    addstr("|                                                        |\n");
    addstr("|         Do you want to read a short how-to?            |\n");
    addstr("| Press 'y' for a tutorial, and 'n' to start right away. |\n");
    addstr("|                                                        |\n");
    addstr("==========================================================\n");

    char input_char{};
    while((input_char = getch()) != 'y' && input_char != 'n');

    if(input_char == 'y')
    {
        clear();
        addstr("==========================================================\n");
        addstr("|                                                        |\n");
        addstr("| Once you start the program, a text will be displayed   |\n");
        addstr("| at the top of your screen. You will have to input that |\n");
        addstr("| text on your keyboard. The text typing will end auto-  |\n");
        addstr("| matically once you typed the whole text. You may also  |\n");
        addstr("| terminate the trainer by hitting the enter key at any  |\n");
        addstr("| point during the training. After having finished,      |\n");
        addstr("| you can see statistics evaluating your performance. If |\n");
        addstr("| you happen to make a typo, you will see a red marker.  |\n");
        addstr("| To correct this typo, you may either use backspace or  |\n");
        addstr("| simply keep typing. The wrong character will be rep-   |\n");
        addstr("| laced by the correct character, as soon as you type    |\n");
        addstr("| the correct character.                                 |\n");
        addstr("|                                                        |\n");
        addstr("| To start typing, press any character. The time tracker |\n");
        addstr("| won't start until you type.                            |\n");
        addstr("|                                                        |\n");
        addstr("==========================================================\n");

        getch();
    }

    clear();
    endwin();
}

/*
    Ncurses reacts to any character input, i.e. also to character inputs that are no text
    characters (e.g. backspace, arrow keys, enter, etc.). Such characters should obviously
    not be treated as type-writer user input and thus, this function is designed to distinguish
    between printable and non-printable characters.
*/
bool is_valid_text_char(char c)
{
    const static array allowed_special_chars = {' ', '.', ',', '\'', 
    '!', '?', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '\\', '/', 
    '{', '[', ']', '}', '|', ':', ';', '<', '>', '~', '`'};

    bool c_valid_text_char = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
        || (c >= '0' && c <= '9');

    for(int i = 0; i < allowed_special_chars.size() && !c_valid_text_char; i++)
        c_valid_text_char = (c_valid_text_char || c == allowed_special_chars[i]);
        
    return c_valid_text_char;
}

/*
    This function concatenates a file's content over several lines into
    a single line and returns it as a string. It is being used to get the 
    sample-training text from a file.
*/
string read_sample_text(string file_location)
{
    ifstream istr(file_location);
    string current_line;
    string file_content="";

    while (getline(istr, current_line)) 
    {
        file_content += current_line;
    }
   
    return file_content;
}

/*
    This function saves typing statistics into a text file at
    a specific location.
*/
void write_typing_stats(typing_stats stats, string file_location)
{
    ofstream ostr;
    ostr.open(file_location);
    if(ostr.is_open())
    {
        ostr << "Typing training statistics:\n\tCharacters typed: " << stats.chars_typed
            << "\n\tMistakes made: " << stats.num_of_mistakes << "\n\tTime (sec.): "
            << stats.elapsed_time_sec << "\n\tTyping speed (characters / min.): " << stats.type_rate << endl;
        ostr.close();
    }
    else
        cout << "Could not save typing statistics in a text file due to an error." << endl;
}

/*
    This function runs the typing trainer and displays statistics after its termination.
*/
typing_stats run_typing_trainer(const string sample_text)
{
    initscr();

    // Here, we define how wide the output window is
    int window_length = 100;

    // We initialize and enable the color capability of the terminal
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_RED);

    // We define the windows and set up some graphical properties
    WINDOW *sample_text_win = newwin(3, window_length, 0, 0);
    WINDOW *input_text_win = newwin(3, window_length, 3, 0);
    WINDOW *statistic_info_win = newwin(3, window_length, 6, 0);
    box(sample_text_win, 0, 0);
    box(input_text_win, 0, 0);
    box(statistic_info_win, 0, 0);
    mvwprintw(sample_text_win, 0, 1, "Text to type");
    mvwprintw(input_text_win, 0, 1, "Your input");
    mvwprintw(statistic_info_win, 0, 1, "Statistics");
    mvwprintw(statistic_info_win, 1, 1, "Error Count: 0");
    mvwprintw(statistic_info_win, 1, window_length - 23, "Press 'Enter' to stop");

    refresh();
    wrefresh(sample_text_win);
    wrefresh(input_text_win);
    wrefresh(statistic_info_win);
    

    // noecho ensures that user typing is not automatically written into the terminal
    // (because we want to do that manually)
    noecho();

    // User's current typing position in text. E.g. position 4 for "Foo Bar" means 
    // that the user needs to input the character 'B' now
    int pos_in_sample_text = 0;

    // The numbers of wrong characters having been typed
    int num_of_typing_errors = 0;
    
    // Number of characters in the sample text
    int len_of_sample_text = sample_text.size();

    // How many characters we can display in a window (-2 because of the window borders)
    int displayable_text_len = window_length - 2;

    // The position of the first character that is currently being shown in the window
    // E.g. sample text: "ABCDEFGHIKL" -> If only "CDEFGHIJKL" can be shown in the window
    // (because more cannot fit), the variable takes value 2.
    int text_segment_start = 0;

    // The character that has last been input
    char input_char;

    // This will hold the time_point object of the time when the user typed the first letter
    chrono::steady_clock::time_point start_time;

    // Whether the user started typing: Used for measuring start_time (see above).
    bool user_started_typing = false;

    // Indicates whether the user wants to interrupt and end the training
    bool user_interrupted_input = false;


    // We run the typing trainer until we are at the end of the sample text
    while(pos_in_sample_text < len_of_sample_text && !user_interrupted_input)
    {
        // Compute which part of the string is currently displayed in the window
        string current_text_segment = sample_text.substr(text_segment_start, displayable_text_len);

        // Display the text to be shown (adding the trailing space is needed to avoid cosmetic issues)
        mvwprintw(sample_text_win, 1, 1, (current_text_segment + " ").c_str());
        wrefresh(sample_text_win);

        // Refresh the shown text in the input window
        mvwprintw(input_text_win, 1, 1, (current_text_segment.substr(0, pos_in_sample_text - text_segment_start)).c_str());
        wrefresh(input_text_win);

        // Read the user input from input, store it in input_char and check if the input was correct.
        // If it was incorrect, repeat until it's correct
        while((input_char = getch()) != sample_text[pos_in_sample_text])
        {
            // Measure the time when the user started typing
            if(!user_started_typing)
            {
                user_started_typing = true;
                start_time = chrono::steady_clock::now();
            }

            // Input was incorrect: Display a red box around the wrongly input character
            if(is_valid_text_char(input_char))
            {
                mvwprintw(input_text_win, 1, 1, current_text_segment.substr(0, pos_in_sample_text - text_segment_start).c_str());
                wattron(input_text_win, COLOR_PAIR(2));
                mvwaddch(input_text_win, 1, pos_in_sample_text - text_segment_start + 1, input_char);
                wattroff(input_text_win,COLOR_PAIR(2));
                wrefresh(input_text_win);
                num_of_typing_errors++;
                mvwprintw(statistic_info_win, 1, 1, ("Error Count: " + to_string(num_of_typing_errors)).c_str());
                wrefresh(statistic_info_win);
            }
            else if(input_char == KEY_ENTER)
            {
                user_interrupted_input = true;
                break;
            }
            else if(input_char == KEY_BACKSPACE)
            {
                mvwaddch(input_text_win, 1, pos_in_sample_text - text_segment_start + 1, ' '); 
                wmove(input_text_win, 1, pos_in_sample_text - text_segment_start + 1);
                wrefresh(input_text_win);
            }
            else
            {
                /*
                This is a workaround for an odd peculiarity of ncurses:
                Some special inputs (e.g. arrow keys, escape key, etc) are
                retrieved by calling getch() twice or thrice. The arrow key
                is thus not passed to getch() by one single character but by
                several characters that all need to be read. The issue is that
                we do not want to consider special inputs. Thus, when we encounter
                unwanted characters, we flush the whole character input queue 
                in order to not fetch "weird" character values in the next getch()
                call (that actually still belong to e.g. an input arrow key)
                */
                flushinp();
            }
            
        }

        // Measure the time when the user started typing
        if(!user_started_typing)
        {
            user_started_typing = true;
            start_time = chrono::steady_clock::now();
        }

        // This is a cosmetic fix that is needed
        mvwaddch(input_text_win, 1, pos_in_sample_text - text_segment_start + 1, ' '); 

        // When we finally input the correct char, we move on to the next
        if(!user_interrupted_input)
            pos_in_sample_text++;

        // In the beginning, the current input position will move from left to right.
        // At half of the window size, we stop moving the input position and move
        // the whole text instead
        if(pos_in_sample_text > displayable_text_len / 2)
            text_segment_start++;

        // After the last character of the text has been entered, we need to 
        // refresh the window again (this typically happens in the loop above)
        // but since we are at the end of the text, the loop won't execute anymore
        if(pos_in_sample_text == len_of_sample_text)
        {
            // Refresh the shown text in the input window
            mvwprintw(input_text_win, 1, 1, (current_text_segment.substr(0, pos_in_sample_text - text_segment_start + 1)).c_str());
            wrefresh(input_text_win);
        }
    }

    //calculate the user time depending on start and end time
    auto end_time = chrono::steady_clock::now();
    auto elapsed_time = int(chrono::duration_cast<chrono::seconds>(end_time - start_time).count());
    float chars_per_minute;
    if(elapsed_time > 0)
        chars_per_minute = pos_in_sample_text / elapsed_time * 60.;
    else
        chars_per_minute = 0;
    mvwprintw(statistic_info_win, 1, 20, ("Elapsed time: " + to_string(elapsed_time) + "sec.").c_str());
    mvwprintw(statistic_info_win, 1, 44, ("Characters / min.: " + to_string(chars_per_minute)).c_str());
    mvwprintw(statistic_info_win, 1, window_length - 23, "Press 'Enter' to exit");
    wrefresh(statistic_info_win);
    while(getch() != '\n');

    endwin();

    typing_stats training_stats;
    training_stats.chars_typed = pos_in_sample_text;
    training_stats.elapsed_time_sec = elapsed_time;
    training_stats.type_rate = chars_per_minute;
    training_stats.num_of_mistakes = num_of_typing_errors;

    return training_stats;
}


int main()
{
    show_start_menu();
    typing_stats training_stats = run_typing_trainer(read_sample_text("beginner.txt"));
    write_typing_stats(training_stats, "statistics.txt");
}