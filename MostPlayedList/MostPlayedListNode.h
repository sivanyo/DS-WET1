//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_MOSTPLAYEDLISTNODE_H
#define WET1_MOSTPLAYEDLISTNODE_H

#include "SongPlaysByArtistIdNode.h"
#include "ArtistPlaysByIdNode.h"

class MostPlayedListNode {
private:
    int numberOfPlays;
    ArtistPlaysByIdNode data;
    ArtistPlaysByIdNode *ptrToLowestArtistId;
    SongPlaysByArtistIdNode *ptrToLowestSongId;
    MostPlayedListNode *previous;
    MostPlayedListNode *next;

public:
    MostPlayedListNode(int numOfPlays);
    MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous);

    MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next);
};


#endif //WET1_MOSTPLAYEDLISTNODE_H
