//
// Created by Mor on 26/04/2020.
//

#include "Song.h"

Song::Song() : songId(0) {
}

Song::Song(int songId) {
    this->songId = songId;
}

int Song::GetSongId() {
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
