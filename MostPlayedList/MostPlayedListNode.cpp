//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"
#include "../Artist/Artist.h"

MostPlayedListNode::MostPlayedListNode(int numOfPlays) : numberOfPlays(numOfPlays) {
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous) :
        numberOfPlays(numOfPlays), previous(previous) {
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next) :
        numberOfPlays(numOfPlays), previous(previous), next(next) {
}

ArtistPlaysTree *MostPlayedListNode::getArtistPlaysTree() const {
    return artistPlaysTree;
}

void MostPlayedListNode::setArtistPlaysTree(ArtistPlaysTree *ptr) {
    MostPlayedListNode::artistPlaysTree = ptr;
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

void MostPlayedListNode::setPrevious(MostPlayedListNode *ptr) {
    MostPlayedListNode::previous = ptr;
}

MostPlayedListNode *MostPlayedListNode::getNext() const {
    return next;
}

void MostPlayedListNode::setNext(MostPlayedListNode *ptr) {
    MostPlayedListNode::next = ptr;
}

// TODO: later
bool MostPlayedListNode::AddArtist(ArtistPlaysNode *artistNode) {
//    if (ptrToLowestArtistId) {
//        // There are already artists stored in this linked list
//        this->artistPlaysTree->AddNode(artistNode);
//        if (this->ptrToLowestArtistId->GetData().getArtistId() > artistNode->GetData().getArtistId()) {
//            this->ptrToLowestArtistId = artistNode;
//            this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
//        }
//        return true;
//    } else {
//        // There are no artists in this linked list, just add the new artist
//        this->artistPlaysTree = artistNode;
//        this->ptrToLowestArtistId = artistNode;
//        this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
//        return true;
//    }
    return true;
}

MostPlayedListNode::~MostPlayedListNode() {
    delete this->artistPlaysTree;
}

int MostPlayedListNode::getNumberOfPlays() {
    return this->numberOfPlays;
}

bool MostPlayedListNode::isNextNullptr() {
    return this->getNext();
}

class Artist;


