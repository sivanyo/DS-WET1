//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTIST_H
#define WET1_ARTIST_H

#include <memory>
#include "../TreeNode/Tree.h"
#include "../Song/Song.h"

using std::unique_ptr;

class Artist {
private:
    int artistId;
    int numberOfSongs;
    unique_ptr<Song[]> artistSongs;
public:
    Artist(int artistId, int numOfSongs);

    int GetArtistId();

    void SetArtistId(int artistId);

    int GetNumberOfSongs();

    Song &operator[](int index);

    Song operator[](int index) const;
};

#endif //WET1_ARTIST_H
