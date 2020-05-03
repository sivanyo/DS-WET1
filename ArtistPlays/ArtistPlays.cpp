//
// Created by Mor on 27/04/2020.
//

#include "ArtistPlays.h"

ArtistPlays::ArtistPlays(int artistId) : artistId(artistId) {}

ArtistPlays::ArtistPlays(int artistId, MostPlayedListNode *ptrToListNode) : artistId(artistId), ptrToListNode(ptrToListNode) {

}

ArtistPlays::ArtistPlays(int artistId, SongPlaysNode *SongPlaysTree, SongPlaysNode *ptrToLowestSongId, MostPlayedListNode *ptrToListNode)
        : artistId(artistId), SongPlaysTree(SongPlaysTree), ptrToLowestSongId(ptrToLowestSongId), ptrToListNode(ptrToListNode) {

}

int ArtistPlays::getArtistId() const {
    return this->artistId;
}

SongPlaysNode *ArtistPlays::getSongPlaysTree() const {
    return SongPlaysTree;
}

void ArtistPlays::setSongPlaysTree(SongPlaysNode *songPlaysTree) {
    SongPlaysTree = songPlaysTree;
}

SongPlaysNode *ArtistPlays::getPtrToLowestSongId() const {
    return ptrToLowestSongId;
}

void ArtistPlays::setPtrToLowestSongId(SongPlaysNode *ptrToLowestSongId) {
    ArtistPlays::ptrToLowestSongId = ptrToLowestSongId;
}

MostPlayedListNode *ArtistPlays::getPtrToListNode() const {
    return ptrToListNode;
}

void ArtistPlays::setPtrToListNode(MostPlayedListNode *ptrToListNode) {
    ArtistPlays::ptrToListNode = ptrToListNode;
}