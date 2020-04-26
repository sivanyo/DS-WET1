//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_SONGNODE_H
#define WET1_SONGNODE_H


#include "TreeNode.h"
#include "Song.h"

class SongNode : public TreeNode {
private:
    int songId;
    int numOfPlays;
    Song *ptrToSongInArray;
public:
    SongNode(int songId, int numOfPlays, Song *ptrToSongInArray);

    int GetSongId();

    int GetNumberOfPlayes();

    void IncrementNumberOfPlays();
};


#endif //WET1_SONGNODE_H
