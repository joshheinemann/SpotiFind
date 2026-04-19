#include <iostream>
#include <vector>
#include <array>
#include "Dataset.h"
#include "Song.h"
#include "KDTree.h"
#include "UIHelpers.h"

const size_t FEATURE_COUNT = 10;

std::array<double, FEATURE_COUNT> songToPoint(const Song& song) {
    const std::vector<double>& features = song.getFeatures();

    std::array<double, FEATURE_COUNT> point{};
    for (size_t i = 0; i < FEATURE_COUNT; i++) {
        point[i] = features[i];
    }

    return point;
}

int main() {
    Dataset dataset("data/tracks_features.csv");

    std::cout << "Welcome to SpotiFind, the music recommendation program!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    const std::vector<Song>& songs = dataset.getSongs();

    KDTree<FEATURE_COUNT> tree;

    for (int i = 0; i < static_cast<int>(songs.size()); i++) {
        tree.insert(songToPoint(songs[i]), i);
    }

    bool keepRunning = true;

    while (keepRunning) {
        int chosenIndex = promptUserForSong(dataset, songs);
        const Song& userPicked = songs[chosenIndex];

        std::array<double, FEATURE_COUNT> queryPoint = songToPoint(userPicked);
        std::vector<std::pair<double, int>> rawResults = tree.findKNearest(queryPoint, 5);

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
    }

    std::cout << std::endl;
    std::cout << "Thank you for using SpotiFind!" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    return 0;
}