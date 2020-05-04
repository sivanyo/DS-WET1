//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H

#include "../Song/Song.h"
#include "../TreeNode/Tree.h"

class Artist {
private:
    int artistId;
    int numberOfSongs;
    Song* artistSongs;
public:
    Artist(int artistId, int numOfSongs);

    int getArtistId() const;

    void setArtistId(int id);

    int getNumberOfSongs() const;

    Song &operator[](int index);

    Song operator[](int index) const;

    ~Artist();
};

typedef TreeNode<Artist> ArtistNode;
typedef Tree<Artist> ArtistTree;

#endif //WET1_ARTIST_H
