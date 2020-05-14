//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H

#include "Song.h"
#include "Tree.h"

class Artist {
private:
    int artistId;
    int numberOfSongs;
    Song **artistSongs;
public:
    Artist(int artistId, int numOfSongs);

    int getArtistId() const;

    void setArtistId(int id);

    int getNumberOfSongs() const;

    void setNumberOfSongs(int newNum);

    Song *operator[](int index) const;

    Song *&operator[](int index);

    ~Artist();
};

typedef TreeNode<Artist> ArtistNode;
typedef Tree<Artist> ArtistTree;

#endif //WET1_ARTIST_H
