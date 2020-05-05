//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


#include "../ArtistPlays/ArtistPlays.h"

class Song {
private:
    int songId;
    int numberOfPlays = 0;
    ArtistPlaysTree *ptrToArtistIdPlaysTree = nullptr;
    SongPlaysNode *ptrToSongNodeInPlaysTree = nullptr;
public:
    Song();

    explicit Song(int songId);

    int getSongId() const;

    void SetSongId(int id);

    int getNumberOfPlays() const;

    void setNumberOfPlays(int plays);

    void incrementNumberOfPlays();

    ArtistPlaysTree *getPtrToArtistIdPlaysTree() const;

    void setPtrToArtistIdPlaysTree(ArtistPlaysTree *ptr);

    SongPlaysNode *getPtrToSongNodeInPlaysTree() const;

    void setPtrToSongNodeInPlaysTree(SongPlaysNode *ptr);
};


#endif //WET1_SONG_H
