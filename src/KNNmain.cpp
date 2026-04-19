#include <vector>
#include <iostream>
#include <sstream>
#include "Dataset.h"
#include "KNN.h"
#include "UIHelpers.h"

int main() {
    Dataset dataset("data/tracks_features.csv");

    std::cout << std::endl;
    std::cout << "Welcome to SpotiFind, the music recommendation program!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    const std::vector<Song>& songs = dataset.getSongs();

    bool keepRunning = true;

    while (keepRunning) {
        int chosenIndex = promptUserForSong(dataset, songs);
        const Song& userPicked = songs[chosenIndex];

        std::vector<std::pair<double, int>> rawResults = getFiveClosestKNN(chosenIndex, songs);

        std::vector<int> resultIndices;
        for (const auto& result : rawResults) {
            resultIndices.push_back(result.second);
        }

        printRecommendations(userPicked, songs, resultIndices);
        printTopRecommendation(songs, resultIndices);

        if (askToViewData()) {
            viewData(songs, resultIndices);
        }

        keepRunning = askToContinue();
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Thank you for using SpotiFind!" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    return 0;
}