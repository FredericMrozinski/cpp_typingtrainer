/*************************************************

TrainingTextGenerator.h
Authors: Frederic Mrozinski, Quteiba Alsalaa
Date: Jan 26, 2023

This file enables random training text generation.
The text generation is based on three possible difficulty
levels (1 - easy, 2 - intermediate, 3 - hard) and
randomly samples subjects, verbs and objects to
create syntatically "useful" sentences (by all means
not semantically useful :D). The implementation
of this file gets those word subject, verb and object
samples from several files.

**************************************************/

#ifndef _TRAINING_TEXT_GENERATOR
#define _TRAINING_TEXT_GENERATOR

#include <string>

namespace TrainingTextGenerator
{
    /*
        Reads the sample words form disk and
        makes them available for later sampling.
    */
    void read_sample_words_from_files();
    
    /*
        Samples num_of_sentences many sentences
        of the form subject-verb-object to match
        a certain difficulty-level.

        ARGS:
            int difficulty: 1 - easy, 2 - intermediate, 3 - hard
            int num_of_sentences:
                            The amount of sentences that the sample-
                            text is to be composed of.

        RETURNS:
            std::string:    The sample text that the user can train on.
    */
    std::string get_sample_text(int difficulty, int num_of_sentences);
}

#endif