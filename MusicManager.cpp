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
    shared_ptr<ArtistNode> artist = make_shared<ArtistNode>(artistId, Artist(artistId, numOfSongs));
    Artist &artistObj = artist->GetData();
    if (numberOfArtists == 0) {
        // Create node of first artist in artist tree
        this->artistTree = artist;
        // Create node of songs with 0 plays in linked list
        this->mostPlayedList = make_shared<MostPlayedListNode>(MostPlayedListNode(0));
        // Node with 0 plays in now the "most played" node
        this->ptrToMostRecommended = this->mostPlayedList;
    } else {
        // We already have artists in the system
        // Adding node with the new artist to the existing artist tree
        if (this->artistTree->AddNode(artist) == FAILURE) {
            return FAILURE;
        }
    }
    // Creating artist node to store the tree of it's songs with 0 plays
    shared_ptr<ArtistPlaysNode> artistNode = make_shared<ArtistPlaysNode>(artistId, ArtistPlays(artistId));
    // Create tree for songs of the new artist with 0 plays
    shared_ptr<SongPlaysNode> songNode = make_shared<SongPlaysNode>(0, SongPlays(0, artistId, this->mostPlayedList));
    // TODO: check that data transferred to the artistObj is saved properly
    artistObj[0].SetPtrToSongNode(songNode);
    shared_ptr<SongPlaysNode> songsTree = songNode;
    for (int i = 1; i < numOfSongs; ++i) {
        songNode = make_shared<SongPlaysNode>(i, SongPlays(i, artistId, this->mostPlayedList));
        artistObj[i].SetPtrToSongNode(songNode);
        songsTree->AddNode(songNode);
    }
    // Updating artistNode to store the pointer to the artist song with the lowest Id (currently 0)
    ArtistPlays &aPlays = artistNode->GetData();
    aPlays.SetPtrToLowestSongId(songsTree->Find(0));
    // Adding the new artist along with it's songs tree to the most played list
    this->mostPlayedList->AddArtist(artistNode);
    this->numberOfSongs += numOfSongs;
    this->numberOfArtists++;
    return SUCCESS;
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
