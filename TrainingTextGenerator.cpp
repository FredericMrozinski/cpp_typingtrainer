#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <random>
#include <exception>

const std::string SAMPLE_TEXTS_PATH = "sample_texts/";

std::string words[3][3][4];

std::string get_random_subject(int difficulty)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);

	return words[difficulty - 1][0][dist4(rng)];
}

std::string get_random_verb(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
	return words[difficulty - 1][1][dist4(rng)];
}


std::string get_random_object(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(0, 3);
	return words[difficulty - 1][2][dist4(rng)];
}

std::string get_sample_text(int difficulty, int num_of_sentences)
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

void read_sample_words_from_files()
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
            std::ifstream file(text_file[i][j]);
    
            if(file.is_open())
            {
                std::string word;
                for(int w = 0; w < 4; w++)
                {
                    std::getline(file, word);
                    words[i][j][w] = word;
                }   
            }
            else
            {
                throw std::runtime_error("At least one file cannot be opened");
            }

            file.close();
        }           
    }

    std::cout << "test";

}