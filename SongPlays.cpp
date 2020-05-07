//
// Created by Mor on 30/04/2020.
//

#include "SongPlays.h"

SongPlays::SongPlays(int songId, int artistId, MostPlayedListNode *ptrToListNode) :
        songId(songId), artistId(artistId), ptrToListNode(ptrToListNode), ptrToSong(nullptr) {}

int SongPlays::getSongId() const {
    return songId;
}

int SongPlays::getArtistId() const {
    return artistId;
}

int SongPlays::getNumberOfPlays() const {
    return numberOfPlays;
}

void SongPlays::setNumberOfPlays(int plays) {
    SongPlays::numberOfPlays = plays;
}

void SongPlays::incrementNumberOfPlays() {
    this->numberOfPlays++;
}

void SongPlays::DecrementNumberOfPlays() {
    this->numberOfPlays--;
}

MostPlayedListNode *SongPlays::getPtrToListNode() const {
    return ptrToListNode;
}

void SongPlays::setPtrToListNode(MostPlayedListNode *ptr) {
    ptrToListNode = ptr;
}

Song *SongPlays::getPtrToSong() const {
    return ptrToSong;
}

void SongPlays::setPtrToSong(Song *ptr) {
    ptrToSong = ptr;
}

void SongPlays::DeleteSongPlaysNode(TreeNode<SongPlays>* songNode) {
    if (songNode->getLeft()) {
        DeleteSongPlaysNode(songNode->getLeft());
        delete songNode->getLeft();
        songNode->setLeft(nullptr);
    }
    if (songNode->getRight()) {
        DeleteSongPlaysNode(songNode->getRight());
        delete songNode->getRight();
        songNode->setRight(nullptr);
    }
    SongPlays *temp = songNode->getValue();
    // Marking the current song as deleted, so we know not to try and delete it again
    temp->getPtrToSong()->setNumberOfPlays(-1);
    //temp->setNumberOfPlays(-1);
    if (songNode->getParent() == nullptr) {
        // This is the root of the tree so there is no one else who will try and delete it's contents, need to delete on our own
        // to avoid leak
        delete songNode->getValue();
        songNode->removeValue();
    }
}
