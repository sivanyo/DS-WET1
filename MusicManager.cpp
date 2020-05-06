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
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
        this->artistTree.Remove(artistId);
        return ALLOCATION_ERROR;
    }
    // Creating ArtistPlaysNode object to store SongTree
    ArtistPlaysNode *artistPlaysNode = this->mostPlayedList->getArtistPlaysTree()->InsertGetNode(artistId, artistPlays);
    if (!artistPlaysNode) {
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
        this->artistTree.Remove(artistId);
        delete artistPlays;
        return ALLOCATION_ERROR;
    }
    // Creating SongPlaysTree, to store SongPlaysNode
    SongPlaysTree *songsTree = new SongPlaysTree();
    if (!songsTree) {
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
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
            if (numberOfArtists == 0) {
                delete this->mostPlayedList;
            }
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
        // Getting the songs tree where the current song is stored
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
    ArtistNode *artistNode = this->artistTree.Find(artistId);
    if (artistNode == nullptr) {
        return FAILURE;
    }
    if (artistNode->getValue()->getNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    int newNumOfPlays = artistNode->getValue()->operator[](songID)->getNumberOfPlays() + 1;
    // update the number of streams at songArray
    artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);

    // getting the pointers to the relevant ArtistPlaysTree, SongsPlaysTree and plays list artistNode
    SongPlaysNode *songNode = artistNode->getValue()->operator[](songID)->getPtrToSongNodeInPlaysTree();
    ArtistPlaysNode *artistPlaysNode = artistNode->getValue()->operator[](songID)->getPtrToArtistIdPlaysTree();
    MostPlayedListNode *playsListNode = artistPlaysNode->getValue()->getPtrToListNode();
    ArtistPlaysTree *artistPlays = playsListNode->getArtistPlaysTree();
    // save the value of the artistNode for the next insert action
    SongPlays *oSongPlays = songNode->getValue();
    SongPlays *songPlays = new SongPlays(songID, artistId, nullptr);
    if (!songPlays) {
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        return ALLOCATION_ERROR;
    }
    songPlays->setNumberOfPlays(newNumOfPlays);
    songPlays->incrementNumberOfPlays();


    // we need to add the song at the end of the linked list
    if (playsListNode->getNext()->getNumberOfPlays() != newNumOfPlays) {
        auto *newPlayListNode = new MostPlayedListNode(newNumOfPlays, playsListNode, nullptr);
        if (!newPlayListNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            return ALLOCATION_ERROR;
        }
        ArtistPlaysTree *nArtistTree = new ArtistPlaysTree();
        if (!nArtistTree) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete newPlayListNode;
            return ALLOCATION_ERROR;
        }
        auto *nArtist = new ArtistPlays(artistId, newPlayListNode);
        if (!nArtist) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nArtistTree;
            delete newPlayListNode;
            return ALLOCATION_ERROR;
        }
        ArtistPlaysNode *newPtrToArtistNode = newPlayListNode->getArtistPlaysTree()->InsertGetNode(
                artistId, nArtist);
        if (!newPtrToArtistNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nArtist;
            delete nArtistTree;
            delete newPlayListNode;
            return ALLOCATION_ERROR;
        }
        SongPlaysTree *nSongTree = new SongPlaysTree();
        if (!nSongTree) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete newPtrToArtistNode;
            delete nArtist;
            delete nArtistTree;
            delete newPlayListNode;
            return ALLOCATION_ERROR;
        }
        SongPlaysNode *nSongNode = nSongTree->InsertGetNode(songID, songPlays);
        if (!nSongNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nSongTree;
            delete newPtrToArtistNode;
            delete nArtist;
            delete nArtistTree;
            delete newPlayListNode;
            return ALLOCATION_ERROR;
        }
        nArtist->setSongPlaysTree(nSongTree);
        artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(newPtrToArtistNode);
        artistNode->getValue()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
        nSongNode->getValue()->setPtrToSong(artistNode->getValue()->operator[](songID));
        playsListNode->setNext(newPlayListNode);
        newPlayListNode->setPrevious(playsListNode);
        newPlayListNode->setNext(playsListNode->getNext());
        if(newPlayListNode->getNext()== nullptr){
            this->ptrToMostRecommended = newPlayListNode;
        }
    }
    else {
        //there is a matching node with number of plays
        MostPlayedListNode *nextNode = playsListNode->getNext();
        ArtistPlaysNode *nArtistPlaysNode = nextNode->getArtistPlaysTree()->Find(artistId);
        if (nArtistPlaysNode) {
            // This artist already has songs with this number of plays.
            SongPlaysNode *nSongNode = artistPlaysNode->getValue()->getSongPlaysTree()->InsertGetNode(songID, songPlays);
            if (!nSongNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                return ALLOCATION_ERROR;
            }
            artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(artistPlaysNode);
            artistNode->getValue()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
            nSongNode->getValue()->setPtrToSong(artistNode->getValue()->operator[](songID));
            if (nextNode->getPtrToLowestSongId()->getKey() > songID) {
                nextNode->setPtrToLowestSongId(nSongNode);
                artistPlaysNode->getValue()->setPtrToLowestSongId(nSongNode);
            }
        } else {
            // This artist doesn't have any songs with this number of plays,
            // need to add him and then add his songs.
            ArtistPlays *nArtistPlays = new ArtistPlays(artistId, nextNode);
            if (!nArtistPlays) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                return ALLOCATION_ERROR;
            }
            ArtistPlaysNode *nArtistPlaysNode = nextNode->getArtistPlaysTree()->InsertGetNode(artistId, nArtistPlays);
            if (!nArtistPlaysNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nArtistPlays;
                return ALLOCATION_ERROR;
            }
            SongPlaysTree *nSongTree = new SongPlaysTree();
            if (!nSongTree) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nArtistPlays;
                nextNode->getArtistPlaysTree()->Remove(artistId);
                return ALLOCATION_ERROR;
            }
            SongPlaysNode *nSongNode = artistPlaysNode->getValue()->getSongPlaysTree()->InsertGetNode(songID, songPlays);
            if (!nSongNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            }
            artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(artistPlaysNode);
            artistNode->getValue()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
            nSongNode->getValue()->setPtrToSong(artistNode->getValue()->operator[](songID));
            if (nextNode->getPtrToLowestSongId()->getKey() > songID) {
                nextNode->setPtrToLowestSongId(nSongNode);
                artistPlaysNode->getValue()->setPtrToLowestSongId(nSongNode);
            }
        }
    }

    //the song was alone in the artistPlaysTree, we  need to delete the artistPlaysTree
    if (songNode->getRight() == nullptr && songNode->getLeft() == nullptr && songNode->getParent() == nullptr) {
        //the artist is alone in the MostPlaysListNode we need to remove the link
        if (artistPlaysNode->getRight() == nullptr && artistPlaysNode->getLeft() == nullptr &&
            artistPlaysNode->getParent() == nullptr) {
            artistTree.Remove(songID);
            playsListNode->getPrevious()->setNext(playsListNode->getNext());
            if (playsListNode->getNext() != nullptr) {
                playsListNode->getNext()->setPrevious(playsListNode->getPrevious());
            }
            playsListNode->getArtistPlaysTree()->Remove(artistId);
            delete playsListNode;//might leak
        }
            //there are more artists in this artistsPlaysNode
        else {
            artistTree.Remove(songID);
            playsListNode->getArtistPlaysTree()->Remove(artistId);
        }
    }
    return SUCCESS;
}

