//
// Created by Mor on 30/04/2020.
//

#include "SongPlays.h"
#include "../Song/Song.h"

SongPlays::SongPlays(int songId, int artistId, MostPlayedListNode *ptrToListNode) :
        songId(songId), artistId(artistId), ptrToListNode(ptrToListNode) {}

int SongPlays::getSongId() const {
    return songId;
}

int SongPlays::getArtistId() const {
    return artistId;
}

int SongPlays::getNumberOfPlays() const {
    return numberOfPlays;
}

void SongPlays::setNumberOfPlays(int numberOfPlays) {
    SongPlays::numberOfPlays = numberOfPlays;
}

void SongPlays::incrementNumberOfPlays() {
    this->numberOfPlays++;
}

MostPlayedListNode *SongPlays::getPtrToListNode() const {
    return ptrToListNode;
}

void SongPlays::setPtrToListNode(MostPlayedListNode *ptr) {
    ptrToListNode = ptr;
}