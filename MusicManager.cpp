//
// Created by Mor on 26/04/2020.
//

#include "MusicManager.h"

MusicManager::MusicManager() {

}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    return INVALID_INPUT;
}

StatusType MusicManager::RemoveArtist(int artistId) {
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
