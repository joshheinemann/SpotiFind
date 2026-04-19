#ifndef KNN_H
#define KNN_H

#include <vector>
#include "Song.h"

double Distance(const Song& a, const Song& b);

std::vector<std::pair<double, Song>> getFiveClosestKNN(
    const Song& userpicked,
    const std::vector<Song>& songs
);

#endif