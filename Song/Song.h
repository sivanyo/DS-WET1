//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


#include "../MostPlayedList/SongPlaysByArtistIdNode.h"
#include "../MostPlayedList/ArtistPlaysByIdNode.h"

class Song {
public:
    int songId;
    int numberOfPlays = 0;
    ArtistPlaysByIdNode* ptrToArtistIdPlaysTree = nullptr;
    SongPlaysByArtistIdNode* ptrToArtistsNode = nullptr;

    Song(int songId);
};


#endif //WET1_SONG_H
