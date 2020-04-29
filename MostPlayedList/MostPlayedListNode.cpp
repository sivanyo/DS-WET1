//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

MostPlayedListNode::MostPlayedListNode(int numOfPlays) {
    this->numberOfPlays = numOfPlays;
}

// MostPlayedListNode.cpp
bool MostPlayedListNode::AddArtist(shared_ptr<ArtistPlaysNode> artistNode) {
    if (ptrToLowestArtistId) {
        // There are already artists stored in this linked list
        this->artistPlaysTree->AddNode(artistNode);
        return true;
    } else {
        this->artistPlaysTree = artistNode;
        return true;
    }
}

shared_ptr<ArtistPlaysNode> MostPlayedListNode::GetPtrToLowestArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode) {
    return shared_ptr<ArtistPlaysNode>();
}

void MostPlayedListNode::SetPtrToLowestArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode) {

}

shared_ptr<ArtistPlaysNode> MostPlayedListNode::GetPtrToLowestSong(shared_ptr<SongPlaysNode> songPlaysNode) {
    return shared_ptr<ArtistPlaysNode>();
}

void MostPlayedListNode::SetPtrToLowestSong(shared_ptr<SongPlaysNode> songPlaysNode) {

}


MostPlayedListNode::MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = nullptr;
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous, shared_ptr<MostPlayedListNode> next) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = next;
}


