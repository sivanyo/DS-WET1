//
// Created by Mor on 26/04/2020.
//

#include "Artist.h"

Artist::Artist(int artistId, int numOfSongs) {
    this->artistId = artistId;
//    this->artistSongs[numOfSongs];
//    for (int i = 0; i < numOfSongs; ++i) {
//        artistSongs[i] = Song(i);
//    }
}

int Artist::GetArtistId() {
    return this->artistId;
}
