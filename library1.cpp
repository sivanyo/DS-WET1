//
// Created by Mor on 26/04/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init() {
    try {
        MusicManager *DS = new MusicManager();
        if (!DS) {
            return nullptr;
        }
        return (void *) DS;
    } catch (std::bad_alloc &e) {
        return nullptr;
    }
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (!DS || artistID <= 0 || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->AddArtist(artistID, numOfSongs);

    //return ((MusicManager *) DS)->AddArtist(artistID, numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (!DS || artistID <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->RemoveArtist(artistID);
    //return ((MusicManager *) DS)->RemoveArtist(artistID);
};

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if (!DS || artistID <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->AddToSongCount(artistID, songID);
    //return ((MusicManager *) DS)->AddToSongCount(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if (!DS || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->NumberOfStreams(artistID, songID, streams);
    //return ((MusicManager *) DS)->NumberOfStreams(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if (!DS || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    MusicManager *nDS = static_cast<MusicManager *>(DS);
    return nDS->GetRecommendedSongs(numOfSongs, artists, songs);
    //return ((MusicManager *) DS)->GetRecommendedSongs(numOfSongs, artists, songs);
}

void Quit(void **DS) {
    MusicManager *nDS = static_cast<MusicManager *>(*DS);
    delete nDS;
    nDS = nullptr;
    //delete ((MusicManager *) DS);
    *DS = nullptr;
}