StatusType MusicManager::NumberOfStreams(int artistId, int songID, int *streams) {
    ArtistNode *node = this->artistTree.Find(artistId);
    if (node == nullptr) {
        return FAILURE;
    }
    if (node->getValue()->getNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    *streams = node->getValue()->operator[](songID)->getNumberOfPlays();
    return SUCCESS;
}

StatusType MusicManager::GetRecommendedSongs(int numOfSongs, int *artist, int *songs) {
    if (numOfSongs > this->numberOfSongs) {
        return FAILURE;
    }
    SongPlaysNode *RecommendedSong = this->ptrToMostRecommended->getPtrToLowestSongId();
    ArtistPlaysNode *RecommendedArtist = this->ptrToMostRecommended->getPtrToLowestArtistId();
    int i = 0;
    while (numOfSongs > 0) {
        //finish printing all the songs in this tree, should move to next artist in line
        if (RecommendedSong == nullptr) {
            RecommendedArtist = RecommendedArtist->getNext();
            //finish printing all the songs with K plays, should move to previous node
            if (RecommendedArtist == nullptr) {
                RecommendedSong = RecommendedSong->getValue()->getPtrToListNode()->getPrevious()->getPtrToLowestSongId();
                RecommendedArtist = RecommendedArtist->getValue()->getPtrToListNode()->getPrevious()->getPtrToLowestArtistId();
            }
                //should get ptr to lowest song node
            else {
                RecommendedSong = RecommendedArtist->getValue()->getPtrToLowestSongId();
            }
        }
        artist[i] = RecommendedSong->getValue()->getArtistId();
        songs[i] = RecommendedSong->getValue()->getSongId();

        RecommendedSong = RecommendedSong->getNext();
        i++;
        numOfSongs--;
    }
    return SUCCESS;
}

MusicManager::~MusicManager() {
    //delete this->artistTree;
    delete this->mostPlayedList;
}

StatusType MusicManager::addSongAtEndOfList(int newNumOfPlays, MostPlayedListNode *playsListNode, SongPlays *songPlays,
                                            ArtistNode *artistNode, int songID, int artistId) {
    auto *newPlayListNode = new MostPlayedListNode(newNumOfPlays, playsListNode, nullptr);
    if (!newPlayListNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        return ALLOCATION_ERROR;
    }
    ArtistPlaysTree *nArtistTree = new ArtistPlaysTree();
    if (!nArtistTree) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    auto *nArtist = new ArtistPlays(artistId, newPlayListNode);
    if (!nArtist) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    ArtistPlaysNode *newPtrToArtistNode = newPlayListNode->getArtistPlaysTree()->InsertGetNode(
            artistId, nArtist);
    if (!newPtrToArtistNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete nArtist;
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    SongPlaysTree *nSongTree = new SongPlaysTree();
    if (!nSongTree) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete newPtrToArtistNode;
        delete nArtist;
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    SongPlaysNode *nSongNode = nSongTree->InsertGetNode(songID, songPlays);
    if (!nSongNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getValue()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete nSongTree;
        delete newPtrToArtistNode;
        delete nArtist;
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    nArtist->setSongPlaysTree(nSongTree);
    this->ptrToMostRecommended = newPlayListNode;
    artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(newPtrToArtistNode);
    artistNode->getValue()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
    nSongNode->getValue()->setPtrToSong(artistNode->getValue()->operator[](songID));
    playsListNode->setNext(newPlayListNode);
    newPlayListNode->setPrevious(playsListNode);

    return SUCCESS;
}

