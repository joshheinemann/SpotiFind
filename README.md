# SpotiFind - Music Recommendation System

SpotiFind is a C++-based music recommendation system that identifies similar songs using audio features. The project implements both a brute-force k-Nearest Neighbors (kNN) algorithm and an optimized KD-Tree to compare performance and scalability on large datasets.

---

## Overview

This project explores how content-based recommendation systems can be built using real-world music data.

Each song is represented as a numerical feature vector derived from its audio characteristics. These vectors are then used to compute similarity between songs using distance-based methods.

The system is designed to handle large-scale datasets and demonstrates both naive and optimized approaches to nearest neighbor search.

---

## Features

- Custom CSV parser for large, real-world datasets
- Handles complex fields such as:
  - Quoted text with commas
  - Lists of artists (e.g., `['Artist1', 'Artist2']`)
- Efficient song lookup using hash map (O(1) average)
- Feature engineering and normalization for similarity comparison
- Two recommendation algorithms:
  - Brute-force kNN (baseline)
  - KD-Tree optimized nearest neighbor search
- Modular architecture with separation of concerns:
  - Dataset layer
  - Algorithm layer
  - UI layer
- Command-line interface with duplicate song handling

---

## Dataset

This project uses the following dataset:

https://www.kaggle.com/datasets/rodolfofigueroa/spotify-12m-songs

The dataset contains over 1 million Spotify tracks with metadata and audio features.

Malformed rows are safely detected and skipped during parsing to ensure robustness.

---

## Feature Representation

Each song is converted into a feature vector using:

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

These features are normalized where necessary to ensure consistent scaling for distance calculations.

---

## Algorithms

### Brute-force kNN

- Computes distance between the selected song and all other songs
- Maintains top 5 closest matches using a max heap
- Time Complexity: **O(n)** per query

---

### KD-Tree

- Organizes songs into a K-dimensional tree
- Uses recursive traversal and pruning to reduce search space
- Average Time Complexity: **O(log n)** per query

---

## System Design

The project is structured into three main components:

### 1. Dataset Layer
- Parses CSV data and constructs `Song` objects
- Handles malformed rows and complex formatting
- Maintains a hash map for fast song lookup

### 2. Algorithm Layer
- `KNN`: brute-force nearest neighbor search
- `KDTree`: optimized search using spatial partitioning
- Both implementations return results using song indices for efficiency

### 3. UI Layer
- Shared helper functions for user interaction and output
- Handles input prompts, duplicate resolution, and result display
- Implemented in `UIHelpers` to avoid code duplication

---

## Project Structure

Dataset.h / Dataset.cpp      - CSV parsing and dataset management  
Song.h / Song.cpp            - Song representation and feature vectors  
KNN.h / KNN.cpp              - Brute-force nearest neighbor implementation  
KDTree.h                     - KD-Tree implementation  
UIHelpers.h / UIHelpers.cpp  - Shared UI and interaction logic  
KNNmain.cpp                  - kNN-based interface  
KDmain.cpp                   - KD-Tree-based interface  

---

## Key Design Decisions

- Implemented a custom CSV parser instead of using libraries to handle real-world messy data
- Used feature normalization to ensure fair similarity comparisons
- Stored song indices instead of full objects in algorithms to reduce memory overhead
- Designed both algorithms with a consistent interface for easy comparison
- Separated UI logic into reusable helper functions to improve modularity

---

## Future Improvements

- Add cosine similarity as an alternative distance metric
- Introduce feature weighting to prioritize certain attributes
- Benchmark performance between kNN and KD-Tree
- Integrate natural language search (e.g., “chill guitar songs”)
- Build a web interface using FastAPI

---

## Author

Joshua Heinemann  
Computer Science @ University of Florida
