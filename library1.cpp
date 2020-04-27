//
// Created by Mor on 26/04/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init() {
    MusicManager *DS = new MusicManager();
    return (void *) DS;
}

StatusType AddArtist(void *DS, int artistID, int numOfSongs) {
    if (!DS || artistID <= 0 || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    return ((MusicManager *) DS)->AddArtist(artistID, numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID) {
    if (!DS || artistID <= 0) {
        return INVALID_INPUT;
    }
    return ((MusicManager *) DS)->RemoveArtist(artistID);
};

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    if (!DS || artistID <= 0) {
        return INVALID_INPUT;
    }
    /**
     * TODO: add internal check that the songID that needs to be added is not
     * larger than the total number of songs for that artist
     */
    return ((MusicManager *) DS)->AddToSongCount(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    if (!DS || artistID <= 0 || songID < 0) {
        return INVALID_INPUT;
    }
    /**
     * TODO: add internal check that the songID that needs to be added is not
     * larger than the total number of songs for that artist
     */
    return ((MusicManager *) DS)->NumberOfStreams(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    if (!DS || numOfSongs <= 0) {
        return INVALID_INPUT;
    }
    return ((MusicManager *) DS)->GetRecommendedSongs(numOfSongs, artists, songs);
}

void Quit(void **DS) {
    delete ((MusicManager *) DS);
    //**DS= nullptr;
}