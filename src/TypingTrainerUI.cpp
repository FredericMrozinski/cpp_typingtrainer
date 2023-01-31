#include "TypingTrainerUI.h"
#include <string>
#include <array>
#include "utils.h"

std::unique_ptr<TypingTrainerSession> typing_trainer_session;

void TypingTrainerUI::init()
{
    TypingTrainerSession::init();
}

void TypingTrainerUI::show_program_menu()
{
    initscr();

    // A menu page represents a menu that is currently being shown.
    int menu_page = 0;

    // The last character the user has entered
    char user_input = 0;

    // After a user has been loaded, we reference that user through
    // this pointer
    User* user_selected = nullptr;

    // Indicates whether the "show-statistics" section will show the statistics
    // of all prev runs or just of the previous run
    bool show_stats_of_last_run = false;

    // We do not want to warn the user that TypingStats will be deleted
    // when they first set their difficulty.
    bool first_set_of_difficulty = false;
    
    while(menu_page != 0 || user_input != '4')
    {
        clear();

        // Main menu page
        if(menu_page == 0)
        {
            addstr("=====================Typing Trainer=======================\n");
            addstr("Select from the following options by pressing a number-key: \n\n");
            addstr("(1) New user\n");
            addstr("(2) Delete user\n");
            addstr("(3) Load user and train\n");
            addstr("(4) Exit\n");
        }
        // Add user page
        else if(menu_page == 1)
        {
            if(TypingTrainerSession::users()->size() >= 8)
            {
                addstr("=====================Typing Trainer=======================\n");
                addstr("The maximum amount of users (8) is already met.\n");
                addstr("To add another user, please delete an existing user first.\n\n");
                addstr("(1) Go back");

                getch();

                menu_page = 0;
                continue;
            }
            addstr("=====================Typing Trainer=======================\n");
            addstr("To create a new user, first enter the new user name. To cancel, hit the 'ESC' key. \n\n");
            addstr("Username: ");
            std::string user_name = "";
            while((user_input = getch()) != KEY_ENTER && user_input != KEY_ESC)
            {
                if(user_input == KEY_BACKSPACE)
                {
                    if(user_name.size() > 0)
                        user_name.pop_back();
                }
                else
                    user_name.push_back(user_input);
            }
            if(user_input == KEY_ESC)
            {
                menu_page = 0;
                continue;
            }
            clear();

            User* new_user = new User(user_name);
            TypingTrainerSession::users()->push_back(*new_user);
            user_selected = new_user;

            first_set_of_difficulty = true;

            menu_page = 5;
            TypingTrainerSession::write_users();
            continue;
        }
        // Delete user page
        else if(menu_page == 2)
        {
            addstr("=====================Typing Trainer=======================\n");
            addstr("Select the user you want to delete:\n\n");
            int i = 0;
            for(; i < 9 && i < TypingTrainerSession::users()->size(); i++)
            {
                addstr(("(" + std::to_string(i + 1) + ") " 
                    + TypingTrainerSession::users()->at(i).user_name + "\n").c_str());
            }
            addstr(("(" + std::to_string(i + 1) + ") Go back").c_str());

            while((user_input = getch()) < '1' || user_input > ('1' + i))
            {
                getch();
            }

            // Delete the user from the array and from the heap
            if(user_input != '1' + i)
            {
                TypingTrainerSession::users()->erase(TypingTrainerSession::users()->begin() + user_input - '1');
                user_selected = nullptr;
            }

            menu_page = 0;
            TypingTrainerSession::write_users();
            continue;
        }
        // Load user page
        else if(menu_page == 3)
        {
            addstr("=====================Typing Trainer=======================\n");
            addstr("Select the user you want to load:\n\n");

            int i = 0;
            for(; i < 9 && i < TypingTrainerSession::users()->size(); i++)
            {
                addstr(("(" + std::to_string(i + 1) + ") " 
                    + TypingTrainerSession::users()->at(i).user_name + "\n").c_str());
            }
            addstr(("(" + std::to_string(i + 1) + ") Go back").c_str());

            while((user_input = getch()) < '1' || user_input > ('1' + i))
            {
                getch();
            }

            // Mark the selected user as selected if not selected 'Go back'
            if(user_input != '1' + i)
            {
                user_selected = &(TypingTrainerSession::users()->at(user_input - '1'));
                menu_page = 4;
                continue;
            }
            // If selected 'Go back'
            else
            {
                menu_page = 0;
                continue;
            }
            
        }
        // Show typing menu for a user
        else if(menu_page == 4)
        {
            addstr("=====================Typing Trainer=======================\n");
            addstr(("Hi, " + user_selected->user_name + ", what do you want to do?\n\n").c_str());
            addstr("(1) Show progress\n");
            addstr("(2) Change difficulty\n");
            addstr("(3) Clean progress\n");
            addstr("(4) Start practicing\n");
            addstr("(5) Go back to main menu\n");
        }
        // Change difficulty of user
        else if(menu_page == 5)
        {
            if(!first_set_of_difficulty)
            {
                addstr("=====================Typing Trainer=======================\n");
                addstr(("Hi, " + user_selected->user_name + ", changing the difficulty level causes all recorded statistics\n"
                    "of yours to be deleted.\n(1) Proceed   (9) Go back\n\n").c_str());

                while((user_input = getch()) != '1' && user_input != '9');

                if(user_input == '9')
                {
                    menu_page = 4;
                    continue;
                }

                clear();
            }
            else
                first_set_of_difficulty = false;

            addstr("=====================Typing Trainer=======================\n");
            addstr(("Hi, " + user_selected->user_name + ", enter the difficulty level you want to practice at.\n\n").c_str());
            addstr("(1) Easy, i.e. middle row key\n");
            addstr("(2) Intermediate, i.e. middle and top row keys\n");
            addstr("(3) Difficult, i.e. all keys\n");

        }
        // Show user progess
        else if(menu_page == 6)
        {
            int stats_page = 0;
            bool use_relative_units = false;
            user_input = 0;

            std::shared_ptr<TypingStats> stats_to_show;
            if(show_stats_of_last_run)
                stats_to_show = typing_trainer_session->get_training_stats();
            else
                stats_to_show = user_selected->user_typing_stats;

            do
            {
                if(user_input == '1')
                    stats_page = std::max(0, --stats_page);
                else if(user_input == '2')
                    stats_page = std::min(4, ++stats_page);
                else if(user_input == '3')
                    use_relative_units = !use_relative_units;

                clear();
                addstr("=====================Typing Trainer=======================\n");
                if(show_stats_of_last_run)
                    addstr("These are your typing statistics from the previous training session:\n");
                else
                    addstr(("Hi, " + user_selected->user_name + ", here are your overall statistics:\n").c_str());
                addstr("(1) <<   (2) >>   (3) abs/rel   (9) go to menu\n\n");

                switch (stats_page)
                {
                // Simple overview
                case 0:
                    addstr("Summarization:\n");
                    addstr(("Difficulty level: " + std::to_string(user_selected->get_difficulty()) + "\n").c_str());
                    addstr(("Total number of typed characters: " 
                        + std::to_string(stats_to_show->get_num_of_typed_chars()) + "\n").c_str());
                    addstr(("Total time typed (in seconds): " 
                        + std::to_string(stats_to_show->get_total_elapsed_time_ms() / 1000) + "\n").c_str());
                    addstr(("Total number of mistakes: " 
                        + std::to_string(stats_to_show->get_num_of_errors()) + "\n").c_str());
                    addstr(("Total typing rate (chars / min): " + float_to_prec((float) stats_to_show->get_num_of_typed_chars()
                        / (float) stats_to_show->get_total_elapsed_time_ms() * 6e4, 2) + "\n\n").c_str());

                    break;

                // Errors per finger
                case 1:
                    {
                        std::unique_ptr<std::map<int, float>> err_per_finger 
                            = stats_to_show->get_errors_per_finger(use_relative_units);
                        addstr("Errors for each finger:\n");
                        addstr(("Left index:  " + float_to_prec(err_per_finger->at(4), 2) 
                            + "\t\tRight index:  " + float_to_prec(err_per_finger->at(7), 2) + "\n").c_str());
                        addstr(("Left middle: " + float_to_prec(err_per_finger->at(3), 2) 
                            + "\t\tRight middle: " + float_to_prec(err_per_finger->at(8), 2) + "\n").c_str());
                        addstr(("Left ring:   " + float_to_prec(err_per_finger->at(2), 2) 
                            + "\t\tRight ring:   " + float_to_prec(err_per_finger->at(9), 2) + "\n").c_str());
                        addstr(("Left pinky:  " + float_to_prec(err_per_finger->at(1), 2) 
                            + "\t\tRight pinky:  " + float_to_prec(err_per_finger->at(10), 2) + "\n").c_str());
                        addstr(("Thumb: " + float_to_prec(err_per_finger->at(5), 2)+ "\n").c_str());
                    }
                        
                    break;

                // Errors per row
                case 2:
                    {
                        std::unique_ptr<std::map<int, float>> err_per_row 
                            = stats_to_show->get_errors_per_row(use_relative_units);
                        addstr("Errors for each row:\n");
                        addstr(("123...890: " + float_to_prec(err_per_row->at(1), 2) + "\n").c_str());
                        addstr(("QWE...IOP: " + float_to_prec(err_per_row->at(2), 2) + "\n").c_str());
                        addstr(("ASD...JKL: " + float_to_prec(err_per_row->at(3), 2) + "\n").c_str());
                        addstr(("ZXC...M,.: " + float_to_prec(err_per_row->at(4), 2) + "\n").c_str());
                        addstr(("Space    : " + float_to_prec(err_per_row->at(5), 2) + "\n").c_str());
                    }
                        
                    break;

                // Top 5 most problematic characters
                case 3:
                    {
                        std::unique_ptr<std::vector<std::pair<char, float>>> errors_sorted 
                            = stats_to_show->get_errors_for_char_sorted(use_relative_units);
                        addstr("Top 5 most problematic characters:\n");
                        for(int i = 0; i < 5; i++)
                        {
                            if(i < errors_sorted->size())
                            {
                                addstr((std::string("") + errors_sorted->at(i).first
                                    + ": " + float_to_prec(errors_sorted->at(i).second, 2) + "\n").c_str());
                            }
                            else
                            {
                                addstr("---\n");
                            }
                        }
                        
                    }
                        
                    break;

                // Top 5 slowest character combinations
                case 4:
                    {
                        std::unique_ptr<std::vector<std::tuple<char, char, float>>> letter_combinations 
                            = stats_to_show->get_duration_for_letter_combinations_sorted();
                        addstr("Top 5 slowest letter combination average time:\n");
                        for(int i = 0; i < 5; i++)
                        {
                            if(i < letter_combinations->size())
                            {
                                addstr((std::string("") + std::get<0>(letter_combinations->at(i)) + std::get<1>(letter_combinations->at(i))
                                    + ": " + float_to_prec(std::get<2>(letter_combinations->at(i)), 2) + "\n").c_str());
                            }
                            else
                            {
                                addstr("---\n");
                            }
                        }                        
                    }
                        
                    break;
                
                default:
                    addstr(("page: " + std::to_string(stats_page) + "\n").c_str());
                    break;
                }
            }
            while((user_input = getch()) != '9');

            show_stats_of_last_run = false;

            menu_page = 4;
            continue;
        }
        // Reset statistics
        else if(menu_page == 7)
        {
            user_selected->user_typing_stats->flush();

            addstr("=====================Typing Trainer=======================\n");
            addstr(("Hi, " + user_selected->user_name + ", your statistics have been reset.\n\n").c_str());

            addstr("Press any key to go back.");
            getch();

            menu_page = 4;
            TypingTrainerSession::write_users();
            continue;
        }
        // Run typing trainer
        else if(menu_page == 8)
        {
            addstr("=====================Typing Trainer=======================\n");
            addstr(("Hi, " + user_selected->user_name + ", when you're ready to start, press any key.\n\n").c_str());

            getch();

            typing_trainer_session = std::make_unique<TypingTrainerSession>();

            // Here, we start the typing trainer
            typing_trainer_session->run_typing_trainer(user_selected);
            run_typing_trainer_session();

            show_stats_of_last_run = true;
            
            // After the typing training, we want to write the user
            // statistics to disk.
            TypingTrainerSession::write_users();

            menu_page = 6;
            continue;
        }

        user_input = getch();

        /*
            Here we react to the user input on the menu. Indeed, partially this 
            has already happened above also but only for the "special" cases
            where the menu was more dynamic than just plain navigation.
        */
        if(menu_page == 0)
        {
            if(user_input >= '1' && user_input <= '3')
            {
                menu_page = user_input - '0';
            }
            else if(user_input == '4')
            {
                clear();
                endwin();
                exit(0);
            }
            user_input = 0;
        }
        else if(menu_page == 4)
        {
            if(user_input == '1')
                menu_page = 6;
            else if(user_input == '2')
                menu_page = 5;
            else if(user_input == '3')
                menu_page = 7;
            else if(user_input == '4')
                menu_page = 8;
            else if(user_input == '5')
            {
                menu_page = 0;
                user_selected = nullptr;
            }
        }
        else if(menu_page == 5)
        {
            if(user_input >= '1' && user_input <= '3')
            {
                user_selected->set_difficulty(user_input - '0');
                menu_page = 4;
                TypingTrainerSession::write_users();

            }
            
        }
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
    const static std::array allowed_special_chars = {' ', '.', ',', '\'', 
    '!', '?', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '\\', '/', 
    '{', '[', ']', '}', '|', ':', ';', '<', '>', '~', '`'};

    bool c_valid_text_char = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') 
        || (c >= '0' && c <= '9');

    for(int i = 0; i < allowed_special_chars.size() && !c_valid_text_char; i++)
        c_valid_text_char = (c_valid_text_char || c == allowed_special_chars[i]);
        
    return c_valid_text_char;
}

void TypingTrainerUI::run_typing_trainer_session()
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

    std::string sample_text = typing_trainer_session->training_text();
    
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
 
    // Compute which part of the string is currently displayed in the window
    std::string current_text_segment = sample_text.substr(text_segment_start, displayable_text_len);

    // Display the text to be shown (adding the trailing space is needed to avoid cosmetic issues)
    mvwprintw(sample_text_win, 1, 1, (current_text_segment + " ").c_str());
    wrefresh(sample_text_win);

    // Refresh the shown text in the input window
    mvwprintw(input_text_win, 1, 1, (current_text_segment.substr(0, 
        typing_trainer_session->pos_in_training_text() - text_segment_start)).c_str());
    wrefresh(input_text_win);

    while(typing_trainer_session->training_running())
    {
        // Compute which part of the string is currently displayed in the window
        std::string current_text_segment = sample_text.substr(text_segment_start, displayable_text_len);

        // Display the text to be shown (adding the trailing space is needed to avoid cosmetic issues)
        mvwprintw(sample_text_win, 1, 1, (current_text_segment + " ").c_str());
        wrefresh(sample_text_win);

        // Refresh the shown text in the input window
        mvwprintw(input_text_win, 1, 1, (current_text_segment.substr(0, typing_trainer_session->pos_in_training_text()
            - text_segment_start)).c_str());
        wrefresh(input_text_win);

        while(!is_valid_text_char(input_char = getch()))
        {
            if(input_char == KEY_ENTER)
            {
                typing_trainer_session->abort_typing_training();
                break;
            }
            // We do not have to report a backspace-event to the training session
            // as the training session does not move to the next char unless the
            // correct char was typed. This is therefore just a GUI feature that
            // gives the user the ability to "pretend" to use the backspace character
            // out of being used to it.
            else if(input_char == KEY_BACKSPACE)
            {
                mvwaddch(input_text_win, 1, typing_trainer_session->pos_in_training_text()
                        - text_segment_start + 1, ' '); 
                wmove(input_text_win, 1, typing_trainer_session->pos_in_training_text()
                        - text_segment_start + 1);
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

        // In case the user aborts the training, we need to break the outer
        // loop here, as we do not want the following code to be executed
        if(!typing_trainer_session->training_running())
        {
            break;
        }

        // If the correct char has been entered
        if(typing_trainer_session->char_typed(input_char))
        {
            // This is a cosmetic fix that is needed
            mvwaddch(input_text_win, 1, 
                typing_trainer_session->pos_in_training_text() - text_segment_start + 1, ' '); 

            // In the beginning, the current input position will move from left to right.
            // At half of the window size, we stop moving the input position and move
            // the whole text instead
            if(typing_trainer_session->pos_in_training_text() > displayable_text_len / 2)
                text_segment_start++;

            // After the last character of the text has been entered, we need to 
            // refresh the window again (this typically happens in the loop above)
            // but since we are at the end of the text, the loop won't execute anymore
            if(typing_trainer_session->pos_in_training_text() == len_of_sample_text)
            {
                // Refresh the shown text in the input window
                mvwprintw(input_text_win, 1, 1, 
                    (current_text_segment.substr(0, typing_trainer_session->pos_in_training_text() 
                    - text_segment_start + 1)).c_str());
                wrefresh(input_text_win);
            }
        }
        else
        {
            mvwprintw(input_text_win, 1, 1, current_text_segment.substr(0, 
                typing_trainer_session->pos_in_training_text() - text_segment_start).c_str());
            wattron(input_text_win, COLOR_PAIR(2));
            mvwaddch(input_text_win, 1, 
                typing_trainer_session->pos_in_training_text() - text_segment_start + 1, input_char);
            wattroff(input_text_win,COLOR_PAIR(2));
            wrefresh(input_text_win);
            mvwprintw(statistic_info_win, 1, 1, ("Error Count: " + std::to_string(
                typing_trainer_session->get_training_stats()->get_num_of_errors())).c_str());
            wrefresh(statistic_info_win);
        }
    }

    //calculate the user time depending on start and end time
    float chars_per_minute;
    int elapsed_time_sec = typing_trainer_session->get_training_stats()->get_total_elapsed_time_ms() / 1000;
    if(elapsed_time_sec > 0)
        chars_per_minute = typing_trainer_session->get_training_stats()->get_num_of_typed_chars()
            / elapsed_time_sec * 60.;
    else
        chars_per_minute = 0;
    mvwprintw(statistic_info_win, 1, 20, ("Elapsed time: " + std::to_string(elapsed_time_sec) + "sec.").c_str());
    mvwprintw(statistic_info_win, 1, 44, ("Characters / min.: " + std::to_string(chars_per_minute)).c_str());
    mvwprintw(statistic_info_win, 1, window_length - 23, "Press 'Enter' to exit");
    wrefresh(statistic_info_win);
    while(getch() != '\n');

    endwin();
}

