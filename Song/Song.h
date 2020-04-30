//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


#include "../MostPlayedList/SongPlaysNode.h"
#include "../ArtistPlays/ArtistPlays.h"

class Song {
public:
    int songId;
    int numberOfPlays = 0;
    ArtistPlaysNode* ptrToArtistIdPlaysTree = nullptr;
    SongPlaysNode* ptrToArtistsNode = nullptr;

    Song(int songId);
};


#endif //WET1_SONG_H
