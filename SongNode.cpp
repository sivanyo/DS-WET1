//
// Created by Mor on 26/04/2020.
//

#include "SongNode.h"

SongNode::SongNode(int songId, int numOfPlays, Song *ptrToSongInArray) : TreeNode(songId), songId(songId),
                                                                         numOfPlays(numOfPlays), ptrToSongInArray(ptrToSongInArray) {

}

int SongNode::GetSongId() {
    return this->songId;
}

int SongNode::GetNumberOfPlayes() {
    return this->numOfPlays;
}

void SongNode::IncrementNumberOfPlays() {
    this->numOfPlays++;
}
