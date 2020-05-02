//
// Created by Mor on 30/04/2020.
//

#include "SongPlays.h"
#include "../Song/Song.h"

SongPlays::SongPlays(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToListNode) : songId(songId), artistId(artistId),
                                                                                               ptrToListNode(ptrToListNode) {}

int SongPlays::GetSongId() const {
    return this->songId;
}

int SongPlays::GetNumberOfPlays() const {
    return this->numberOfPlays;
}

int SongPlays::GetArtistId() const {
    return this->artistId;
}

void SongPlays::IncrementNumberOfPlays() {
    this->numberOfPlays++;
}

shared_ptr<MostPlayedListNode> SongPlays::GetPtrToListNode() {
    return this->ptrToListNode;
}

void SongPlays::SetPtrToListNode(shared_ptr<MostPlayedListNode> listNode) {
    this->ptrToListNode.reset();
    this->ptrToListNode = listNode;
}