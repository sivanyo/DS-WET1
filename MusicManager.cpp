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
    shared_ptr<ArtistPlaysNode> artistNode = make_shared<ArtistPlaysNode>(artistId,
                                                                          ArtistPlays(artistId, this->mostPlayedList));
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
    // Storing the root of artist songs tree in the ArtistPlaysNode
    // TODO: update in document that we're using this function which takes log(m) instructions in the worst case
    aPlays.SetSongPlaysTree(songNode->FindRoot());
    aPlays.SetPtrToLowestSongId(songsTree->Find(0));
    // Adding the new artist along with it's songs tree to the most played list
    this->mostPlayedList->AddArtist(artistNode);
    this->numberOfSongs += numOfSongs;
    this->numberOfArtists++;
    return SUCCESS;
}


/**
 * Flow of remove artist:
 * check if an artist with that ID exists,
 * go over all songs of that artist (in songs array from Artist object)
 * for each song, go to the pointer for the artistPlaysNode, delete the tree the node is pointing to
 * (that is the tree of songs of that artist with that number of plays) during this time if a song is removed, use
 * , use the pointer saved in ArtistPlaysNode
 * to go to the list node and delete that artist from the tree stored in the node
 * return SUCCESS
 * @param artistId
 * @return
 */

// TODO: add function to most played list - RemoveArtistFromListById(int artistId)
StatusType MusicManager::RemoveArtist(int artistId) {
    if (numberOfArtists == 0) {
        // There are no artists so this counts as a case where no artist with the input ID exists
        return FAILURE;
    }
    shared_ptr<ArtistNode> artist = artistTree->Find(artistId);
    if (!artist) {
        // There is no artist with the input ID
        return FAILURE;
    }
    Artist &artistObj = artist->GetData();
    for (int i = 0; i < artistObj.GetNumberOfSongs(); ++i) {
        if (artistObj[i].GetSongId() == -1) {
            // This song has already been deleted in a previous iteration of the loop
            continue;
        }
        shared_ptr<ArtistPlaysNode> artistPlays = artistObj[i].GetPtrToArtistNode();
        shared_ptr<SongPlaysNode> songPlaysTree = artistPlays->GetData().GetSongPlaysTree();
        songPlaysTree->DeleteTree();
    }
    // TODO: finish this function
    return INVALID_INPUT;
}

