#include <iostream>
#include <ncurses.h>
using namespace std;

/*
    This function will be called on program startup. It will offer the user to
    choose a difficulty level for the typing test.
*/
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

/*
    This function runs the typing trainer.
*/
void run_typing_trainer(string & sample_text);



int main(int argc, char ** argv)
{
    initscr();

    WINDOW *sample_text_win = newwin(3, 100, 0, 0);
    WINDOW *input_text_win = newwin(3, 100, 3, 0);
    WINDOW *statistic_info_win = newwin(3, 100, 6, 0);
    refresh();

    box(sample_text_win, 0, 0);
    box(input_text_win, 0, 0);
    box(statistic_info_win, 0, 0);

    mvwprintw(sample_text_win, 0, 1, "Text to type");
    mvwprintw(sample_text_win, 1, 1, "This is the sample text");
    mvwprintw(input_text_win, 0, 1, "Your input");
    mvwprintw(statistic_info_win, 0, 1, "Statistics");
    mvwprintw(statistic_info_win, 1, 1, "Here, we will show the statistics");

    wrefresh(sample_text_win);
    wrefresh(input_text_win);
    wrefresh(statistic_info_win);

    noecho();
    char one_length_str[2] = {0, 0};
    char c{};
    int currentPos = 1;

    while((c = getch()) != 'a')
    {
        one_length_str[0] = c;
        mvwprintw(input_text_win, 1, currentPos++, one_length_str);
        wrefresh(input_text_win);
    }

    endwin();
    return 0;
}