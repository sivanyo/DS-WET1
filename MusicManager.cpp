//
// Created by Mor on 26/04/2020.
//

#include "Artist/Artist.h"
#include "MusicManager.h"

MusicManager::MusicManager() {
    this->numberOfArtists = 0;
    this->artistTree = ArtistTree();
}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    if (numberOfArtists == 0) {
        // Inserting the new artist to our Artist tree
        Artist *tempArtist = new Artist(artistId, numOfSongs);
        if (!tempArtist) {
            return ALLOCATION_ERROR;
        }
        if (this->artistTree.Insert(artistId, tempArtist) != SUCCESS) {
            delete tempArtist;
            return ALLOCATION_ERROR;
        }
        if (!this->mostPlayedList) {
            this->mostPlayedList = new MostPlayedListNode(0);
            if (!this->mostPlayedList) {
                // removal from tree should delete the data.
                this->artistTree.Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->ptrToMostRecommended = this->mostPlayedList;
            ArtistPlaysTree *tempPlaysTree = new ArtistPlaysTree();
            if (!tempArtist) {
                // removal from tree should delete the data.
                this->artistTree.Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->mostPlayedList->setArtistPlaysTree(tempPlaysTree);
        }
        if (!this->mostPlayedList->getArtistPlaysTree()) {
            ArtistPlaysTree *tempPlaysTree = new ArtistPlaysTree();
            if (!tempArtist) {
                // removal from tree should delete the data.
                this->artistTree.Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->mostPlayedList->setArtistPlaysTree(tempPlaysTree);
        }
    } else {
        if (this->artistTree.Find(artistId) != nullptr) {
            // There already exists an artist with this ID
            return FAILURE;
        }
        Artist *tempArtist = new Artist(artistId, numOfSongs);
        if (!tempArtist) {
            return ALLOCATION_ERROR;
        }
        if (this->artistTree.Insert(artistId, tempArtist) != SUCCESS) {
            delete tempArtist;
            return ALLOCATION_ERROR;
        }
    }
    // Creating ArtistPlays object to store in ArtistPlaysNode
    ArtistPlays *artistPlays = new ArtistPlays(artistId, this->mostPlayedList);
    if (!artistPlays) {
        this->artistTree.Remove(artistId);
        return ALLOCATION_ERROR;
    }
    // Creating ArtistPlaysNode object to store SongTree
    ArtistPlaysNode *artistPlaysNode = this->mostPlayedList->getArtistPlaysTree()->InsertGetNode(artistId, artistPlays);
    if (!artistPlaysNode) {
        this->artistTree.Remove(artistId);
        delete artistPlays;
        return ALLOCATION_ERROR;
    }
    // Creating SongPlaysTree, to store SongPlaysNode
    SongPlaysTree *songsTree = new SongPlaysTree();
    if (!songsTree) {
        this->artistTree.Remove(artistId);
        return ALLOCATION_ERROR;
    }
    // retrieving new artist from artist tree to update his song pointers
    ArtistNode *artistNode = this->artistTree.Find(artistId);
    Artist *artist = artistNode->getValue();
    SongPlaysNode *lowestIdSongNode;
    for (int i = 0; i < numOfSongs; ++i) {
        SongPlays *plays = new SongPlays(i, artistId, this->mostPlayedList);
        if (!plays) {
            delete songsTree;
            this->artistTree.Remove(artistId);
            return ALLOCATION_ERROR;
        }

        Song *tempSong = artist->operator[](i);
        SongPlaysNode *tempSongNode = songsTree->InsertGetNode(i, plays);
        if (i == 0) {
            // This is the song with the lowest ID, saving in case we need to update the lowest song ID pointer
            lowestIdSongNode = tempSongNode;
        }
        // Saving inside every song of this artist, the pointer to the node of that song in the artist Songs tree
        tempSong->setPtrToSongNodeInPlaysTree(tempSongNode);
        // Saving inside every song of this artist, the pointer to the node of that artist in the linked list
        tempSong->setPtrToArtistIdPlaysTree(artistPlaysNode);
        // Saving inside every song plays node of this artist, the pointer to the Song object of that song
        plays->setPtrToSong(tempSong);

    }

    if (this->mostPlayedList->getPtrToLowestArtistId()) {
        if (this->mostPlayedList->getPtrToLowestArtistId()->getKey() > artistId) {
            // The newly added artist has an ID that's lower than the current lowest artist ID,
            // updating pointers in linked list.
            this->mostPlayedList->setPtrToLowestArtistId(artistPlaysNode);
            this->mostPlayedList->setPtrToLowestSongId(lowestIdSongNode);
        }
    } else {
        // The newly added artist is the first artist so his ID is the lowest,
        // updating pointers in linked list.
        this->mostPlayedList->setPtrToLowestArtistId(artistPlaysNode);
        this->mostPlayedList->setPtrToLowestSongId(lowestIdSongNode);
    }

    this->numberOfSongs += numOfSongs;
    this->numberOfArtists++;
    return SUCCESS;
}

StatusType MusicManager::RemoveArtist(int artistId) {
    ArtistNode *artistNode = artistTree.Find(artistId);
    if (numberOfArtists == 0 || !artistNode) {
        // There are no artists so this counts as a case where no artist with the input ID exists
        return FAILURE;
    }
    Artist *artist = artistNode->getValue();
    for (int i = 0; i < artist->getNumberOfSongs(); ++i) {
        Song *tempSong = artist->operator[](i);
        // Checking if the song was already deleted from it's songs tree
        if (tempSong->getNumberOfPlays() == -1) {
            continue;
        }
        // Getting the list where the current song is stored
        MostPlayedListNode *node = tempSong->getPtrToArtistIdPlaysTree()->getValue()->getPtrToListNode();
        // Getting the Artist Plays Node of the current song
        ArtistPlaysNode *artistPlaysNode = tempSong->getPtrToArtistIdPlaysTree();
        // Getting the songs tree where the current song is stroed
        SongPlaysTree *songTree = artistPlaysNode->getValue()->getSongPlaysTree();
        // Deleting all nodes from the song plays tree, and marking the songs in the Song array as deleted
        SongPlays::DeleteSongPlaysNode(songTree->GetRoot());
        // Deleting the tree object
        delete songTree;
        // Marking as deleted to avoid invalid delete.
        songTree = nullptr;
        // Removing the artist from the list
        node->getArtistPlaysTree()->Remove(artistId);
        bool songTreeNowEmpty = false;
        if (node->getPtrToLowestArtistId()->getKey() == artistPlaysNode->getKey()) {
            // The artist we are currently removing is the one with the lowest ID for this number of plays
            // Setting a new pointer to the artist with a higher ID;
            node->setPtrToLowestArtistId(artistPlaysNode->getParent());
            // Setting a new pointer to the song of this artist with the lowest ID
            node->setPtrToLowestSongId(node->getPtrToLowestArtistId()->getValue()->getPtrToLowestSongId());
        }
        if (node->getArtistPlaysTree()->IsEmpty() && node->getNumberOfPlays() != 0) {
            // The artist tree for this node is now empty, meaning the node is now pointless and can be removed
            node->getPrevious()->setNext(node->getNext());
            node->getNext()->setPrevious(node->getPrevious());
            delete node;
        }
    }
    // Removing songs of artist from total song count.
    numberOfSongs -= artist->getNumberOfSongs();
    // Removing artist from total artist count.
    numberOfArtists--;
    artistTree.Remove(artistId);
    return SUCCESS;
}

StatusType MusicManager::AddToSongCount(int artistId, int songID) {
    shared_ptr <ArtistNode> node = this->artistTree->Find(artistId);
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
    shared_ptr <SongPlaysNode> songNode = node->GetData()[songID].GetPtrToSongNode();
    shared_ptr <ArtistPlaysNode> artistNode = node->GetData()[songID].getPtrToArtistIdPlaysTree();
    shared_ptr <MostPlayedListNode> PlaysListNode = node->GetData()[songID].GetPtrToArtistNode()->GetData().getPtrToListNode();

    SongPlaysNode newSongNode = SongPlaysNode(songID, songNode->GetData());
    shared_ptr <SongPlaysNode> newPtrToSongNode = make_shared<SongPlaysNode>(newSongNode);

    //case in which there is a matching playsNode to this song
    if (newNumOfPlays == PlaysListNode->getNext()->getNumberOfPlays()) {
        //there is not matching artistTree to this node
        if (PlaysListNode->getNext()->getArtistPlaysTree()->Find(artistId) == nullptr) {
            ArtistPlaysNode newArtistNode = ArtistPlaysNode(artistId, artistNode->GetData());
            shared_ptr <ArtistPlaysNode> newPtrToArtistNode = make_shared<ArtistPlaysNode>(newArtistNode);
            PlaysListNode->getNext()->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
            newPtrToArtistNode->GetData().GetSongPlaysTree()->AddNode(newPtrToSongNode);
            node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
            //we have a new lowest artistID, and new lowet songID
            if (PlaysListNode->GetPtrToLowestArtist()->GetData().getArtistId() > artistId) {
                PlaysListNode->setPtrToLowestArtistId(newPtrToArtistNode);
                PlaysListNode->SetPtrToLowestSong(newPtrToSongNode);
                //this is the last playsListNode, so it contains the most recommended songs
                if (PlaysListNode->getNext() == nullptr) {
                    this->ptrToMostRecommended = PlaysListNode;
                }
            }
            node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
        }
            //a matching artistTree is already exist
        else {
            PlaysListNode->getArtistPlaysTree()->Find(artistId)->GetData().GetSongPlaysTree()->AddNode(
                    newPtrToSongNode);
            node->GetData().operator[](songID).SetPtrToArtistNode(PlaysListNode->getArtistPlaysTree()->Find(artistId));
            //we have a new lowest songID
            if (PlaysListNode->getArtistPlaysTree()->Find(
                    artistId)->GetData().GetPtrToLowestSongId()->GetData().GetSongId() > songID) {
                PlaysListNode->getArtistPlaysTree()->Find(artistId)->GetData().SetPtrToLowestSongId(newPtrToSongNode);
                //this is the last playsListNode, so it contains the most recommended songs
                if (PlaysListNode->getNext() == nullptr) {
                    this->ptrToMostRecommended = PlaysListNode;
                }
            }
        }
    }
        //need to create new SongsPlayNode, it will always be after the current node
    else {
        MostPlayedListNode newPlayListNode = MostPlayedListNode(newNumOfPlays, PlaysListNode, PlaysListNode->getNext());
        shared_ptr <MostPlayedListNode> newPtrToListNode = make_shared<MostPlayedListNode>(newPlayListNode);
        //that was the last link in the list, now we have a new one
        if (PlaysListNode->getNext() == nullptr) {
            this->ptrToMostRecommended = newPtrToListNode;
        } else {
            PlaysListNode->getNext()->setPrevious(newPtrToListNode);
        }
        PlaysListNode->setNext(newPtrToListNode);
        ArtistPlaysNode newArtistNode = ArtistPlaysNode(artistId, artistNode->GetData());
        shared_ptr <ArtistPlaysNode> newPtrToArtistNode = make_shared<ArtistPlaysNode>(newArtistNode);
        PlaysListNode->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
        newPtrToArtistNode->GetData().GetSongPlaysTree()->AddNode(newPtrToSongNode);
        PlaysListNode->getArtistPlaysTree()->AddNode(newPtrToArtistNode);
        newPlayListNode.SetPtrToLowestSong(newPtrToSongNode);
        newPlayListNode.setPtrToLowestArtistId(newPtrToArtistNode);
        newPtrToArtistNode->GetData().SetPtrToLowestSongId(newPtrToSongNode);
        node->GetData().operator[](songID).SetPtrToArtistNode(newPtrToArtistNode);
    }

    //the song was alone in the artistPlaysTree, we  need to delete the artistPlaysTree
    if (songNode->GetRight() == nullptr && songNode->GetLeft() == nullptr && songNode->GetFather() == nullptr) {
        //the artist is alone in the MostPlaysListNode we need to remove the link
        if (artistNode->GetRight() == nullptr && artistNode->GetLeft() == nullptr &&
            artistNode->GetFather() == nullptr) {
            artistNode->RemoveNode(songID);
            PlaysListNode->getArtistPlaysTree()->DeleteTree(artistNode);
            PlaysListNode->GetPrevious()->setNext(PlaysListNode->getNext());
            if (PlaysListNode->getNext() != nullptr) {
                PlaysListNode->getNext()->setPrevious(PlaysListNode->GetPrevious());
            }
            PlaysListNode.reset();
        }
            //there are more artists in this artistsPlaysNode
        else {
            artistNode->RemoveNode(songID);
            PlaysListNode->getArtistPlaysTree()->RemoveNode(artistId);
        }
    }
        //there are more songs in the ArtistsPlaysTree
    else {
        artistNode->RemoveNode(songID);
    }
    node->GetData().operator[](songID).SetPtrToSongNode(newPtrToSongNode);
    return SUCCESS;
}

StatusType MusicManager::NumberOfStreams(int artistId, int songID, int *streams) {
    shared_ptr <ArtistNode> node = this->artistTree->Find(artistId);
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
    shared_ptr <SongPlaysNode> RecommendedSong = this->ptrToMostRecommended->GetPtrToLowestSong();
    shared_ptr <ArtistPlaysNode> RecommendedArtist = this->ptrToMostRecommended->GetPtrToLowestArtist();
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
    //delete this->artistTree;
    delete this->mostPlayedList;
}