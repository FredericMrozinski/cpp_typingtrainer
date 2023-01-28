/*************************************************

TypingTrainerUI.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 25, 2023

This file encapsulates all functionality needed
to run the typing trainer in a terminal based
environment. The key to enabling this is the use
of the library 'ncurses', available for all UNIX
systems.

While this program is aimed at a terminal based
interaction, it can be easily adopted to feature
a different GUI-type. This is due to its structure
that separates GUI from TypingTrainer logic, fully.

**************************************************/

#ifndef _TYPING_TRAINER_UI
#define _TYPING_TRAINER_UI

#include <ncurses.h>
#include "TypingTrainerSession.h"

// Ncurses defines values for the enter and backspace key that
// do not work. Thus, we redefine their values to work on Linux machines.
// (Tested on Ubuntu & Fedora Linux)
#ifdef KEY_BACKSPACE
    #undef KEY_BACKSPACE
#endif
#ifdef KEY_ENTER
    #undef KEY_ENTER
#endif
#ifdef KEY_ESC
    #undef KEY_ESC
#endif
#define KEY_BACKSPACE 127
#define KEY_ENTER 10
#define KEY_ESC 27

namespace TypingTrainerUI
{
    /*
    This function triggers the necessary calls to read
    the program state from disk (users, statistics, etc)
    */
    void init();

    /*
        This function shows the main menu
    */
    void show_program_menu();

    void run_typing_trainer_session();
}


#endif