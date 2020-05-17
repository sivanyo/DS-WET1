//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_MOSTPLAYEDLISTNODE_H
#define WET1_MOSTPLAYEDLISTNODE_H

#include "ArtistPlays.h"
#include "SongPlays.h"
#include "Artist.h"

class MostPlayedListNode {
private:
    int numberOfPlays;
    ArtistPlaysTree *artistPlaysTree = nullptr;
    ArtistPlaysNode *ptrToLowestArtistId = nullptr;
    SongPlaysNode *ptrToLowestSongId = nullptr;
    MostPlayedListNode *previous = nullptr;
    MostPlayedListNode *next = nullptr;

public:
    // Create the first node in the list (0 plays)
    explicit MostPlayedListNode(int numOfPlays);

    // Create a new node with a new highest number of plays
    MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous);

    // Create a new node with a number of plays between to values (1<2<3)
    MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next);

    ArtistPlaysTree *getArtistPlaysTree() const;

    void setArtistPlaysTree(ArtistPlaysTree *ptr);

    bool AddArtist(ArtistPlaysNode *artistNode);

    ArtistPlaysNode *getPtrToLowestArtistId() const;

    void setPtrToLowestArtistId(ArtistPlaysNode *ptr);

    SongPlaysNode *getPtrToLowestSongId() const;

    void setPtrToLowestSongId(SongPlaysNode *ptr);

    MostPlayedListNode *getPrevious() const;

    void setPrevious(MostPlayedListNode *ptr);

    MostPlayedListNode *getNext() const;

    void setNext(MostPlayedListNode *ptr);

    int getNumberOfPlays();

    bool isNextNullptr();

    ~MostPlayedListNode();

};


#endif //WET1_MOSTPLAYEDLISTNODE_H
