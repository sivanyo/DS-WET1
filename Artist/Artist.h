//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H


#include "../Song/Song.h"

class Artist {
private:
    int artistId;
    //Song *artistSongs;
public:
    Artist(int artistId, int numOfSongs);

    int GetArtistId();

    int getArtistId() const;

    void setArtistId(int artistId);

//    Song &operator[](int index);
//
//    Song operator[](int index) const;
};

typedef TreeNode<Artist> ArtistNode;

#endif //WET1_ARTIST_H
