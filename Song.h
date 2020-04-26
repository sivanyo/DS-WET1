//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


class Song {
public:
    int songId;
    int numberOfPlays = 0;
    //SongPlaysListNode* ptrToArtistsNode = nullptr;
    //ArtistPlaysTree* ptrToArtistIdPlaysTree = nullptr;

    Song(int songId);
};


#endif //WET1_SONG_H
