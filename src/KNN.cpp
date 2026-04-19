#include "KNN.h"
#include <queue>
#include <utility>
#include <stdexcept>
#include <cmath>
#include <algorithm>

struct CompareDistance {
    bool operator()(const std::pair<double, int>& a,
                    const std::pair<double, int>& b) const {
        return a.first < b.first;
    }
};

double Distance(const Song& a, const Song& b) {
    const std::vector<double>& a_features = a.getFeatures();
    const std::vector<double>& b_features = b.getFeatures();

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

std::vector<std::pair<double, int>> getFiveClosestKNN(
    int chosenIndex,
    const std::vector<Song>& songs
) {
    std::priority_queue<
        std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        CompareDistance
    > maxheap;

    const Song& userpicked = songs[chosenIndex];

    for (int i = 0; i < static_cast<int>(songs.size()); i++) {
        if (i == chosenIndex) {
            continue;
        }

        double dist = Distance(userpicked, songs[i]);

        if (maxheap.size() < 5) {
            maxheap.push({dist, i});
        } else if (dist < maxheap.top().first) {
            maxheap.pop();
            maxheap.push({dist, i});
        }
    }

    std::vector<std::pair<double, int>> results;

    while (!maxheap.empty()) {
        results.push_back(maxheap.top());
        maxheap.pop();
    }

    std::reverse(results.begin(), results.end());
    return results;
}