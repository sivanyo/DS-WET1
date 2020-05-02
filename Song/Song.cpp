//
// Created by Mor on 26/04/2020.
//

#include "Song.h"

Song::Song() : songId(0) {
}

Song::Song(int songId) {
    this->songId = songId;
}

int Song::GetSongId() const {
    return songId;
}

void Song::SetSongId(int id) {
    songId = id;
}

shared_ptr<ArtistPlaysNode> Song::GetPtrToArtistNode() {
    return this->ptrToArtistIdPlaysTree;
}

void Song::SetPtrToArtistNode(shared_ptr<ArtistPlaysNode> ptr) {
    ptrToArtistIdPlaysTree = ptr;
}

shared_ptr<SongPlaysNode> Song::GetPtrToSongNode() {
    return this->ptrToSongNodeInPlaysTree;
}

void Song::SetPtrToSongNode(shared_ptr<SongPlaysNode> ptr) {
    ptrToSongNodeInPlaysTree = ptr;
}

int Song::getNumberOfPlays() const {
    return this->numberOfPlays;
}

void Song::setNumberOfPlays(int numberOfPlays) {
    this->numberOfPlays=numberOfPlays;
}

const shared_ptr<ArtistPlaysNode> &Song::getPtrToArtistIdPlaysTree() const {
    return this->ptrToArtistIdPlaysTree;
}

const shared_ptr<SongPlaysNode> &Song::getPtrToSongNodeInPlaysTree() const {
    return this->ptrToSongNodeInPlaysTree;
}
