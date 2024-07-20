# Typing-Trainer in C++

This program is a small sample project with which I learned C++. It may also serve as insight into my coding style. This project is part of the voluntary assignments for the Advanced Programming class at TUM.

The program is a terminal based, simple yet extendable typing trainer. It's been developed for UNIX based systems but the core functionality could be adapted to other platforms as well, simply by rewriting the GUI.

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

and enjoy the outcome (executable can be found in `bin`-folder)!
