#ifndef _TRAINING_TEXT_GENERATOR
#define _TRAINING_TEXT_GENERATOR

#include <string>

namespace TrainingTextGenerator
{
    void read_sample_words_from_files();
    
    std::string get_sample_text(int difficulty, int num_of_sentences);
}

#endif