#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <string>
using namespace std;



/*
    This function will be called on program startup. It will offer the user to
    choose a difficulty level for the typing test.
*/

// char *difficulty[]={
//     "Easy",
//     "Middle",
//     "Difficult"
// };

void show_start_menu();


/*
    After the user selected a difficulty from the start menu, this function will
    be called and prepares all necessary data to later run the typing test.
    The necessary data is:
        - The sample typing text that is being read from file depending on the
          difficulty
    
    Parameter:
        - difficulty: 0 - easy, 1 - medium, 2 - hard

    Returns:
        - string: The sample string that is being read from the text file, depending
          on the difficulty.
*/
string init_typing_trainer(int difficulty);

bool is_valid_text_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
    || c == '.' || c == ',' || c == ' ';
}

/*
    This function runs the typing trainer.
*/
void run_typing_trainer(const string sample_text)
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
    WINDOW *choose_difficulty=newwin(3, window_length,9,0 );
    box(sample_text_win, 0, 0);
    box(input_text_win, 0, 0);
    box(statistic_info_win, 0, 0);
    box(choose_difficulty,0,0);
    mvwprintw(sample_text_win, 0, 1, "Text to type");
    mvwprintw(input_text_win, 0, 1, "Your input");
    mvwprintw(statistic_info_win, 0, 1, "Statistics");
    mvwprintw(statistic_info_win, 1, 1, "Here, we will show the statistics");
    mvwprintw(choose_difficulty,0,1,"choose difficulty");
    //mvwprintw(choose_difficulty,1,1,difficulty[0]);

    refresh();
    wrefresh(sample_text_win);
    wrefresh(input_text_win);
    wrefresh(statistic_info_win);
    wrefresh(choose_difficulty);

    // noecho ensures that user typing is not automatically written into the terminal
    // (because we want to do that manually)
    noecho();

    // User's current typing position in text. E.g. position 4 for "Foo Bar" means 
    // that the user needs to input the character 'B' now
    int pos_in_sample_text = 0;
    
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

    // We run the typing trainer until we are at the end of the sample text
    while(text_segment_start < len_of_sample_text)
    {
        // Compute which part of the string is currently displayed in the window
        string current_text_segment = sample_text.substr(text_segment_start, displayable_text_len);

        // Display the text to be shown
        mvwprintw(sample_text_win, 1, 1, current_text_segment.c_str());
        wrefresh(sample_text_win);

        // Refresh the shown text in the input window
        mvwprintw(input_text_win, 1, 1, (current_text_segment.substr(0, pos_in_sample_text - text_segment_start)).c_str());
        wrefresh(input_text_win);

        // Read the user input from input, store it in input_char and check if the input was correct.
        // If it was incorrect, repeat until it's correct
        while((input_char = getch()) != sample_text[pos_in_sample_text])
        {
            // Input was incorrect: Display a red box around the wrongly input character
            if(is_valid_text_char(input_char))
            {
                mvwprintw(input_text_win, 1, 1, current_text_segment.substr(0, pos_in_sample_text - text_segment_start).c_str());
                wattron(input_text_win, COLOR_PAIR(2));
                mvwaddch(input_text_win, 1, pos_in_sample_text - text_segment_start + 1, input_char);
                wattroff(input_text_win,COLOR_PAIR(2));
                wrefresh(input_text_win);
            }
        }

        // This is a cosmetic fix that is needed
        mvwaddch(input_text_win, 1, pos_in_sample_text - text_segment_start + 1, ' '); 

        // When we finally input the correct char, we mve on to the next
        pos_in_sample_text++;

        // In the beginning, the current input position will move from left to right.
        // At half of the window size, we stop moving the input position and move
        // the whole text instead
        if(pos_in_sample_text > displayable_text_len / 2)
            text_segment_start++;
    }    

    endwin();
}



int main()
{
    ifstream is("beginner.txt");
    string line;
    string file_content="";

    while (getline(is, line)) {
        file_content+=line;
    }
    
    
    run_typing_trainer(file_content);
}