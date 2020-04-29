//
// Created by Mor on 26/04/2020.
//

#include <memory>
#include "MusicManager.h"

using std::shared_ptr;
using std::make_shared;

MusicManager::MusicManager() {
    this->artistTree = shared_ptr<ArtistNode>(make_shared<ArtistNode>(ArtistNode(0, 0)));
    this->mostPlayedList = shared_ptr<MostPlayedListNode>(make_shared<MostPlayedListNode>(MostPlayedListNode(0)));
    this->numberOfArtists = 0;
    this->ptrToMostRecommended = shared_ptr<MostPlayedListNode>(this->mostPlayedList);
}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    if (numberOfArtists == 0) {
        this->artistTree->SetData(artistId, numOfSongs);
        this->artistTree->SetKey(artistId);
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
