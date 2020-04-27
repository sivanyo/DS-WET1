//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H


#include "../Song/Song.h"

class Artist {
private:
    int artistId;
    Song artistSongs[];

    int GetArtistId();

public:
    Artist(int artistId, int numOfSongs);
};


#endif //WET1_ARTIST_H
