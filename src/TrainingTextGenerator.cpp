#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <random>
#include <exception>

#include "TrainingTextGenerator.h"

/*

    This file takes care of generating a simple sample text for three different
    levels of difficulty (1 - easy, 2 - intermediate, 3 - advanced). It generates
    sentences from words specified across several files. The sentences take the general
    form of Subject-Verb-Object and are randomly sampled. 

    The idea of using multiple files for storing the words is indeed not ideal - instead,
    a more complex syntax should be used to only use one file (e.g. JSON). However,
    for time reasons, we were not able to work this out that way.

    Note that our sample word choice is to be improved - especially for easy sentences. It
    would be far fetched to regard those as 'meaningful' sentences. Better go looking for those
    in the advanced level ;)
*/


const std::string SAMPLE_TEXTS_PATH = "../res/sample_texts/";

/*
    Stores all sample words/phrases for all difficulties and sentence functions.

    First dimension: Difficulty
    Second dimension: 0 - Subject, 1 - Verb, 2 - Object
    Fourth dimension: Different words, phrases. We limited ourselves down to 4, though
                      this number can be changed (and must of course be adapted in the files).
*/
std::string sample_phrases[3][3][4];

// Returns a random subject phrase for a given difficulty
std::string get_random_subject(int difficulty)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);

	return sample_phrases[difficulty - 1][0][dist4(rng)];
}

// Returns a random verb phrase for a given difficulty
std::string get_random_verb(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
	return sample_phrases[difficulty - 1][1][dist4(rng)];
}

// Returns a random object phrase for a given difficulty
std::string get_random_object(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
	return sample_phrases[difficulty - 1][2][dist4(rng)];
}

// Generates several sentences in the form subject-verb-object for 
// a given difficulty
std::string TrainingTextGenerator::get_sample_text(int difficulty, int num_of_sentences)
{

    std::string sample_text = "";

    for(int i = 0; i < num_of_sentences; i++)
    {
        sample_text += get_random_subject(difficulty) + " " 
            + get_random_verb(difficulty) + " " 
            + get_random_object(difficulty);
        if(i < num_of_sentences - 1)
            sample_text += ' ';
    }

	return sample_text;
}

// This function reads the sample phrases/words from the file and
// places them into the array sample_phrases.
void TrainingTextGenerator::read_sample_words_from_files()
{
    std::string text_file[3][3] = 
    {
        {
            SAMPLE_TEXTS_PATH + "subject_beginner.txt", 
            SAMPLE_TEXTS_PATH + "verb_beginner.txt", 
            SAMPLE_TEXTS_PATH + "object_beginner.txt"
        },
        {
            SAMPLE_TEXTS_PATH + "subject_intermediate.txt",
            SAMPLE_TEXTS_PATH + "verb_intermediate.txt",
            SAMPLE_TEXTS_PATH + "object_intermediate.txt"
        },
        {
            SAMPLE_TEXTS_PATH + "subject_advanced.txt",
            SAMPLE_TEXTS_PATH + "verb_advanced.txt",
            SAMPLE_TEXTS_PATH + "object_advanced.txt"
        }
    };

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            std::ifstream istr(text_file[i][j]);
    
            if(istr.is_open())
            {
                std::string word;
                for(int w = 0; w < 4; w++)
                {
                    std::getline(istr, word);
                    sample_phrases[i][j][w] = word;
                }   
            }
            else
            {
                throw std::runtime_error("At least one file cannot be opened");
            }

            istr.close();
        }           
    }

}