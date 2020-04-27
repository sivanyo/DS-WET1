//
// Created by Mor on 26/04/2020.
//

#include <memory>>
#include "MusicManager.h"

using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;

MusicManager::MusicManager() {
    try {
        this->artistTree = unique_ptr<ArtistNode>(new ArtistNode(0, 0));
        this->mostPlayedList = unique_ptr<MostPlayedListNode>(new MostPlayedListNode(0));
        this->numberOfArtists = 0;
        this->ptrToMostRecommended = this->mostPlayedList.get();
    } catch (std::bad_alloc &e) {
        throw ALLOCATION_ERROR;
    }
}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    if (numberOfArtists == 0) {
        this->artistTree->SetData(artistId, numOfSongs);
        this->artistTree.
        this->artistTree = new ArtistNode(artistId, numOfSongs);
        this->numberOfSongs += numOfSongs;
        this->numberOfArtists++;
        return SUCCESS;
    } else {
        this->artistTree->AddNode(new ArtistNode(artistId, numOfSongs));
        this->numberOfSongs += numOfSongs;
        this->numberOfArtists++;
        return SUCCESS;
    }
    return INVALID_INPUT;
}

StatusType MusicManager::RemoveArtist(int artistId) {
    if (numberOfArtists == 0) {

    }
    return INVALID_INPUT;
}

StatusType MusicManager::AddToSongCount(int artistId, int numOfSongs) {
    return INVALID_INPUT;
}

StatusType MusicManager::NumberOfStreams(int artistId, int songID, int *streams) {
    return INVALID_INPUT;
}

StatusType MusicManager::GetRecommendedSongs(int numOfSongs, int *artist, int *songs) {
    return INVALID_INPUT;
}

MusicManager::~MusicManager() {

}