StatusType MusicManager::AddToSongCount(int artistId, int songID) {
    shared_ptr<ArtistNode> node = this->artistTree->Find(artistId);
    if (node == nullptr) {
        return FAILURE;
    }
    if (node->GetData().GetNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    int newNumOfPlays = node->GetData()[songID].getNumberOfPlays() + 1;
    //update the number of streams at songArray
    node->GetData()[songID].setNumberOfPlays(newNumOfPlays);

    //getting the pointers to the relevant ArtistPlaysTree, SongsPlaysTree and plays list node
    shared_ptr<SongPlaysNode> songNode = node->GetData()[songID].GetPtrToSongNode();
    shared_ptr<ArtistPlaysNode> artistNode = node->GetData()[songID].getPtrToArtistIdPlaysTree();
    shared_ptr<MostPlayedListNode> PlaysListNode = node->GetData()[songID].GetPtrToArtistNode()->GetData().getPtrToListNode();

    SongPlaysNode newSongNode = SongPlaysNode(songID, songNode->GetData());
    shared_ptr<SongPlaysNode> newPtrToSongNode = make_shared<SongPlaysNode>(newSongNode);

    //case in which there is a matching playsNode to this song
    if (newNumOfPlays == PlaysListNode->getNext()->getNumberOfPlays()) {
        //there is not matching artistTree to this node
        if(PlaysListNode->getNext()->getArtistPlaysTree()->Find(artistId)== nullptr){
            ArtistPlaysNode newArtistNode = ArtistPlaysNode(artistId, artistNode->GetData());
            shared_ptr<ArtistPlaysNode> newPtrToArtistNode = make_shared<ArtistPlaysNode>(newArtistNode);
            PlaysListNode->getNext()->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
            newPtrToArtistNode->GetData().GetSongPlaysTree()->AddNode(newPtrToSongNode);
            node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
            //we have a new lowest artistID, and new lowet songID
            if(PlaysListNode->GetPtrToLowestArtist()->GetData().GetArtistId() > artistId ) {
                PlaysListNode->setPtrToLowestArtistId(newPtrToArtistNode);
                PlaysListNode->SetPtrToLowestSong(newPtrToSongNode);
                //this is the last playsListNode, so it contains the most recommended songs
                if(PlaysListNode->getNext() == nullptr){
                    this->ptrToMostRecommended=PlaysListNode;
                }
            }
            node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
        }
        //a matching artistTree is already exist
        else{
            PlaysListNode->getArtistPlaysTree()->Find(artistId)->GetData().GetSongPlaysTree()->AddNode(newPtrToSongNode);
            node->GetData().operator[](songID).SetPtrToArtistNode(PlaysListNode->getArtistPlaysTree()->Find(artistId));
            //we have a new lowest songID
            if(PlaysListNode->getArtistPlaysTree()->Find(artistId)->GetData().GetPtrToLowestSongId()->GetData().GetSongId() > songID){
                PlaysListNode->getArtistPlaysTree()->Find(artistId)->GetData().SetPtrToLowestSongId(newPtrToSongNode);
                //this is the last playsListNode, so it contains the most recommended songs
                if(PlaysListNode->getNext()== nullptr){
                    this->ptrToMostRecommended=PlaysListNode;
                }
            }
        }
    }
    //need to create new SongsPlayNode, it will always be after the current node
    else {
        MostPlayedListNode newPlayListNode = MostPlayedListNode(newNumOfPlays, PlaysListNode, PlaysListNode->getNext());
        shared_ptr<MostPlayedListNode> newPtrToListNode = make_shared<MostPlayedListNode>(newPlayListNode);
        //that was the last link in the list, now we have a new one
        if(PlaysListNode->getNext() == nullptr){
            this->ptrToMostRecommended = newPtrToListNode;
        }
        else {
            PlaysListNode->getNext()->setPrevious(newPtrToListNode);
        }
        PlaysListNode->setNext(newPtrToListNode);
        ArtistPlaysNode newArtistNode = ArtistPlaysNode(artistId, artistNode->GetData());
        shared_ptr<ArtistPlaysNode> newPtrToArtistNode = make_shared<ArtistPlaysNode>(newArtistNode);
        PlaysListNode->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
        newPtrToArtistNode->GetData().GetSongPlaysTree()->AddNode(newPtrToSongNode);
        PlaysListNode->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
        newPlayListNode.SetPtrToLowestSong(newPtrToSongNode);
        newPlayListNode.setPtrToLowestArtistId(newPtrToArtistNode);
        newPtrToArtistNode->GetData().SetPtrToLowestSongId(newPtrToSongNode);
        node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
        }

    //the song was alone in the artistPlaysTree, we  need to delete the artistPlaysTree
    if(songNode->GetRight()== nullptr && songNode->GetLeft()== nullptr && songNode->GetFather()== nullptr) {
        //the artist is alone in the MostPlaysListNode we need to remove the link
        if(artistNode->GetRight()== nullptr && artistNode->GetLeft()== nullptr && artistNode->GetFather()== nullptr){
            artistNode->RemoveNode(songID);
            PlaysListNode->getArtistPlaysTree()->DeleteTree(artistNode);
            PlaysListNode->GetPrevious()->setNext(PlaysListNode->getNext());
            if(PlaysListNode->getNext()!= nullptr){
                PlaysListNode->getNext()->setPrevious(PlaysListNode->GetPrevious());
            }
            PlaysListNode.reset();
        }
        //there are more artists in this artistsPlaysNode
        else{
            artistNode->RemoveNode(songID);
            PlaysListNode->getArtistPlaysTree()->RemoveNode(artistId);
        }
    }
    //there are more songs in the ArtistsPlaysTree
    else{
        artistNode->RemoveNode(songID);
    }
    node->GetData().operator[](songID).SetPtrToSongNode(newPtrToSongNode);
    return SUCCESS;
}

StatusType MusicManager::NumberOfStreams(int artistId, int songID, int *streams) {
    shared_ptr<ArtistNode> node = this->artistTree->Find(artistId);
    if (node == nullptr) {
        return FAILURE;
    }
    if (node->GetData().GetNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    *streams = node->GetData()[songID].getNumberOfPlays();
    return SUCCESS;
}

StatusType MusicManager::GetRecommendedSongs(int numOfSongs, int *artist, int *songs) {
    if (numOfSongs > this->numberOfSongs) {
        return FAILURE;
    }
    shared_ptr<SongPlaysNode> RecommendedSong = this->ptrToMostRecommended->GetPtrToLowestSong();
    shared_ptr<ArtistPlaysNode> RecommendedArtist = this->ptrToMostRecommended->GetPtrToLowestArtist();
    int i = 0;
    while (numOfSongs > 0) {
        //finish printing all the songs in this tree, should move to next artist in line
        if (RecommendedSong == nullptr) {
            RecommendedArtist = RecommendedArtist->GetNextNode(RecommendedArtist);
            //finish printing all the songs with K plays, should move to previous node
            if (RecommendedArtist == nullptr) {
                RecommendedSong = RecommendedSong->GetData().GetPtrToListNode()->GetPrevious()->GetPtrToLowestSong();
                RecommendedArtist = RecommendedArtist->GetData().getPtrToListNode()->GetPrevious()->GetPtrToLowestArtist();
            }
            //should get ptr to lowest song node
            else {
                RecommendedSong = RecommendedArtist->GetData().GetPtrToLowestSongId();
            }
        }
        artist[i] = RecommendedSong->GetData().GetArtistId();
        songs[i] = RecommendedSong->GetData().GetSongId();

        RecommendedSong = RecommendedSong->GetNextNode(RecommendedSong);
        i++;
        numOfSongs--;
    }
    return SUCCESS;
}

MusicManager::~MusicManager() {

}
