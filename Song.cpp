//
// Created by Mor on 26/04/2020.
//

#include "Song.h"

Song::Song() : songId(0) {
}

Song::Song(int songId) {
    this->songId = songId;
}

int Song::getSongId() const {
    return songId;
}

void Song::SetSongId(int id) {
    songId = id;
}

int Song::getNumberOfPlays() const {
    return this->numberOfPlays;
}

void Song::setNumberOfPlays(int plays) {
    this->numberOfPlays = plays;
}

void Song::incrementNumberOfPlays() {
    numberOfPlays++;
}

SongPlaysNode *Song::getPtrToSongNodeInPlaysTree() const {
    return ptrToSongNodeInPlaysTree;
}

void Song::setPtrToSongNodeInPlaysTree(SongPlaysNode *ptr) {
    ptrToSongNodeInPlaysTree = ptr;
}