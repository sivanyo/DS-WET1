//
// Created by Mor on 27/04/2020.
//

#include "ArtistPlays.h"

ArtistPlays::ArtistPlays(int artistId) : artistId(artistId) {}

ArtistPlays::ArtistPlays(int artistId, MostPlayedListNode *ptrToListNode) : artistId(artistId), ptrToListNode(ptrToListNode) {

}

ArtistPlays::ArtistPlays(int artistId, ::SongPlaysTree *SongPlaysTree, SongPlaysNode *ptrToLowestSongId, MostPlayedListNode *ptrToListNode)
        : artistId(artistId), SongPlaysTree(SongPlaysTree), ptrToLowestSongId(ptrToLowestSongId), ptrToListNode(ptrToListNode) {

}

int ArtistPlays::getArtistId() const {
    return this->artistId;
}

SongPlaysTree *ArtistPlays::getSongPlaysTree() const {
    return SongPlaysTree;
}

void ArtistPlays::setSongPlaysTree(::SongPlaysTree *songPlaysTree) {
    SongPlaysTree = songPlaysTree;
}

SongPlaysNode *ArtistPlays::getPtrToLowestSongId() const {
    return ptrToLowestSongId;
}

void ArtistPlays::setPtrToLowestSongId(SongPlaysNode *ptr) {
    ArtistPlays::ptrToLowestSongId = ptr;
}

MostPlayedListNode *ArtistPlays::getPtrToListNode() const {
    return ptrToListNode;
}

void ArtistPlays::setPtrToListNode(MostPlayedListNode *ptr) {
    ArtistPlays::ptrToListNode = ptr;
}

ArtistPlays::~ArtistPlays() {
    delete SongPlaysTree;
}
