//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H


#include "library1.h"
#include "ArtistTree/ArtistNode.h"
#include "MostPlayedList/MostPlayedListNode.h"

using std::shared_ptr;

class MusicManager {
private:
    shared_ptr<ArtistNode> artistTree;
    shared_ptr<MostPlayedListNode> mostPlayedList;
    shared_ptr<MostPlayedListNode> ptrToMostRecommended;
    int numberOfArtists = 0;
    int numberOfSongs = 0;
public:
    MusicManager();
    StatusType AddArtist(int artistId, int numOfSongs);

    StatusType RemoveArtist(int artistId);

    StatusType AddToSongCount(int artistId, int numOfSongs);

    StatusType NumberOfStreams(int artistId, int songID, int *streams);

    StatusType GetRecommendedSongs(int numOfSongs,int *artist, int *songs);

    ~MusicManager();
};


#endif //WET1_MUSICMANAGER_H