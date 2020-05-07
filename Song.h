//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONG_H
#define WET1_SONG_H


#include "ArtistPlays.h"

class ArtistPlays;
class SongPlays;

class Song {
private:
    int songId;
    int numberOfPlays = 0;
    TreeNode<ArtistPlays> *ptrToArtistIdPlaysTree = nullptr;
    TreeNode<SongPlays> *ptrToSongNodeInPlaysTree = nullptr;
public:
    Song();

    explicit Song(int songId);

    int getSongId() const;

    void SetSongId(int id);

    int getNumberOfPlays() const;

    void setNumberOfPlays(int plays);

    void incrementNumberOfPlays();

    TreeNode<ArtistPlays> *getPtrToArtistIdPlaysTree() const;

    void setPtrToArtistIdPlaysTree(TreeNode<ArtistPlays> *ptr);

    TreeNode<SongPlays> *getPtrToSongNodeInPlaysTree() const;

    void setPtrToSongNodeInPlaysTree(TreeNode<SongPlays> *ptr);
};


#endif //WET1_SONG_H
