//
// Created by Mor on 26/04/2020.
//

#include "Artist.h"

Artist::Artist(int artistId, int numOfSongs): artistId(artistId), numberOfSongs(numOfSongs) {
    if (numOfSongs != 0) {
        this->artistSongs = unique_ptr<Song[]>(new Song[numOfSongs]);
        for (int i = 0; i < numOfSongs; ++i) {
            artistSongs[i].SetSongId(i);
        }
    }
}

int Artist::GetArtistId() {
    return this->artistId;
}

void Artist::SetArtistId(int artistId) {
    Artist::artistId = artistId;
}

int Artist::GetNumberOfSongs() {
    return numberOfSongs;
}


Song &Artist::operator[](int index) {
    return artistSongs[index];
}

Song Artist::operator[](int index) const {
    return artistSongs[index];
}