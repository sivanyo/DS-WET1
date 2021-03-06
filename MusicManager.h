//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_MUSICMANAGER_H
#define WET1_MUSICMANAGER_H


#include "library1.h"
#include "MostPlayedListNode.h"
#include "Artist.h"

class MusicManager {
private:
    ArtistTree *artistTree;
    MostPlayedListNode *mostPlayedList;
    MostPlayedListNode *ptrToMostRecommended;
    int numberOfArtists;
    int numberOfSongs;
public:
    MusicManager();

    StatusType AddArtist(int artistId, int numOfSongs);

    StatusType RemoveArtist(int artistId);

    StatusType AddToSongCount(int artistId, int songID);

    StatusType NumberOfStreams(int artistId, int songID, int *streams);

    StatusType GetRecommendedSongs(int numOfSongs, int *artist, int *songs);

    ~MusicManager();

    StatusType addSongAtEndOfList(int newNumOfPlays, MostPlayedListNode *playsListNode,
                                  SongPlays *songPlays, ArtistNode *artistNode, int songID, int artistId);

    StatusType addArtistToPlaysNode();

    void removingSongNodeCaseNotAlone(MostPlayedListNode *playsListNode, int artistId, int songID, SongPlaysNode *songNode,
                                      ArtistNode *artistNode);

    void removingSongNodeCaseAlone(ArtistPlaysNode *artistPlaysNode, MostPlayedListNode *playsListNode, int artistId);
};


#endif //WET1_MUSICMANAGER_H
