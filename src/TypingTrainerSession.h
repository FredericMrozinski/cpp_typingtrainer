/*************************************************

TypingTrainerSession.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 25, 2023

This file defines a class that can be used as an 
interface between the View/GUI and the Model/data.
It thus takes the functionality of the controller
and should be used by a developer when adapting
or rebuilding the View/GUI.

A TypingTrainerSession stands for one session of
typing training. Even though, this object can also be
used for a second training session, it is not adviced
to do so because that would add to the previously 
derived statistics. The object can of course live on
after the training session for statistics retrieval.

Its interface is aimed at being as simple as possible
such that the GUI does only have to use this class
for data modification. For data retrieval the developer
may, however, get information from a User-object 
and the TypingStats-object directly. The user object
is also retrieved from here.

Note that here, no assumptions about any GUI logic
are made, except that the Typing Trainer runs forward
only, i.e. there is no possibility of using and recording
backspaces through the text. Entering an incorrect
character will just increase the error count without
moving forward in the sample text until the correct
character has been entered.

To build a GUI for using this controller, it suffices
to understand the functions of this controller and 
the data provided by the User-class, the 
TypingStats-class and the interpretion of fingers and
keyboard-rows as given in utils.h.

**************************************************/

#ifndef _TYPING_TRAINER_SESSION
#define _TYPING_TRAINER_SESSION

#include <vector>
#include <memory>
#include <string>
#include "User.h"
#include "TypingStatsV2.h"
#include "TypingStatsRecorder.h"

class TypingTrainerSession
{

private:

    /*
        Contains all the users that are currently registered
        in this program. These can be written to and loaded
        from disk.

        This member is static as it won't change across multiple
        TypingTrainerSessions.

        SEE ALSO:
            write_users()
            read_users()
            users()
    */
    static std::shared_ptr<std::vector<User>> users_vec;

    /*
        Reads all users from disk. Is called during init().

        SEE ALSO:
            init()
    */  
    static void read_users();

    /*
        Each TypingTrainerSession uses a TypingStatsRecorder
        as a clean and convenient interface between this
        controller and TypingStats.
    */
    std::unique_ptr<TypingStatsRecorder> stats_recorder;

    /*
        The training text that the user will perform a training
        session on.
    */
    std::string _training_text;

    /*
        The position of the character in _training_text that is
        expected to be typed by the user next.
    */
    int _pos_in_training_text;

    /*
        A pointer to the user who performs this typing session.
    */
    User* current_user = nullptr;

    /*
        Used only internally. To abort the training from the GUI,
        use:

        SEE ALSO:
            abort_typing_training()

    */
    void end_training();

public:

    /*
        Gives access to the internally held vector of users.
        The GUI may modify this array directly (e.g. adding
        or removing a user). After modifications of this array
        or information about the user, be sure to call
        write_users() for the changes to be adapted to disk.
    */
    static std::shared_ptr<std::vector<User>> users();

    /*
        Initialized crucial information. Since it's static,
        it only needs to be called once, ideally during
        the initialization phase of the GUI.
    */
    static void init();

    /*
        Writes all users to disk for later retrieval. Should be
        called after every modification of the users()-array or
        a user's attributes.
    */
    static void write_users();

    /*
        This starts the typing training for a certain user.
        Calling this initializes the training text and a 
        TypingStatsRecorder. The typing training is then
        realized by calling char_typed(char) for every user
        input that is meaningful.

        SEE ALSO:
            char_typed(char)

        ARGS:
            User* user: Pointer to the user who prefers the 
                        typing training.
    */
    void run_typing_trainer(User* user);

    /*
        This method is the heart of the interface between View/GUI
        and program logic. After having called run_typing_trainer(...)
        for initialization, this method should be called after every
        meaningful keystroke by the user. A keystroke is meaningful if
        it represents a character that will be counted as an error. This
        excludes keystroke events like the arrow keys, backspace, function keys,
        etc.

        Since this method will also record user performance w.r.t. time,
        this method should be called with little latency after the keystroke
        to accurately measure the time between keystrokes.

        SEE ALSO:
            run_typing_trainer(User*)
            training_running()

        EXAMPLE USE:

            The very rough structure of using this method in a GUI could be
            something like:

                //- ------------------------------------------------
                User* alice = TypingTrainerSession::users()->at(0);
                run_typing_trainer(alice);

                while(training_running())
                {
                    if(char_typed(get_next_meaningful_keystroke()))
                        // print happy face because correct char typed
                    else
                        // print sad face because incorrect char typed
                }

                // Done with training, retrieve statistics
                // -------------------------------------------------

        ARGS:
            char c:     The meaningful char that the user input (which
                        may be an incorrect keystroke).

        RETURNS:
            bool:       Whether the input character matches the expected
                        character
    */
    bool char_typed(char c);

    /*
        This method indicates whether the training is (still) running,
        i.e. whether we still expect another char to be entered.

        SEE ALSO:
            char_typed(char)

        EXAMPLE:
            See documentation of char_typed(char)

        RETURNS:
            bool:       Whether we wait for another input.
    */
    bool training_running();

    /*
        Aborts the typing training before the user has finished typing
        all text.
    */
    void abort_typing_training();

    /*
        Trivial getter for _training_text. For more information,
        see documentation of _trianing_text.
    */
    std::string training_text();

    /*
        Trivial getter for _pos_in_training_text. For more information,
        see documentation of _pos_in_training_text.
    */
    int pos_in_training_text();

    /*
        Trivial getter for stats_recorder->get_typing_stats(). 
        For more information,  see documentation of 
        TypingStatsRecorder::get_typing_stats().
    */
    std::shared_ptr<TypingStats> get_training_stats();
};

#endif
