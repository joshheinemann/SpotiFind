#include "Dataset.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cctype>
//This is a custom CSV file parser that I made for the specific dataset that we used:
//https://www.kaggle.com/datasets/rodolfofigueroa/spotify-12m-songs

//Normalizes a string by removing non-alphanumeric characters and converting to lowercase
//This ensures consistent matching for song titles
std::string normalizeString(const std::string& input) {
    std::string result;

    for (char c : input) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

//Parses one CSV row into individual fields while correctly handling quoted values
std::vector<std::string> Dataset::parseRow(const std::string& line) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        if (c == '"') {
            if (inQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } 
        else if (c == ',' && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } 
        else {
            field += c;
        }
    }

    fields.push_back(field);
    return fields;
}

//Removes quotes from a field if they are present
std::string trimQuotes(const std::string& s) {
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
        return s.substr(1, s.size() - 2);
    }
    return s;
}

//Parses a list. ex: ['Artist 1', 'Artist 2']
std::vector<std::string> Dataset::parseList(const std::string& field) {
    std::vector<std::string> result;

    size_t start = field.find('[');
    size_t end   = field.find(']');
    if (start == std::string::npos || end == std::string::npos)
        return result;

    std::string inner = field.substr(start + 1, end - start - 1);

    size_t pos = 0;
    while (pos < inner.size()) {
        size_t open = inner.find('\'', pos);
        if (open == std::string::npos) break;
        size_t close = inner.find('\'', open + 1);
        if (close == std::string::npos) break;

        result.push_back(inner.substr(open + 1, close - open - 1));
        pos = close + 1;
    }

    return result;
}

// Loads and parses the dataset from a CSV file.
// Each row is converted into a Song object and stored in a vector.
// Also builds a hash map for fast song name lookup.
Dataset::Dataset(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Could not open dataset file: " + filepath);

    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Dataset file is empty: " + filepath);

    int lineNumber = 1;
    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.empty()) continue;

        try {
            auto f = parseRow(line);
            for (std::string& field : f) {
                field = trimQuotes(field);
            }
            //Ensure row has expected number of columns
            if (f.size() != 24) {
                std::cerr << "Bad row " << lineNumber
                        << " got " << f.size() << " columns\n";
                std::cerr << "RAW: " << line << "\n";

                for (size_t i = 0; i < f.size(); i++) {
                    std::cerr << i << ": [" << f[i] << "]\n";
                }
                std::cerr << "------------------------\n";
                continue;
            }
            //Construct song object using parsed features
            songs.emplace_back(
                f.at(0),                                 // id
                f.at(1),                                 // name
                parseList(f.at(4)),                      // artists
                f.at(2),                                 // album
                std::stod(f.at(9)),                      // danceability
                std::stod(f.at(10)),                     // energy
                std::stod(f.at(18)),                     // valence
                std::stod(f.at(19)),                     // tempo
                std::stod(f.at(15)),                     // acousticness
                std::stod(f.at(16)),                     // instrumentalness
                std::stod(f.at(12)),                     // loudness
                std::stod(f.at(14)),                     // speechiness
                std::stod(f.at(17)),                     // liveness
                std::stoi(f.at(11)),                     // key
                std::stoi(f.at(13)),                     // mode
                static_cast<int>(std::stod(f.at(20)))    // duration_ms
            );
            // Store normalized song name -> index mapping for fast lookup.
            songmap[normalizeString(f.at(1))].push_back(songs.size()-1);

        } catch (const std::exception& e) {
            std::cerr << "Warning: Skipping malformed row " << lineNumber
                      << " (" << e.what() << ")\n";
        }
    }
}

const std::vector<Song>& Dataset::getSongs() const { return songs; }
int Dataset::size() const { return static_cast<int>(songs.size()); }

//since we are only able to use songs in our dataset, we must check that the song the user inputs is in our dataset.

//if the song the user inputs is found, return the vector of songs with that title. else, return an empty vector
//because multiple songs can have the same title, we are storing them in a vector
const std::vector<int> Dataset::searchForSong(const std::string& userinput) const{
    auto it = songmap.find(normalizeString(userinput));
    if (it != songmap.end()){
        return it->second;
    }
    else{
        return {};
    }
}