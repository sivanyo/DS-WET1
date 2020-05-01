//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

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
    return shared_ptr<ArtistPlaysNode>();
}

void MostPlayedListNode::SetPtrToLowestArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode) {

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

shared_ptr<MostPlayedListNode> MostPlayedListNode::GetPrevious() {
    return this->previous;
}





