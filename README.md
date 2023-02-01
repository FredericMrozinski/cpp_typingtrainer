# Typing-Trainer

This program is a small terminal based, simple yet extendable typing trainer. It's been developed for UNIX based systems but the core functionality could be adapted to other platforms as well, simply by rewriting the GUI.

This project is part of the voluntary assignments for the Advanced Programming class at TUM.

# Building and Prerequisites
## NCurses

The GUI is built upon the NCurses library, which enables more advanced I/O to the system terminal on UNIX based systems (Linux & MacOS). There are ways of getting NCurses to work on Windows but we have not experimented with those.

For the program to run, having Ncurses installed is required. You can easily do so by:

### Ubuntu

     sudo apt-get install libncurses5-dev libncursesw5-dev

### Fedora

    sudo yum install ncurses-devel

### MacOS (using Homebrew)

    brew install ncurses

## nlohmann-JSON

nlohmann-JSON is a C++ JSON parser library that we use in this program. Unfortunately, we did not manage to dynamically link to this library, so we ship this library within the repo and link it statically. This is not nice and we're still looking for a fix. Ideally, we would like to link to it dynamically.

## Building

To build the program, feel free to use the existing `CMakeLists.txt` file provided. For that, open a terminal session and navigate into the `build`-folder. From there you can run

    cmake ../src
    make

and enjoy the outcome (executable can be found in `bin`-folder!

# Project description from class-instructors  ✌️

Project idea for the Advanced Programming course by Anastasia Golovin anastasia.golovin@tum.de and Mykyta Smyrnov ge78daq@mytum.de. 

## Motivation
In this project, you will create a command line typing trainer, which will help to acquire or improve user's touch typing skills. The program has to be implemented completely in the command line interface of any binary-executable environment. Users can create different user accounts to save their progress. They can choose between several levers of difficulty, starting with the middle row on the basic level to the full layout on the advanced level.


## Sprint 1
### Goal:
Implement the main functionality of the type trainer: display predetermined sample text, process user input, collect, save and display statistics. 
### Definiton of "done"
- The ncurses library is used to create three windows in the terminal: one for sample text, one for user input and one for the error count.
- The program displays sample text in English. The text is loaded from a persistent storage in a .txt file.
- Current position is marked in the sample text. 
- As the user types, the program processes characters as they are typed (using the `getch()` function from the ncurses library). If the user enters a wrong character, the program marks the letter red in the sample text and increases the error count. 
- After each level, the score and the elapsed time are displayed.
- Progress is saved in a .txt file.
### Optional:
- Let the user re-type the whole sentence if she makes a typo. Add a short time delay so that characters typed immediately after the typo are not treated as an error.
- If the user did too many typos, she has to start the level over again. 

## Sprint 2
### Goal:
Add a menu and a possibility to create different accounts. Replace predetermined text by a clever text generator that can handle different difficulty levels. 
### Definiton of "done":
- A menu is shown to the user at the start of the program with the following elements: 
```
    | - new user = (fields: username, difficulty)
    | - delete user; 
    | - load user;
        | - show progress;
        | - change difficulty;
        | - clean progress; 
        | - start practicing; 
            | - back to menu
```
- The user can select between different difficulty levels (beginner, intermediate, advanced).
    - Beginner: lowercase letters from the middle row
    - Intermediate: lower- and uppercase letters from the middle and upper rows
    - Advanced: lower- and uppercase letters from all three rows, dot and comma 
- Use a fixed grammatical structure to generate sentences, but insert random words in runtime to construct a meaningful sentence.

### Optional:
- Offer multiple layouts in different languages
- Display the keyboard layout in the command line and mark the next key. 

## Sprint 3 
### Goal
Optimize performance of the software and tidy up the code to make it more readable
- Collect statistics about the behavior of the user, e.g., time interval between keystrokes, the frequency of errors for every character or combinations of characters. 
- Collect statistics about the lag of the software.
- Analyze performance and identify inefficient parts of the code. Apply optimization techniques to improve them. 
- Refactor the code to make it more readable and maintainable. Separate the functionality according to the model-view-controller model to make it possible to replace or extend individual modules, e.g., replace the command line interface with a web UI, without readjusting the whole code. 
### Definiton of "done":
- The user can see detailed statistics in the `show progress` menu: most problematic characters, errors per row, errors per finger, slowest letter combinations. 
- A file `performance.md` presents your observations from the performance analysis and describes optimization techniques you applied.
- The code follows the model-view-controller pattern. A file `structure.md` describes the logical structure of the program and gives instructions on how to add further functionality. 
### Optional:
- Spinning-up a web-server to move the input/output environment to the web over http and tcp websockets
- Add a web user interface
- Replace .txt-based storage with a sequalized (or not-sequalized) data base