# Structure of TypingTrainer

The TypingTrainer follows the model-view-controller pattern to be as easily modifiable and extendable as possible. We briefly describe the structure, here. 

Note however that the header-files in the code contain very detailed and rich documentation, thus more information can be found within the files.

## View

`main.cpp` and `TypingTrainerUI.h/cpp` provide the User Interface. In fact, `main.cpp` only has the functionality to call functions from `TypingTrainerUI`.

`TypingTrainerUI`: From an external standpoint, the GUI can be started by first calling `init()` and then `show_program_menu()`. The remaining GUI flow will be called from within the functions itself. For further details, read `main.cpp` and `TypingTrainerUI.h`.

## Model

The model only consists of the classes `User` and `TypingStats`, as well as the code from `TrainingTextGenerator`. While `User` contains basic information about a user, it also contains a reference to a `TypingStats`-instance which houses detailed information on training progress for the user. Both classes allow for JSON import/export to conveniently save and retrieve states from disk. The view is able to retrieve information from `User` and `TypingStats`. The view can access instances of `User` using the controller (see below) and instances of `TypingStats` through the corresponding `User`.

`TrainingTextGenerator` provides randomly sampled training text in a simple syntactic structure.

## Controller

The controller consists of the classes `TypingTrainerSession` and `TypingStatsRecorder` and the file `utils.h/cpp`. `TypingTrainerSession` provides a very simple interface for a GUI to use the core functionality of the TypingTrainer. `TypingStatsRecorder` is part of the lower-level of the controller and does not need to be worked with from the GUI. Sometimes it's best to learn from examples, so here is a (generic) one for how to use `TypingTrainerSession`:

    // Reads all saved states from disk
    TypingTrainerSession::init();

    TypingTrainerSession session = TypingTrainerSession();

    // Select an example user for the training
    User* alice = TypingTrainerSession::users()->at(0);

    // Initialize the training
    run_typing_trainer(alice);

    // Get training text for rendering
    std::string text = session.training_text();

    // While we have not reached the end of the training
    while(training_running())
    {
        int pos_in_text = session.pos_in_training_text();

        // ... Render training text using a marker to the currently
        // expected character

        // Log the keystroke and see if it was correct or not
        if(char_typed(get_next_meaningful_keystroke()))
        { /* ... print happy face because correct char typed */ }
        else
        { /* ... print sad face because incorrect char typed */ }
    }

    std::shared_ptr<TypingStats> stats = session.get_training_stats();

    // ... print training stats

This is pretty much it! Have fun building your GUI! For more detailed information, see `TypingTrainerSession.h`.

`TypingStatsRecorder` can be considered, together with `utils`, simple helper method for functionality separation and cleaner code.