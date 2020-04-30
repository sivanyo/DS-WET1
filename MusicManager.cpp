//
// Created by Mor on 26/04/2020.
//

#include <memory>
#include "TreeNode/TreeNode.h"
#include "Artist/Artist.h"
#include "MusicManager.h"

using std::shared_ptr;
using std::make_shared;

//class SongPlays;
//typedef TreeNode<SongPlays> SongPlaysNode;

MusicManager::MusicManager() {
    this->numberOfArtists = 0;
}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    if (numberOfArtists == 0) {
        // Create node of first artist in large artist tree
        make_shared<ArtistNode>(0, Artist(0,0));
        this->artistTree = shared_ptr<ArtistNode>(make_shared<ArtistNode>(artistId, Artist(artistId, numOfSongs)));
        // Create node of songs with 0 plays in linked list
        this->mostPlayedList = shared_ptr<MostPlayedListNode>(make_shared<MostPlayedListNode>(MostPlayedListNode(0)));
        this->ptrToMostRecommended = shared_ptr<MostPlayedListNode>(this->mostPlayedList);
        // Create song tree for artist
        shared_ptr<ArtistPlaysNode> artistNode = make_shared<ArtistPlaysNode>(artistId, ArtistPlays(artistId));
        // Create tree for songs of the new artist
        shared_ptr<SongPlaysNode> songsTree = make_shared<SongPlaysNode>(0, SongPlays(0, artistId, this->mostPlayedList));
//        shared_ptr<SongPlaysNode> songsTree = make_shared<SongPlaysNode>(SongPlaysNode(0, artistId, this->mostPlayedList));
        for (int i = 1; i < numOfSongs; ++i) {
            songsTree->AddNode(make_shared<SongPlaysNode>(i, SongPlays(i, artistId, this->mostPlayedList)));
        }
        ArtistPlays aPlays = artistNode->GetData();
        aPlays.SetPtrToLowestSongId(songsTree->Find(0));
        this->mostPlayedList->AddArtist(artistNode);
        this->numberOfSongs += numOfSongs;
        this->numberOfArtists++;
        return SUCCESS;
    } else {
        this->artistTree->AddNode(make_shared<ArtistNode>(artistId, Artist(artistId, numOfSongs)));
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
