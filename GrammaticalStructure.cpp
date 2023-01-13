#include <string>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdio.h>
#include <random>
#include <exception>


std::string words[3][3][4];

std::string get_random_subject(int difficulty)
{
	std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,4);

	return words[difficulty - 1][0][dist4(rng)];
}

std::string get_random_verb(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,4);
	return words[difficulty - 1][1][dist4(rng)];
}


std::string get_random_object(int difficulty){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist4(1,4);
	return words[difficulty - 1][2][dist4(rng)];
}

std::string get_sample_text(int difficulty, int num_of_sentences)
{

    std::string sample_text = "";

    for(int i = 0; i < num_of_sentences; i++)
    {
        sample_text += get_random_subject(difficulty) + " " 
            + get_random_verb(difficulty) + " " 
            + get_random_object(difficulty) + " ";
    }

	return sample_text;
}

void read_sample_words_from_files()
{
    const std::string text_file[3][3] = 
    {
        {"subject_beginner.txt","verb_beginner.txt","object_beginner.txt"},
        {"subject_intermediate.txt","verb_intermediate.txt","object_intermediate.txt"},
        {"subject_advanced.txt","verb_advanced.txt","object_advanced.txt"}
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
        }           
    }

    std::cout << "test";

}