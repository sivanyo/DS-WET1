//
// Created by Mor on 26/04/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();
    if (!DS) {
        return nullptr;
    }
    return (void *) DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (!DS || artistID <= 0 || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->AddArtist(artistID, numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (!DS || artistID <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->RemoveArtist(artistID);
};

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if (!DS || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->AddToSongCount(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if (!DS || !streams || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->NumberOfStreams(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if (!DS) {
        return INVALID_INPUT;
    }
    if (numOfSongs <= 0) {
        return ALLOCATION_ERROR;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->GetRecommendedSongs(numOfSongs, artists, songs);
}

void Quit(void **DS) {
    MusicManager *nDS = static_cast<MusicManager *>(*DS);
    delete nDS;
    nDS = nullptr;
    *DS = nullptr;
}