//
// Created by Mor on 26/04/2020.
//

#include "Artist.h"

Artist::Artist(int artistId, int numOfSongs) : artistId(artistId), numberOfSongs(numOfSongs) {
    if (numOfSongs != 0) {
        this->artistSongs = new Song *[numOfSongs];
        if (this->artistSongs) {
            for (int i = 0; i < numOfSongs; ++i) {
                artistSongs[i] = new Song(i);
            }
        }
    }
}

int Artist::getArtistId() const {
    return artistId;
}

void Artist::setArtistId(int id) {
    artistId = id;
}

int Artist::getNumberOfSongs() const {
    return numberOfSongs;
}

Song *&Artist::operator[](int index) {
    return artistSongs[index];
}

Song *Artist::operator[](int index) const {
    return artistSongs[index];
}

Artist::~Artist() {
    for (int i = 0; i < numberOfSongs; ++i) {
        delete this->artistSongs[i];
    }
    delete this->artistSongs;
}

void Artist::setNumberOfSongs(int newNum) {
    this->numberOfSongs=newNum;
}

