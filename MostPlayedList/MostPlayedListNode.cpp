//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

MostPlayedListNode::MostPlayedListNode(int numOfPlays) {
    this->numberOfPlays = numOfPlays;
}

bool MostPlayedListNode::AddArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode) {
    shared_ptr<ArtistPlaysNode> test = make_shared<ArtistPlaysNode>(5);
    test->AddNode(make_shared<ArtistPlaysNode>(4))
    artistPlaysNode.ad
    if (ptrToLowestArtistId) {
        // There are already artists stored in this linked list
        // TODO: might be related to code progression
        this->artistPlaysTree.
    }
    return false;
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


MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = nullptr;
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = next;
}


