#ifndef KDTREE_H
#define KDTREE_H
#include <iostream>
#include <array>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int NUM_SONGS_OUTPUT = 5;
template <size_t K>
class KDTree {
private:
    // Node structure representing each point in the KDTree
    struct Node {
        // Point in K dimensions
        array<double, K> point;
        // Pointer to left child
        Node* left;
        // Pointer to right child
        Node* right;
        //stores index of song
        int songIndex;
        // Constructor to initialize a Node
        Node(const array<double, K>& pt, int idx) : point(pt), songIndex(idx), left(nullptr), right(nullptr) {}
    };

    Node* root; // Root of the KDTree

    // Recursive function to insert a point into the KDTree
    Node* insertRecursive(Node* node, const array<double, K>& point, int songIndex, int depth) {
        // Base case: If node is null, create a new node
        if (node == nullptr) return new Node(point, songIndex);

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            node->left = insertRecursive(node->left, point, songIndex, depth + 1);
        else
            node->right = insertRecursive(node->right, point, songIndex, depth + 1);

        return node;
    }

    // Recursive function to search for a point in the KDTree
    bool searchRecursive(Node* node, const array<double, K>& point, int depth) const {
        // Base case: If node is null, the point is not found
        if (node == nullptr) return false;

        // If the current node matches the point, return true
        if (node->point == point) return true;

        // Calculate current dimension (cd)
        int cd = depth % K;

        // Compare point with current node and decide to go left or right
        if (point[cd] < node->point[cd])
            return searchRecursive(node->left, point, depth + 1);
        else
            return searchRecursive(node->right, point, depth + 1);
    }
    //Recursive memory cleanup
    void freeTree(Node* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

    double distanceFormula(const array<double, K>& a, const array<double, K>& b) const {
        double dist = 0.0;
        for (size_t i = 0; i < K; i++) {
            double diff = a[i] - b[i];
            dist += diff * diff;
        }
        return dist;
    }

    void kNearestRecursive(Node* node,
                       const array<double, K>& query,
                       int depth,
                       int k,
                       priority_queue<pair<double, int>>& best) const {
        if (node == nullptr) return;

        int cd = depth % K;

        Node* nextBranch = nullptr;
        Node* otherBranch = nullptr;

        if (query[cd] < node->point[cd]) {
            nextBranch = node->left;
            otherBranch = node->right;
        } else {
            nextBranch = node->right;
            otherBranch = node->left;
        }

        kNearestRecursive(nextBranch, query, depth + 1, k, best);

        double dist = distanceFormula(query, node->point); //get distance of current point
        
        //update queue (current 5 closest)
        if(best.size() < NUM_SONGS_OUTPUT && dist!=0.0){
            best.push({dist, node->songIndex});
        }
        else if (dist < best.top().first && dist!=0.0) {
            best.pop();
            best.push({dist, node->songIndex});
        }

        // check if we need to search the other side
        //what this does is computes the minimum possible distance the other node could be away
        //if it is less than our current farthest node away in the heap, it doesn't search
        
        double diff = query[cd] - node->point[cd];
        double diffSquared = diff * diff;

        if ((int)best.size() < NUM_SONGS_OUTPUT || diffSquared < best.top().first) {
            kNearestRecursive(otherBranch, query, depth + 1, k, best);
        }
    }

public:
    // Constructor to initialize the KDTree with a null root
    KDTree() : root(nullptr) {}
    //Destructor to prevent memory leaks
    ~KDTree() {
        freeTree(root);
    }
    // Public function to insert a point into the KDTree
    void insert(const array<double, K>& point, int songIndex) {
        root = insertRecursive(root, point, songIndex, 0);
    }

    // Public function to search for a point in the KDTree
    bool search(const array<double, K>& point) const {
        return searchRecursive(root, point, 0);
    }

    vector<pair<double, int>> findKNearest(const array<double, K>& query, int k) const {
        priority_queue<pair<double, int>> best;
        kNearestRecursive(root, query, 0, k, best);

        vector<pair<double, int>> results;
        while (!best.empty()) {
            results.push_back(best.top());
            best.pop();
        }

        reverse(results.begin(), results.end());
        return results;
    }
};

#endif //KDTREE_H
