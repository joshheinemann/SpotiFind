#ifndef UIHELPERS_H
#define UIHELPERS_H

#include <vector>
#include <string>
#include "Dataset.h"
#include "Song.h"

void printArtists(const std::vector<std::string>& artists);

int chooseSongFromMatches(const std::vector<Song>& songs, const std::vector<int>& matches);

int promptUserForSong(const Dataset& dataset, const std::vector<Song>& songs);

bool askToContinue();

bool askToViewData();

void viewData(const std::vector<Song>& songs, const std::vector<int>& indices);

void printRecommendations(const Song& userPicked, const std::vector<Song>& songs, const std::vector<int>& indices);

void printTopRecommendation(const std::vector<Song>& songs, const std::vector<int>& indices);

#endif