//this class will read and parse the song data from our data taken from kaggle
//takes the CSV file and creates song objects
//initially we will store all of the songs inside of a vector, then transfer to KD tree

#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Song.h"

class Dataset {
private:
    std::vector<Song> songs; //will store all of the songs in our dataset in a vector
    std::unordered_map<std::string, std::vector<int>> songmap; //will use this for looking to see if a song is in the dataset O(1) avg
    std::vector<std::string> parseRow(const std::string& line); //used in parsing
    std::vector<std::string> parseList(const std::string& field); //used in parsing

public:
    explicit Dataset(const std::string& filepath); //constructor (parses)

    Dataset();
    
    const std::vector<Song>& getSongs() const; //returns our song vector
    int size() const;

    const std::vector<int> searchForSong(const std::string& userinput) const; //used when a user inputs a song
};