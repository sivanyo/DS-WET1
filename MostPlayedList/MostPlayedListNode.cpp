//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

MostPlayedListNode::MostPlayedListNode(int numOfPlays) : numberOfPlays(numOfPlays) {
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous) :
        numberOfPlays(numOfPlays), previous(previous) {
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next) :
        numberOfPlays(numOfPlays), previous(previous), next(next) {
}

ArtistPlaysNode *MostPlayedListNode::getArtistPlaysTree() const {
    return artistPlaysTree;
}

void MostPlayedListNode::setArtistPlaysTree(ArtistPlaysNode *artistPlaysTree) {
    MostPlayedListNode::artistPlaysTree = artistPlaysTree;
}

ArtistPlaysNode *MostPlayedListNode::getPtrToLowestArtistId() const {
    return ptrToLowestArtistId;
}

void MostPlayedListNode::setPtrToLowestArtistId(ArtistPlaysNode *ptr) {
    ptrToLowestArtistId = ptr;
}

SongPlaysNode *MostPlayedListNode::getPtrToLowestSongId() const {
    return ptrToLowestSongId;
}

void MostPlayedListNode::setPtrToLowestSongId(SongPlaysNode *ptr) {
    ptrToLowestSongId = ptr;
}

MostPlayedListNode *MostPlayedListNode::getPrevious() const {
    return previous;
}

void MostPlayedListNode::setPrevious(MostPlayedListNode *previous) {
    MostPlayedListNode::previous = previous;
}

MostPlayedListNode *MostPlayedListNode::getNext() const {
    return next;
}

void MostPlayedListNode::setNext(MostPlayedListNode *next) {
    MostPlayedListNode::next = next;
}

bool MostPlayedListNode::AddArtist(ArtistPlaysNode *artistNode) {
    if (ptrToLowestArtistId) {
        // There are already artists stored in this linked list
        this->artistPlaysTree->AddNode(artistNode);
        if (this->ptrToLowestArtistId->GetData().getArtistId() > artistNode->GetData().getArtistId()) {
            this->ptrToLowestArtistId = artistNode;
            this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
        }
        return true;
    } else {
        // There are no artists in this linked list, just add the new artist
        this->artistPlaysTree = artistNode;
        this->ptrToLowestArtistId = artistNode;
        this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
        return true;
    }
}

MostPlayedListNode::~MostPlayedListNode() {
    delete this->artistPlaysTree;
}
