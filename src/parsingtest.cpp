#include <iostream>
#include "Dataset.h"
#include "Song.h"
#include "KNN.h"

int main() {
    Dataset dataset("data/tracks_features.csv");

    const std::vector<Song>& songs = dataset.getSongs();

    Song userpicked = songs[2727];

    std::cout << "User picked : " << userpicked.getName() << std::endl;

    std::vector<std::pair<double, Song>> results = getFiveClosestKNN(userpicked, songs);

    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "Song #" << i + 1 << std::endl;

        std::cout << "Name: " 
                  << results[i].second.getName() << std::endl;

        std::cout << "Artists: ";
        std::vector<std::string> artists = results[i].second.getArtists();

        for (size_t j = 0; j < artists.size(); j++) {
            std::cout << artists[j];
            if (j < artists.size() - 1) std::cout << ", ";
        }

        std::cout << std::endl;
        std::cout << "Distance: " << results[i].first << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    return 0;
}