//
// Created by Mor on 30/04/2020.
//

#ifndef WET1_SONGPLAYS_H
#define WET1_SONGPLAYS_H

#include "../TreeNode/TreeNode.h"

class MostPlayedListNode;

class SongPlays {
private:
    int songId;
    int numberOfPlays = 0;
    int artistId;
    MostPlayedListNode *ptrToListNode;
public:
    SongPlays(int songId, int artistId, MostPlayedListNode *ptrToListNode);

    int getSongId() const;

    int getArtistId() const;

    int getNumberOfPlays() const;

    void setNumberOfPlays(int numberOfPlays);

    void incrementNumberOfPlays();

    MostPlayedListNode *getPtrToListNode() const;

    void setPtrToListNode(MostPlayedListNode *ptr);


};

typedef TreeNode<SongPlays> SongPlaysNode;


#endif //WET1_SONGPLAYS_H
