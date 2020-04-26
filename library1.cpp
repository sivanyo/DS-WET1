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
    return ((MusicManager *) DS)->AddArtist(artistID, numOfSongs);
}

StatusType RemoveArtist(void *DS, int artistID) {
    return ((MusicManager *) DS)->RemoveArtist(artistID);
};

StatusType AddToSongCount(void *DS, int artistID, int songID) {
    return ((MusicManager *) DS)->AddToSongCount(artistID, songID);
}

StatusType NumberOfStreams(void *DS, int artistID, int songID, int *streams) {
    return ((MusicManager *) DS)->NumberOfStreams(artistID, songID, streams);
}

StatusType GetRecommendedSongs(void *DS, int numOfSongs, int *artists, int *songs) {
    return ((MusicManager *) DS)->GetRecommendedSongs(numOfSongs, artists, songs);
}

void Quit(void **DS) {
    delete ((MusicManager *) DS);
    //**DS= nullptr;
}