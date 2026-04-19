#include "Dataset.h"
#include "Song.h"
#include <queue>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <algorithm>

struct CompareDistance {
    bool operator()(const std::pair<double, Song>& a,
                    const std::pair<double, Song>& b) const {
        return a.first < b.first;
    }
};

double Distance(const Song& a, const Song& b) {                 //euclidian distance
    std::vector<double> a_features = a.getFeatures();
    std::vector<double> b_features = b.getFeatures();

    if (a_features.size() != b_features.size()) {
        throw std::invalid_argument("Songs must have same number of features");
    }

    double sum = 0.0;

    for (size_t i = 0; i < a_features.size(); i++) {
        double diff = a_features[i] - b_features[i];
        sum += diff * diff;
    }

    return std::sqrt(sum);
}

std::vector<std::pair<double, Song>> getFiveClosestKNN(const Song& userpicked, const std::vector<Song>& songs){      
    std::priority_queue<
        std::pair<double, Song>,
        std::vector<std::pair<double, Song>>,
        CompareDistance
    > maxheap; // will use a maxheap to store the 5 most similar songs

    //loop through all of the songs in the dataset. if current song is closer than any of the current 5 in the dataset,
    //add it and remove the one that is farthest away (top of maxheap)
    for(const Song& s : songs){
        if(s.getId() == userpicked.getId()){continue;}

        double dist = Distance(userpicked, s);

        if(maxheap.size() < 5){
            maxheap.push({dist, s});
        }
        else if(dist < maxheap.top().first){
            maxheap.pop();
            maxheap.push({dist, s});
        }
    }

    std::vector<std::pair<double, Song>> results;

    while (!maxheap.empty()) {
        results.push_back(maxheap.top());
        maxheap.pop();
    }

    std::reverse(results.begin(), results.end());

    return results;
    
}