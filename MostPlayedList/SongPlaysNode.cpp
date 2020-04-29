//
// Created by Mor on 27/04/2020.
//

#include "SongPlaysNode.h"

SongPlaysNode::SongPlaysNode(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToList) : TreeNode(songId) {
    this->songId = songId;
    this->numberOfPlays = 0;
    this->artistId = artistId;
    this->ptrToListNode = ptrToList;
}

int SongPlaysNode::GetSongId() const {
    return songId;
}

int SongPlaysNode::GetNumberOfPlays() const {
    return numberOfPlays;
}

int SongPlaysNode::GetArtistId() const {
    return artistId;
}

void SongPlaysNode::IncrementNumberOfPlays() {
    this->numberOfPlays++;
}

shared_ptr<MostPlayedListNode> SongPlaysNode::GetPtrToListNode() {
    return this->ptrToListNode;
}

void SongPlaysNode::SetPtrToListNode(shared_ptr<MostPlayedListNode> listNode) {
    this->ptrToListNode = listNode;
}
