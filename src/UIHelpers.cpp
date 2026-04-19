#include "UIHelpers.h"
#include <iostream>

using namespace std;

// Print all artists for a song
void printArtists(const vector<string>& artists) {
    for (size_t i = 0; i < artists.size(); i++) {
        cout << artists[i];
        if (i < artists.size() - 1) {
            cout << ", ";
        }
    }
}

// Handle duplicate song name matches
int chooseSongFromMatches(const vector<Song>& songs, const vector<int>& matches) {
    if (matches.empty()) return -1;

    if (matches.size() == 1) return matches[0];

    while (true) {
        cout << "Multiple songs found with that name. Please choose one:" << endl;
        cout << "------------------------------------------------------" << endl;

        for (size_t i = 0; i < matches.size(); i++) {
            const Song& song = songs[matches[i]];

            cout << i + 1 << ". " << song.getName() << " - ";
            printArtists(song.getArtists());
            cout << endl;
        }

        cout << endl;
        cout << "Enter the number of the correct song: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice >= 1 && choice <= static_cast<int>(matches.size())) {
            return matches[choice - 1];
        }

        cout << "Invalid selection. Try again." << endl << endl;
    }
}

// Prompt user to enter a song
int promptUserForSong(const Dataset& dataset, const vector<Song>& songs) {
    while (true) {
        string songName;

        cout << "Please enter a song: " << endl;
        cout << "--------------------" << endl;
        getline(cin, songName);

        vector<int> matches = dataset.searchForSong(songName);

        if (matches.empty()) {
            cout << "Sorry, we couldn't find that song in our dataset." << endl;
            cout << "Please try again." << endl << endl;
            continue;
        }

        return chooseSongFromMatches(songs, matches);
    }
}

// Print recommendation list
void printRecommendations(const Song& userPicked,
                          const vector<Song>& songs,
                          const vector<int>& indices) {

    cout << endl;
    cout << "User picked: " << userPicked.getName() << endl;
    cout << endl;

    for (size_t i = 0; i < indices.size(); i++) {
        const Song& s = songs[indices[i]];

        cout << "Song #" << i + 1 << endl;
        cout << "Name: " << s.getName() << endl;

        cout << "Artists: ";
        printArtists(s.getArtists());
        cout << endl;

        cout << "------------------------" << endl;
    }
}

// Print top recommendation only
void printTopRecommendation(const vector<Song>& songs,
                            const vector<int>& indices) {

    if (indices.empty()) return;

    cout << endl;
    cout << "SpotiFind's top recommended song:" << endl;

    const Song& s = songs[indices[0]];

    cout << "Name: " << s.getName() << endl;

    cout << "Artists: ";
    printArtists(s.getArtists());
    cout << endl;

    cout << "------------------------" << endl << endl;
}

// Ask user if they want to continue
bool askToContinue() {
    while (true) {
        string answer;

        cout << endl;
        cout << "Would you like to search again? (y/n): " << endl;
        cout << "--------------------------------------" << endl;
        getline(cin, answer);

        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;

        cout << "Invalid input. Please enter y or n." << endl;
    }
}

// Ask user if they want to view detailed data
bool askToViewData() {
    while (true) {
        string answer;

        cout << endl;
        cout << "Would you like to view the recommended songs' data? (y/n)" << endl;
        cout << "--------------------------------------------------------" << endl;
        getline(cin, answer);

        if (answer == "y" || answer == "Y") return true;
        if (answer == "n" || answer == "N") return false;

        cout << "Invalid input. Please enter y or n." << endl;
    }
}

// Print detailed song data
void viewData(const vector<Song>& songs, const vector<int>& indices) {
    for (size_t i = 0; i < indices.size(); i++) {
        const Song& s = songs[indices[i]];

        cout << "Song #" << i + 1 << endl;
        cout << "Name: " << s.getName() << endl;

        cout << "Artists: ";
        printArtists(s.getArtists());
        cout << endl;

        cout << "Album: " << s.getAlbum() << endl << endl;

        cout << "Key: " << s.getKey() << endl;
        cout << "Mode: " << s.getMode() << endl;
        cout << "Duration (ms): " << s.getDurationMs() << endl;

        cout << "Danceability: " << s.getDanceability() << endl;
        cout << "Energy: " << s.getEnergy() << endl;
        cout << "Valence: " << s.getValence() << endl;
        cout << "Tempo: " << s.getTempo() << endl;

        cout << "Acousticness: " << s.getAcousticness() << endl;
        cout << "Instrumentalness: " << s.getInstrumentalness() << endl;
        cout << "Loudness: " << s.getLoudness() << endl;
        cout << "Speechiness: " << s.getSpeechiness() << endl;
        cout << "Liveness: " << s.getLiveness() << endl;

        cout << "------------------------" << endl << endl;
    }
}