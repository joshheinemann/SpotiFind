# SpotiFind - Music Recommendation System

SpotiFind is a C++-based music recommendation system that identifies similar songs using audio features. The system compares songs using both a brute-force k-Nearest Neighbors (kNN) approach and an optimized KD-Tree implementation to demonstrate differences in performance and scalability.

## 🚀 Features

- Parses and processes a large-scale dataset (~1M+ songs)
- Custom CSV parser to handle complex fields (lists, quotes, malformed rows)
- Song similarity based on audio features
- Two recommendation algorithms:
  - Brute-force kNN (baseline)
  - KD-Tree (optimized nearest neighbor search)
- Interactive command-line interface for user input
- Handles duplicate song names and resolves ambiguity
- Displays detailed metadata and audio characteristics

## 🧠 How It Works

Each song is represented as a feature vector derived from audio characteristics such as:

- Danceability
- Energy
- Valence
- Acousticness
- Instrumentalness
- Liveness
- Speechiness
- Key (normalized)
- Loudness (normalized)
- Tempo (normalized)

These features are used to compute similarity between songs using Euclidean distance.

Songs are then indexed into a KD-Tree to enable faster nearest neighbor searches compared to brute-force methods.

## ⚙️ Algorithms

### 1. Brute-force kNN
- Computes distance between the selected song and every other song
- Maintains top 5 closest songs using a max heap  
- Time complexity: **O(n)** per query :contentReference[oaicite:0]{index=0}

### 2. KD-Tree
- Organizes songs in a K-dimensional tree structure
- Uses recursive pruning to reduce search space  
- Average time complexity: **O(log n)** for queries :contentReference[oaicite:1]{index=1}

## 📂 Project Structure
