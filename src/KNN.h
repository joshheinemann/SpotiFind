#ifndef KNN_H
#define KNN_H

#include <vector>
#include "Song.h"

double Distance(const Song& a, const Song& b);

std::vector<std::pair<double, int>> getFiveClosestKNN(
    int chosenIndex,
    const std::vector<Song>& songs
);

#endif