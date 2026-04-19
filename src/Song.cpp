#include "Song.h"

double normalize(float x, float min, float max) {
    if (max == min) return 0.0f;
    return (x - min) / (max - min);
}

Song::Song(std::string id, std::string name, std::vector<std::string> artists, std::string album,
           double danceability, double energy, double valence, double tempo,
           double acousticness, double instrumentalness, double loudness,
           double speechiness, double liveness, int key, int mode, int duration_ms)
    : id(id), name(name), artists(artists), album(album),
      danceability(danceability), energy(energy), valence(valence), tempo(tempo),
      acousticness(acousticness), instrumentalness(instrumentalness),
      loudness(loudness), speechiness(speechiness), liveness(liveness),
      key(key), mode(mode), duration_ms(duration_ms) 
{
        features = {
            this->danceability,
            this->energy,
            this->valence,
            this->acousticness,
            this->instrumentalness,
            this->liveness,
            this->speechiness,
            normalize(this->key, 0, 11),
            normalize(this->loudness, -60, 7),
            normalize(this->tempo, 0, 250),
        };

}

const std::vector<double>& Song::getFeatures() const {
    return features;
}

std::string Song::getId() const {
    return id;
}

std::string Song::getName() const {
    return name;
}

std::vector<std::string> Song::getArtists() const {
    return artists;
}

std::string Song::getAlbum() const {
    return album;
}

double Song::getDanceability() const {
    return danceability;
}

double Song::getEnergy() const {
    return energy;
}

double Song::getValence() const {
    return valence;
}

double Song::getTempo() const {
    return tempo;
}

double Song::getAcousticness() const {
    return acousticness;
}

double Song::getInstrumentalness() const {
    return instrumentalness;
}

double Song::getLoudness() const {
    return loudness;
}

double Song::getSpeechiness() const {
    return speechiness;
}

double Song::getLiveness() const {
    return liveness;
}

int Song::getKey() const {
    return key;
}

int Song::getMode() const {
    return mode;
}

int Song::getDurationMs() const {
    return duration_ms;
}