//
// Created by Mor on 26/04/2020.
//

#include "Artist.h"

Artist::Artist(int artistId, int numOfSongs) {
    this->artistId = artistId;
//    if (numOfSongs != 0) {
//        Song* test = new Song[numOfSongs];
//        this->artistSongs = unique_ptr<Song[]>(array() new Song[numOfSongs]);
//        this->artistSongs[numOfSongs];
//        for (int i = 0; i < numOfSongs; ++i) {
//            artistSongs[i] = Song(i);
//        }
//    }
}

int Artist::GetArtistId() {
    return this->artistId;
}

int Artist::getArtistId() const {
    return artistId;
}

void Artist::setArtistId(int artistId) {
    Artist::artistId = artistId;
}

//Song &Artist::operator[](int index) {
//    return artistSongs[index];
//}
//
//Song Artist::operator[](int index) const {
//    return artistSongs[index];
//}
