#include <iostream>
#include <vector>
#include <array>
#include "Dataset.h"
#include "Song.h"
#include "KDTree.h"

#include <vector>
#include <iostream>
#include <sstream>
#include "Dataset.h"
#include "KNN.h"

const size_t FEATURE_COUNT = 10;

array<double, FEATURE_COUNT> songToPoint(const Song& song) {
    vector<double> features = song.getFeatures();

    array<double, FEATURE_COUNT> point{};
    for (size_t i = 0; i < FEATURE_COUNT; i++) {
        point[i] = features[i];
    }

    return point;
}

void printArtists(const std::vector<std::string>& artists) { //prints all the artists of the song
    for (size_t i = 0; i < artists.size(); i++) {
        std::cout << artists[i];
        if (i < artists.size() - 1) {
            std::cout << ", ";
        }
    }
}

int chooseSongFromMatches(const std::vector<Song>& songs, const std::vector<int>& matches) {
    if (matches.empty()) {
        return -1;
    }

    if (matches.size() == 1) {
        return matches[0];
    }

    while (true) {
        std::cout << "Multiple songs found with that name. Please choose one:" << std::endl;
        std::cout << "------------------------------------------------------" << std::endl;

        for (size_t i = 0; i < matches.size(); i++) {
            const Song& song = songs[matches[i]];

            std::cout << i + 1 << ". " << song.getName() << " - ";

            const std::vector<std::string>& artists = song.getArtists();
            for (size_t j = 0; j < artists.size(); j++) {
                std::cout << artists[j];
                if (j < artists.size() - 1) {
                    std::cout << ", ";
                }
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Enter the number of the correct song: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        if (choice >= 1 && choice <= static_cast<int>(matches.size())) {
            return matches[choice - 1];
        }

        std::cout << "Invalid selection. Try again." << std::endl;
        std::cout << std::endl;
    }
}

int promptUserForSong(const Dataset& dataset, const std::vector<Song>& songs) {
    while (true) {
        std::string songName;

        std::cout << "Please enter a song: " << std::endl;
        std::cout << "--------------------" << std::endl;
        std::getline(std::cin, songName);

        std::vector<int> matches = dataset.searchForSong(songName);

        if (matches.empty()) {
            std::cout << "Sorry, we couldn't find that song in our dataset." << std::endl;
            std::cout << "Please try again." << std::endl;
            std::cout << std::endl;
            continue;
        }

        return chooseSongFromMatches(songs, matches);
    }
}

void printRecommendations(const Song& userPicked,
                          const std::vector<Song>& songs,
                          const std::vector<std::pair<double, int>>& results) {

    std::cout << std::endl;
    std::cout << "User picked: "
              << userPicked.getName() << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < results.size(); i++) {
        int songIndex = results[i].second;

        std::cout << "Song #" << i + 1 << std::endl;

        std::cout << "Name: "
                  << songs[songIndex].getName() << std::endl;

        std::cout << "Artists: ";
        printArtists(songs[songIndex].getArtists());
        std::cout << std::endl;

        std::cout << "------------------------" << std::endl;
    }
}

void top(const std::vector<Song>& songs, const std::vector<std::pair<double, int>>& results){
  std::cout << "SpotiFind's top recommedned song: " << std::endl;
    std::cout << "Name: " << songs[results[0].second].getName() << std::endl;

    std::cout << "Artists: ";
    printArtists(songs[results[0].second].getArtists());
    std::cout << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << std::endl;
  }

bool askToContinue() {
    while (true) {
        std::string answer;

        std::cout << std::endl;
        std::cout << "Would you like to search again? (y/n): " << std::endl;
        std::cout << "--------------------------------------" << std::endl;
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y") {
            return true;
        }

        if (answer == "n" || answer == "N") {
            return false;
        }

        std::cout << "Invalid input. Please enter y or n." << std::endl;
    }
}
bool askToViewData() {
    while (true) {
        std::string answer;

        std::cout << std::endl;
        std::cout << "Would you like to view our recommednded songs' data? (y/n)" << std::endl;
        std::cout << "----------------------------------------------------" << std::endl;
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y") {
            return true;
        }

        if (answer == "n" || answer == "N") {
            return false;
        }

        std::cout << "Invalid input. Please enter y or n." << std::endl;
    }
}
void viewData(const std::vector<Song>& songs, const std::vector<std::pair<double, int>>& results){
    for (size_t i = 0; i < results.size(); i++) {
        int songIndex = results[i].second;
        std::cout << "Song #" << i + 1 << std::endl;
        std::cout << "Name: " << songs[songIndex].getName() << std::endl;

        std::cout << "Artists: ";
        printArtists(songs[songIndex].getArtists());
        std::cout << std::endl;

        std::cout << "Album: " << songs[songIndex].getAlbum() << std::endl;

        std::cout << std::endl;

        std::cout << "Key: " << songs[songIndex].getKey() << std::endl;

        std::cout << "Mode: " << songs[songIndex].getMode() << std::endl;

        std::cout << "Duration (ms): " << songs[songIndex].getDurationMs() << std::endl;

        std::cout << "Danceability: " << songs[songIndex].getDanceability() << std::endl;


        std::cout << "Energy: " << songs[songIndex].getEnergy() << std::endl;

        std::cout << "Valence: " << songs[songIndex].getValence() << std::endl;

        std::cout << "Tempo: " << songs[songIndex].getTempo() << std::endl;

        std::cout << "Acousticness: " << songs[songIndex].getAcousticness() << std::endl;

        std::cout << "Instrumentalness: " << songs[songIndex].getInstrumentalness() << std::endl;

        std::cout << "Loudness: " << songs[songIndex].getLoudness() << std::endl;

        std::cout << "Speechiness: " << songs[songIndex].getSpeechiness() << std::endl;

        std::cout << "Liveness: " << songs[songIndex].getLiveness() << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    Dataset dataset("data/tracks_features.csv");

    std::cout << "Welcome to SpotiFind, the music recommendation program!" << std::endl;
    std::cout << "------------------------------------------------------" << std::endl;

    const std::vector<Song>& songs = dataset.getSongs();

    KDTree<FEATURE_COUNT> tree;

    for(int i = 0; i < songs.size(); i++){
        tree.insert(songToPoint(songs[i]), static_cast<int>(i));
    }

    bool keepRunning = true;
    bool view = false;

    while (keepRunning) {
        int chosenIndex = promptUserForSong(dataset, songs);
        const Song& userPicked = songs[chosenIndex];

        array<double, FEATURE_COUNT> queryPoint = songToPoint(userPicked);

        vector<pair<double, int>> results = tree.findKNearest(queryPoint, 5);
        
        printRecommendations(userPicked, songs, results);

        top(songs, results);

        view = askToViewData();

        if (view) {
            viewData(songs, results);
        }

        keepRunning = askToContinue();
    }

    std::cout << std::endl;
    std::cout << "Thank you for using SpotiFind!" << std::endl;
    std::cout << "-----------------------------" << std::endl;

    return 0;
}