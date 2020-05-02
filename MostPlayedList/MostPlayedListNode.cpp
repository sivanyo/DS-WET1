//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

#include <utility>

MostPlayedListNode::MostPlayedListNode(int numOfPlays) {
    this->numberOfPlays = numOfPlays;
}

bool MostPlayedListNode::AddArtist(shared_ptr<ArtistPlaysNode> artistNode) {
    if (ptrToLowestArtistId) {
        // There are already artists stored in this linked list
        this->artistPlaysTree->AddNode(artistNode);
        if (this->ptrToLowestArtistId->GetData().GetArtistId() > artistNode->GetData().GetArtistId()) {
            this->ptrToLowestArtistId.reset();
            this->ptrToLowestArtistId = artistNode;
            this->ptrToLowestSongId.reset();
            this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
        }
        return true;
    } else {
        this->artistPlaysTree = artistNode;
        this->ptrToLowestArtistId = artistNode;
        this->ptrToLowestSongId = artistNode->GetData().GetPtrToLowestSongId();
        return true;
    }
}

shared_ptr<ArtistPlaysNode> MostPlayedListNode::GetPtrToLowestArtist() {
    return this->ptrToLowestArtistId;
}

void MostPlayedListNode::SetPtrToLowestArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode) {
    this->ptrToLowestArtistId = (artistPlaysNode);
}


void MostPlayedListNode::SetPtrToLowestSong(shared_ptr<SongPlaysNode> songPlaysNode) {
    this->ptrToLowestSongId=(songPlaysNode);
}


MostPlayedListNode::MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous) {
    this->numberOfPlays = numOfPlays;
    this->previous = (previous);
    this->next = nullptr;
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous, shared_ptr<MostPlayedListNode> next) {
    this->numberOfPlays = numOfPlays;
    this->previous = (previous);
    this->next = (next);
}

shared_ptr<MostPlayedListNode> MostPlayedListNode::GetPrevious() {
    return this->previous;
}

void MostPlayedListNode::setPrevious(shared_ptr<MostPlayedListNode> previous) {
    MostPlayedListNode::previous = previous;
}

const shared_ptr<MostPlayedListNode> &MostPlayedListNode::getNext() const {
    return this->next;
}

void MostPlayedListNode::setNext(shared_ptr<MostPlayedListNode> next) {
    MostPlayedListNode::next = next;
}

int MostPlayedListNode::getNumberOfPlays() const {
    return this->numberOfPlays;
}

const shared_ptr<ArtistPlaysNode> &MostPlayedListNode::getArtistPlaysTree() const {
    this->artistPlaysTree;
}

void MostPlayedListNode::setPtrToLowestArtistId(shared_ptr<ArtistPlaysNode> ptrToLowestArtistId) {
    MostPlayedListNode::ptrToLowestArtistId = (ptrToLowestArtistId);
}

shared_ptr<SongPlaysNode> MostPlayedListNode::GetPtrToLowestSong() {
    return this->ptrToLowestSongId;
}

