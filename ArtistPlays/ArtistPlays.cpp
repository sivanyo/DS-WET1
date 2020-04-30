//
// Created by Mor on 27/04/2020.
//

#include "ArtistPlays.h"

ArtistPlays::ArtistPlays(int artistId) : artistId(artistId) {}

ArtistPlays::ArtistPlays(int artistId, shared_ptr<SongPlaysNode> ptrToSongPlaysTree, shared_ptr<SongPlaysNode> ptrToLowestSongId,
                                 shared_ptr<MostPlayedListNode> ptrToListNode) {
    this->artistId = artistId;
    this->SongPlaysTree = ptrToSongPlaysTree;
    this->ptrToLowestSongId = ptrToLowestSongId;
    this->ptrToListNode = ptrToListNode;
}

ArtistPlays::ArtistPlays(int artistId, shared_ptr<MostPlayedListNode> ptrToListNode): artistId(artistId) {
    this->ptrToListNode = ptrToListNode;
}

int ArtistPlays::GetArtistId() {
    return this->artistId;
}

const shared_ptr<SongPlaysNode> &ArtistPlays::GetPtrToLowestSongId() const {
    return ptrToLowestSongId;
}

//void ArtistPlays::SetPtrToLowestSongId(const shared_ptr<SongPlaysNode> &ptrToLowestSongId) {
//    this->ptrToLowestSongId.reset();
//    this->ptrToLowestSongId = ptrToLowestSongId;
//}

void ArtistPlays::SetPtrToLowestSongId(shared_ptr<SongPlaysNode> ptrToLowestSongId) {
    this->ptrToLowestSongId.reset();
    this->ptrToLowestSongId = ptrToLowestSongId;
}