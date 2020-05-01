//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


#include "../MostPlayedList/SongPlaysNode.h"
#include "../ArtistPlays/ArtistPlays.h"

class Song {
private:
    int songId;
    int numberOfPlays = 0;
    shared_ptr<ArtistPlaysNode> ptrToArtistIdPlaysTree = nullptr;
    shared_ptr<SongPlaysNode> ptrToSongNodeInPlaysTree = nullptr;
public:
    Song();
    Song(int songId);

    int GetSongId();
    void SetSongId(int id);

    shared_ptr<ArtistPlaysNode> GetPtrToArtistNode();
    void SetPtrToArtistNode(shared_ptr<ArtistPlaysNode> ptr);

    shared_ptr<SongPlaysNode> GetPtrToSongNode();
    void SetPtrToSongNode(shared_ptr<SongPlaysNode> ptr);

    int getNumberOfPlays() const;

    void setNumberOfPlays(int numberOfPlays);
};

void Song::setNumberOfPlays(int numberOfPlays) {
    Song::numberOfPlays = numberOfPlays;
}


#endif //WET1_SONG_H
