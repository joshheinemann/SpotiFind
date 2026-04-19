# SpotiFind - Music Recommendation System

SpotiFind is a C++-based music recommendation system that identifies similar songs using audio features. The project demonstrates both a brute-force k-Nearest Neighbors (kNN) approach and an optimized KD-Tree implementation for efficient similarity search on large-scale data.

---

## Overview

This project was built to explore how large music datasets can be used to generate recommendations based on song characteristics rather than user behavior.

Each song is represented as a feature vector derived from its audio attributes, allowing similarity to be computed mathematically.

The system supports efficient lookup and comparison across a dataset of over 1 million songs.

---

## Features

- Custom CSV parser for large, real-world datasets
- Handles complex fields such as:
  - Quoted strings with commas
  - Lists of artists (e.g., `['Artist1', 'Artist2']`)
- Song lookup using hash map (O(1) average time)
- Feature engineering and normalization for similarity comparison
- Two recommendation approaches:
  - Brute-force kNN
  - KD-Tree optimized nearest neighbor search
- Command-line interface for song selection and results display
- Handles duplicate song names through user selection

---

## Dataset

This project uses the following dataset:

https://www.kaggle.com/datasets/rodolfofigueroa/spotify-12m-songs

The dataset contains over 1 million Spotify tracks and includes both metadata and audio features.

To ensure robustness, malformed rows are detected and skipped during parsing.

---

## Feature Representation

Each song is converted into a numerical feature vector using:

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

These features are used to compute similarity using Euclidean distance.

---

## Algorithms

### Brute-force kNN

- Compares a selected song against all other songs in the dataset
- Maintains the top 5 closest matches using a max heap
- Time Complexity: O(n) per query

---

### KD-Tree

- Organizes songs into a K-dimensional tree structure
- Uses recursive pruning to reduce search space
- Average Time Complexity: O(log n) per query

---

## Key Design Decisions

- Implemented a custom CSV parser to handle real-world messy data instead of relying on libraries
- Used feature normalization to ensure fair distance calculations across different scales
- Stored song indices instead of full objects in the KD-Tree to reduce memory overhead
- Built a hash map for fast song name lookup and duplicate handling

---

## Project Structure

Dataset.h / Dataset.cpp      - CSV parsing and dataset management  
Song.h / Song.cpp            - Song representation and feature vectors  
KNN.h / KNN.cpp              - Brute-force nearest neighbor implementation  
KDTree.h                     - KD-Tree implementation  
KNNmain.cpp                  - kNN-based interface  
KDmain.cpp                   - KD-Tree-based interface  

---

## Future Improvements

- Add cosine similarity as an alternative metric
- Introduce feature weighting to prioritize certain attributes
- Benchmark performance between kNN and KD-Tree
- Integrate natural language search (e.g., “high energy workout songs”)
- Build a web interface using FastAPI

---

## Author

Joshua Heinemann  
Computer Science @ University of Florida
