#include <iostream>

#include <ncurses.h>
int main() {
    initscr();  /* init ncurses */
    keypad(stdscr, TRUE);   /* get keyboard input */
    addstr("Press enter to exit.\n");
    while (10 != getch()) {}    /* 10 == enter */
    endwin();   /* end ncurses */
    return 0;
}