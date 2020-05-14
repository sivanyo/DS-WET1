//
// Created by Mor on 26/04/2020.
//

#include "Artist.h"
#include "MusicManager.h"

MusicManager::MusicManager() : artistTree(new ArtistTree()), mostPlayedList(nullptr),
                               ptrToMostRecommended(nullptr), numberOfArtists(0), numberOfSongs(0) {
}

StatusType MusicManager::AddArtist(int artistId, int numOfSongs) {
    if (numberOfArtists == 0) {
        // Inserting the new artist to our Artist tree
        if (this->artistTree->Find(artistId) != nullptr) {
            //there is already such artist
            return FAILURE;
        }
        Artist *tempArtist = new Artist(artistId, numOfSongs);
        if (!tempArtist) {
            return ALLOCATION_ERROR;
        }
        this->artistTree->Insert(artistId, tempArtist);
        if (!this->mostPlayedList) {
            this->mostPlayedList = new MostPlayedListNode(0);
            if (!this->mostPlayedList) {
                // removal from tree should delete the data.
                this->artistTree->Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->ptrToMostRecommended = this->mostPlayedList;
            ArtistPlaysTree *tempPlaysTree = new ArtistPlaysTree();
            if (!tempPlaysTree) {
                // removal from tree should delete the data.
                this->artistTree->Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->mostPlayedList->setArtistPlaysTree(tempPlaysTree);
        }
        if (!this->mostPlayedList->getArtistPlaysTree()) {
            ArtistPlaysTree *tempPlaysTree = new ArtistPlaysTree();
            if (!tempPlaysTree) {
                // removal from tree should delete the data.
                this->artistTree->Remove(artistId);
                return ALLOCATION_ERROR;
            }
            this->mostPlayedList->setArtistPlaysTree(tempPlaysTree);
        }
    } else {
        if (this->artistTree->Find(artistId) != nullptr) {
            // There already exists an artist with this ID
            return FAILURE;
        }
        Artist *tempArtist = new Artist(artistId, numOfSongs);
        if (!tempArtist) {
            return ALLOCATION_ERROR;
        }
        this->artistTree->Insert(artistId, tempArtist);
        }

    // Creating ArtistPlays object to store in ArtistPlaysNode
    ArtistPlays *artistPlays = new ArtistPlays(artistId, this->mostPlayedList);
    if (!artistPlays) {
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
        this->artistTree->Remove(artistId);
        return ALLOCATION_ERROR;
    }
    // Creating ArtistPlaysNode object to store SongTree
    this->mostPlayedList->getArtistPlaysTree()->Insert(artistId, artistPlays);
    ArtistPlaysNode *artistPlaysNode = this->mostPlayedList->getArtistPlaysTree()->Find(artistId);
    if (!artistPlaysNode) {
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
        this->artistTree->Remove(artistId);
        delete artistPlays;
        return ALLOCATION_ERROR;
    }
    // Creating SongPlaysTree, to store SongPlaysNode
    SongPlaysTree *songsTree = new SongPlaysTree();
    if (!songsTree) {
        if (numberOfArtists == 0) {
            delete this->mostPlayedList;
        }
        this->artistTree->Remove(artistId);
        return ALLOCATION_ERROR;
    }
    artistPlaysNode->getData()->setSongPlaysTree(songsTree);
    // retrieving new artist from artist tree to update his song pointers
    ArtistNode *artistNode = this->artistTree->Find(artistId);
    Artist *artist = artistNode->getData();
    SongPlaysNode *lowestIdSongNode;
    for (int i = 0; i < numOfSongs; ++i) {
        SongPlays *plays = new SongPlays(i, artistId, this->mostPlayedList);
        if (!plays) {
            delete songsTree;
            if (numberOfArtists == 0) {
                delete this->mostPlayedList;
            }
            this->artistTree->Remove(artistId);
            return ALLOCATION_ERROR;
        }

        Song *tempSong = artist->operator[](i);
        songsTree->Insert(i,plays);
        SongPlaysNode *tempSongNode = songsTree->Find(i);
        if (i == 0) {
            // This is the song with the lowest ID, saving in case we need to update the lowest song ID pointer
            lowestIdSongNode = tempSongNode;
        }
        // Saving inside every song of this artist, the pointer to the node of that song in the artist Songs tree
        tempSong->setPtrToSongNodeInPlaysTree(tempSongNode);
        // Saving inside every song of this artist, the pointer to the node of that artist in the linked list
//        tempSong->setPtrToArtistIdPlaysTree(artistPlaysNode); // REMOVED TO PREVENT SEGFAULT
        // Saving inside every song plays node of this artist, the pointer to the Song object of that song
        plays->setPtrToSong(tempSong);

    }
    // Setting pointer in artist node to point to the song with the lowest ID with 0 plays (song ID 0 for now)
    artistPlaysNode->getData()->setPtrToLowestSongId(lowestIdSongNode);
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
    ArtistNode *artistNode = artistTree->Find(artistId);
    if (numberOfArtists == 0 || !artistNode) {
        // There are no artists so this counts as a case where no artist with the input ID exists
        return FAILURE;
    }
    int currentMostRecommended = this->ptrToMostRecommended->getNumberOfPlays();
    Artist *artist = artistNode->getData();
    for (int i = 0; i < artist->getNumberOfSongs(); ++i) {
        Song *tempSong = artist->operator[](i);
        // Checking if the song was already deleted from it's songs tree
        if (tempSong->getNumberOfPlays() == -1) {
            continue;
        }
        // Getting the list where the current song is stored
        MostPlayedListNode *node = tempSong->getPtrToSongNodeInPlaysTree()->getData()->getPtrToListNode();
        ArtistPlaysNode *artistPlaysNode = node->getArtistPlaysTree()->Find(artistId);
        // Getting the songs tree where the current song is stored
        SongPlaysTree *songTree = artistPlaysNode->getData()->getSongPlaysTree();
        // Deleting all nodes from the song plays tree, and marking the songs in the Song array as deleted
        SongPlays::DeleteSongPlaysNode(songTree->GetRoot());
        // Deleting the tree object
        //delete songTree;
        // Marking as deleted to avoid invalid delete.
        songTree = nullptr;
        artistPlaysNode->getData()->setSongPlaysTree(nullptr);
        if (node->getPtrToLowestArtistId()->getKey() == artistPlaysNode->getKey()) {
            // The artist we are currently removing is the one with the lowest ID for this number of plays
            // Setting a new pointer to the artist with a higher ID;
            node->setPtrToLowestArtistId(artistPlaysNode->getNext());
            if (node->getPtrToLowestArtistId()) {
                // There really is another node in the aritstplays tree
                // Setting a new pointer to the song of this artist with the lowest ID
                node->setPtrToLowestSongId(node->getPtrToLowestArtistId()->getData()->getPtrToLowestSongId());
            } else {
                // this artist was alone in this node
                if (node->getNumberOfPlays() == ptrToMostRecommended->getNumberOfPlays()) {
                    // the song we are deleting is the most recommended song
                    // now this node is no longer the most recommended
                    if(node->getPrevious()){
                        ptrToMostRecommended = node->getPrevious();
                    }
                    else{
                        ptrToMostRecommended= nullptr;
                    }
//                    delete temp;
                }
            }
        }
        // Removing the artist from the list
        if (node->getArtistPlaysTree()) {
            //artistPlaysNode->removeValue();
            node->getArtistPlaysTree()->Remove(artistId);
            if (!node->getArtistPlaysTree()->GetRoot()) {
                delete node->getArtistPlaysTree();
                node->setArtistPlaysTree(nullptr);
            }
        }
        if (!node->getArtistPlaysTree() && node->getNumberOfPlays() != 0) {
            // The artist tree for this node is now empty, meaning the node is now pointless and can be removed
            node->getPrevious()->setNext(node->getNext());
            if (node->getNext()) {
                node->getNext()->setPrevious(node->getPrevious());
            }
            //node->setArtistPlaysTree(nullptr);
            delete node;
        }
    }
    // Removing songs of artist from total song count.
    numberOfSongs -= artist->getNumberOfSongs();
    // Removing artist from total artist count.
    numberOfArtists--;
    artistTree->Remove(artistId);
    return SUCCESS;
}

StatusType MusicManager::AddToSongCount(int artistId, int songID) {
    // Check if the artist exists
    ArtistNode *artistNode = this->artistTree->Find(artistId);
    if (artistNode == nullptr) {
        return FAILURE;
    }
    // Check if the artist has a song with the given ID
    if (artistNode->getData()->getNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    int newNumOfPlays = artistNode->getData()->operator[](songID)->getNumberOfPlays() + 1;
    // update the number of streams at songArray
    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);

    // getting the pointers to the relevant ArtistPlaysTree, SongsPlaysTree and plays list artistNode
    SongPlaysNode *songNode = artistNode->getData()->operator[](songID)->getPtrToSongNodeInPlaysTree();

    MostPlayedListNode *playsListNode = songNode->getData()->getPtrToListNode();
    ArtistPlaysNode *artistPlaysNode = playsListNode->getArtistPlaysTree()->Find(artistId);
    // Creating a new song plays object to insert to the next linked list node
    SongPlays *songPlays = new SongPlays(songID, artistId, nullptr);
    if (!songPlays) {
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        return ALLOCATION_ERROR;
    }
    songPlays->setNumberOfPlays(newNumOfPlays);

    // Checking if the song is at the current end of the linked list
    if (playsListNode->getNext()) {
        // The song is not at the end of the linked list, checking if the next node is the right one
        if (playsListNode->getNext()->getNumberOfPlays() == newNumOfPlays) {
            //there is a matching node with number of plays
            MostPlayedListNode *nextNode = playsListNode->getNext();
            ArtistPlaysNode *nArtistPlaysNode = nextNode->getArtistPlaysTree()->Find(artistId);
            if (nArtistPlaysNode) {
                // This artist already has songs with this number of plays.
                nArtistPlaysNode->getData()->getSongPlaysTree()->Insert(songID,
                                                                               songPlays);
                SongPlaysNode *nSongNode = nArtistPlaysNode->getData()->getSongPlaysTree()->Find(songID);
                if (!nSongNode) {
                    // Rolling back changes to number of plays
                    songPlays->DecrementNumberOfPlays();
                    newNumOfPlays--;
                    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                    return ALLOCATION_ERROR;
                }
                // Updating pointers in Song object to the new SongPlaysNode
//                artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(nArtistPlaysNode); // REMOVED TO PREVENT SEGFAULT
                artistNode->getData()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
                // Updating pointers in the new SongPlaysNode object to the Song object
                nSongNode->getData()->setPtrToSong(artistNode->getData()->operator[](songID));
                nSongNode->getData()->setPtrToListNode(nextNode);
                if (nextNode->getPtrToLowestArtistId()->getKey() == artistId) {
                    // The artist with a new song count is already the artist with the lowest ID on this node,
                    // only need to check the song ID
                    if (nextNode->getPtrToLowestSongId()->getKey() > songID) {
                        nextNode->setPtrToLowestSongId(nSongNode);
                        nArtistPlaysNode->getData()->setPtrToLowestSongId(nSongNode);
                    }
                }
                if (nArtistPlaysNode->getData()->getPtrToLowestSongId()->getKey() > songID) {
                    // The new song has a lower ID than the previous song for this artist with this number
                    // of plays, so we need to replace the pointer
                    nArtistPlaysNode->getData()->setPtrToLowestSongId(nSongNode);
                }
            } else {
                // This artist doesn't have any songs with this number of plays,
                // need to add him and then add his songs.
                ArtistPlays *nArtistPlays = new ArtistPlays(artistId, nextNode);
                if (!nArtistPlays) {
                    // Rolling back changes to number of plays
                    songPlays->DecrementNumberOfPlays();
                    newNumOfPlays--;
                    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                    return ALLOCATION_ERROR;
                }

                nextNode->getArtistPlaysTree()->Insert(artistId,
                                                              nArtistPlays);
                ArtistPlaysNode *nArtistPlaysNode = nextNode->getArtistPlaysTree()->Find(artistId);
                if (!nArtistPlaysNode) {
                    // Rolling back changes to number of plays
                    songPlays->DecrementNumberOfPlays();
                    newNumOfPlays--;
                    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                    delete nArtistPlays;
                    return ALLOCATION_ERROR;
                }
                SongPlaysTree *nSongTree = new SongPlaysTree();
                if (!nSongTree) {
                    // Rolling back changes to number of plays
                    songPlays->DecrementNumberOfPlays();
                    newNumOfPlays--;
                    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                    nextNode->getArtistPlaysTree()->Remove(artistId);
                    return ALLOCATION_ERROR;
                }
                nArtistPlays->setSongPlaysTree(nSongTree);
                nArtistPlaysNode->getData()->getSongPlaysTree()->Insert(songID,
                                                                               songPlays);
                SongPlaysNode *nSongNode = nArtistPlaysNode->getData()->getSongPlaysTree()->Find(songID);
                if (!nSongNode) {
                    // Rolling back changes to number of plays
                    songPlays->DecrementNumberOfPlays();
                    newNumOfPlays--;
                    artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                    nextNode->getArtistPlaysTree()->Remove(artistId);
                    return ALLOCATION_ERROR;
                }
                nArtistPlaysNode->getData()->setPtrToLowestSongId(nSongNode);
                // Updating pointers in Song object to the new SongPlaysNode
//                artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(nArtistPlaysNode); // REMOVED TO PREVENT SEGFAULT
                artistNode->getData()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
                // Updating pointers in the new SongPlaysNode object to the Song object
                nSongNode->getData()->setPtrToSong(artistNode->getData()->operator[](songID));
                nSongNode->getData()->setPtrToListNode(nextNode);
                if (nextNode->getPtrToLowestArtistId()->getKey() > artistId) {
                    // The newly added artist has a lower ID than the one of the previous lowest artist
                    // for this node, so we need to replace him.
                    nextNode->setPtrToLowestArtistId(nArtistPlaysNode);
                    // We also need to replace the pointer to the song with the lowest ID
                    nextNode->setPtrToLowestSongId(nSongNode);
                }
            }
        } else {
            // The next node is not the right one, we need to create a new one and then add the song to it
            auto *nPlayListNode = new MostPlayedListNode(newNumOfPlays, playsListNode, playsListNode->getNext());
            if (!nPlayListNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                return ALLOCATION_ERROR;
            }
            ArtistPlaysTree *nArtistPlaysTree = new ArtistPlaysTree();
            if (!nArtistPlaysTree) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nPlayListNode;
                return ALLOCATION_ERROR;
            }
            auto *nArtistPlays = new ArtistPlays(artistId, nPlayListNode);
            if (!nArtistPlays) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nArtistPlaysTree;
                delete nPlayListNode;
                return ALLOCATION_ERROR;
            }
            nPlayListNode->setArtistPlaysTree(nArtistPlaysTree);
            nPlayListNode->getArtistPlaysTree()->Insert(artistId, nArtistPlays);
            ArtistPlaysNode *nArtistPlaysNode = nPlayListNode->getArtistPlaysTree()->Find(artistId);
            if (!nArtistPlaysNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nArtistPlays;
                delete nArtistPlaysTree;
                delete nPlayListNode;
                return ALLOCATION_ERROR;
            }
            SongPlaysTree *nSongTree = new SongPlaysTree();
            if (!nSongTree) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nArtistPlaysNode;
                delete nArtistPlays;
                delete nArtistPlaysTree;
                delete nPlayListNode;
                return ALLOCATION_ERROR;
            }
            nSongTree->Insert(songID, songPlays);
            SongPlaysNode *nSongNode = nSongTree->Find(songID);
            if (!nSongNode) {
                // Rolling back changes to number of plays
                songPlays->DecrementNumberOfPlays();
                newNumOfPlays--;
                artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
                delete nSongTree;
                delete nArtistPlaysNode;
                delete nArtistPlays;
                delete nArtistPlaysTree;
                delete nPlayListNode;
                return ALLOCATION_ERROR;
            }
            nArtistPlaysNode->getData()->setPtrToLowestSongId(nSongNode);
            nArtistPlays->setSongPlaysTree(nSongTree);
            // Updating pointers in Song object to the new SongPlaysNode
//            artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(nArtistPlaysNode); // REMOVED TO PREVENT SEGFAULT
            artistNode->getData()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
            // Updating pointers in the new SongPlaysNode object to the Song object
            nSongNode->getData()->setPtrToSong(artistNode->getData()->operator[](songID));
            nSongNode->getData()->setPtrToListNode(nPlayListNode);
            nPlayListNode->setPtrToLowestArtistId(nArtistPlaysNode);
            nPlayListNode->setPtrToLowestSongId(nSongNode);
            // Updating linked list pointers because we entered a new node in the middle of the list
            nPlayListNode->setNext(playsListNode->getNext());
            nPlayListNode->getNext()->setPrevious(nPlayListNode);
            playsListNode->setNext(nPlayListNode);
            nPlayListNode->setPrevious(playsListNode);
        }
    } else {
        // The song we are adding a stream to is at the end of the linked list,
        // so we need to create a new node and add the song to it
        auto *nPlayListNode = new MostPlayedListNode(newNumOfPlays, playsListNode, nullptr);
        if (!nPlayListNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            return ALLOCATION_ERROR;
        }
        ArtistPlaysTree *nArtistPlaysTree = new ArtistPlaysTree();
        if (!nArtistPlaysTree) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nPlayListNode;
            return ALLOCATION_ERROR;
        }
        nPlayListNode->setArtistPlaysTree(nArtistPlaysTree);
        auto *nArtistPlays = new ArtistPlays(artistId, nPlayListNode);
        if (!nArtistPlays) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nArtistPlaysTree;
            delete nPlayListNode;
            return ALLOCATION_ERROR;
        }
        nPlayListNode->getArtistPlaysTree()->Insert(artistId, nArtistPlays);
        ArtistPlaysNode *nArtistPlaysNode = nPlayListNode->getArtistPlaysTree()->Find(artistId);
        if (!nArtistPlaysNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nArtistPlays;
            delete nArtistPlaysTree;
            delete nPlayListNode;
            return ALLOCATION_ERROR;
        }
        SongPlaysTree *nSongTree = new SongPlaysTree();
        if (!nSongTree) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nArtistPlaysNode;
            delete nArtistPlays;
            delete nArtistPlaysTree;
            delete nPlayListNode;
            return ALLOCATION_ERROR;
        }
        nSongTree->Insert(songID, songPlays);
        SongPlaysNode *nSongNode = nSongTree->Find(songID);
        if (!nSongNode) {
            // Rolling back changes to number of plays
            songPlays->DecrementNumberOfPlays();
            newNumOfPlays--;
            artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
            delete nSongTree;
            delete nArtistPlaysNode;
            delete nArtistPlays;
            delete nArtistPlaysTree;
            delete nPlayListNode;
            return ALLOCATION_ERROR;
        }
        nArtistPlays->setSongPlaysTree(nSongTree);
        nArtistPlaysNode->getData()->setPtrToLowestSongId(nSongNode);
        // Updating pointers in Song object to the new SongPlaysNode
//        artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(nArtistPlaysNode); // REMOVED TO PREVENT SEGFAULT
        artistNode->getData()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
        // Updating pointers in the new SongPlaysNode object to the Song object
        nSongNode->getData()->setPtrToSong(artistNode->getData()->operator[](songID));
        nSongNode->getData()->setPtrToListNode(nPlayListNode);
        nPlayListNode->setPtrToLowestArtistId(nArtistPlaysNode);
        nPlayListNode->setPtrToLowestSongId(nSongNode);
        // Updating linked list pointers because we entered a new node in the end of the list
//        nPlayListNode->setNext(playsListNode->getNext());
        playsListNode->setNext(nPlayListNode);
//        nPlayListNode->setPrevious(playsListNode);
        this->ptrToMostRecommended = nPlayListNode;
    }

    if (songNode->getRight() == nullptr && songNode->getLeft() == nullptr && songNode->getParent() == nullptr) {
        // the song was alone in the artistPlaysTree, we  need to delete the artistPlaysTree
        removingSongNodeCaseAlone(artistPlaysNode, playsListNode, artistId);
    } else {
        // This is not the last song of the artist with this number of plays,
        // so we should only remove this song
        // We also need to remember to update the pointer of this list node to the new lowest song ID, if the
        // Artist ID of this artist is the lowest one in this node
        // Otherwise we just remove the song node
        removingSongNodeCaseNotAlone(playsListNode, artistId, songID, songNode, artistNode);
    }
    return SUCCESS;
}

StatusType MusicManager::NumberOfStreams(int artistId, int songID, int *streams) {
    if (!streams) {
        return INVALID_INPUT;
    }
    ArtistNode *node = this->artistTree->Find(artistId);
    if (node == nullptr) {
        return FAILURE;
    }
    if (node->getData()->getNumberOfSongs() <= songID) {
        return INVALID_INPUT;
    }
    *streams = node->getData()->operator[](songID)->getNumberOfPlays();
    return SUCCESS;
}

StatusType MusicManager::GetRecommendedSongs(int numOfSongs, int *artist, int *songs) {
    if (numOfSongs > this->numberOfSongs) {
        return FAILURE;
    }
    MostPlayedListNode *currListNode = this->ptrToMostRecommended;
    SongPlaysNode *RecommendedSong = this->ptrToMostRecommended->getPtrToLowestSongId();
    ArtistPlaysNode *RecommendedArtist = this->ptrToMostRecommended->getPtrToLowestArtistId();
    int i = 0;
    while (numOfSongs > 0) {
        // finish printing all the songs in this tree, should move to next artist in line
        if (RecommendedSong == nullptr) {
            RecommendedArtist = RecommendedArtist->getNext();
            // finish printing all the songs with K plays, should move to previous node
            if (RecommendedArtist == nullptr) {
                currListNode = currListNode->getPrevious();
                RecommendedSong = currListNode->getPtrToLowestSongId();
                RecommendedArtist = currListNode->getPtrToLowestArtistId();
            } else {
                // should get ptr to lowest song node
                RecommendedSong = RecommendedArtist->getData()->getPtrToLowestSongId();
            }
        }
        artist[i] = RecommendedSong->getData()->getArtistId();
        songs[i] = RecommendedSong->getData()->getSongId();

        RecommendedSong = RecommendedSong->getNext();
        i++;
        numOfSongs--;
    }
    return SUCCESS;
}

MusicManager::~MusicManager() {
    if (this->artistTree) {
        delete this->artistTree;
    }
    if (this->mostPlayedList) {
        MostPlayedListNode *current = this->mostPlayedList;
        MostPlayedListNode *temp = current->getNext();
        while (current) {
            temp = current->getNext();
            delete current;
            current = temp;
        }
    }
}

StatusType MusicManager::addSongAtEndOfList(int newNumOfPlays, MostPlayedListNode *playsListNode, SongPlays *songPlays,
                                            ArtistNode *artistNode, int songID, int artistId) {
    auto *newPlayListNode = new MostPlayedListNode(newNumOfPlays, playsListNode, nullptr);
    if (!newPlayListNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        return ALLOCATION_ERROR;
    }
    ArtistPlaysTree *nArtistTree = new ArtistPlaysTree();
    if (!nArtistTree) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    auto *nArtist = new ArtistPlays(artistId, newPlayListNode);
    if (!nArtist) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    newPlayListNode->getArtistPlaysTree()->Insert(artistId, nArtist);
    ArtistPlaysNode *newPtrToArtistNode = newPlayListNode->getArtistPlaysTree()->Find(artistId);
    if (!newPtrToArtistNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
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
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete newPtrToArtistNode;
        delete nArtist;
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    nSongTree->Insert(songID, songPlays);
    SongPlaysNode *nSongNode = nSongTree->Find(songID);
    if (!nSongNode) {
        // Rolling back changes to number of plays
        songPlays->DecrementNumberOfPlays();
        newNumOfPlays--;
        artistNode->getData()->operator[](songID)->setNumberOfPlays(newNumOfPlays);
        delete nSongTree;
        delete newPtrToArtistNode;
        delete nArtist;
        delete nArtistTree;
        delete newPlayListNode;
        return ALLOCATION_ERROR;
    }
    nArtist->setSongPlaysTree(nSongTree);
    this->ptrToMostRecommended = newPlayListNode;
//    artistNode->getValue()->operator[](songID)->setPtrToArtistIdPlaysTree(newPtrToArtistNode);
    artistNode->getData()->operator[](songID)->setPtrToSongNodeInPlaysTree(nSongNode);
    nSongNode->getData()->setPtrToSong(artistNode->getData()->operator[](songID));
    playsListNode->setNext(newPlayListNode);
    newPlayListNode->setPrevious(playsListNode);

    return SUCCESS;
}

void MusicManager::removingSongNodeCaseNotAlone(MostPlayedListNode *playsListNode, int artistId, int songID,
                                                SongPlaysNode *songNode, ArtistNode *artistNode) {
    ArtistPlaysNode *oArtistPlaysNode = playsListNode->getArtistPlaysTree()->Find(artistId);
    if (playsListNode->getPtrToLowestArtistId()->getKey() == artistId) {
        // The current artist is the one with the lowest ID in this list node,
        // So we need to check if the song we added a stream to is the one with the lowest ID
        // If it is, we need to update the list pointer to the following song
        if (playsListNode->getPtrToLowestSongId()->getKey() == songID) {
            playsListNode->setPtrToLowestSongId(playsListNode->getPtrToLowestSongId()->getNext());
            oArtistPlaysNode->getData()->setPtrToLowestSongId(playsListNode->getPtrToLowestSongId());
        }
    } else {
        // The current artist is not the one with the lowest ID in this list node,
        // But we still need to check if the song we're now removing is the one with the lowest ID
        // For him, if so, we need to find the next one
        if (oArtistPlaysNode->getData()->getPtrToLowestSongId()->getKey() == songID) {
            // Need to update the pointer to the next song
            oArtistPlaysNode->getData()->setPtrToLowestSongId(songNode->getNext());
        }
    }
    oArtistPlaysNode->getData()->getSongPlaysTree()->Remove(songID);
    // need to make sure that the song node we removed didn't cause invalid references in the tree or in song array
//    if (willSwap) {
  //      if ((songNode->getLeft() || songNode->getRight()) && songNode->getKey() != songID) {
            // The original node we looked at has a different ID, which means the old node was replaced with the values from a child node,
            // need to update the pointers in the song array.
    //        artistNode->getData()->operator[](songNode->getKey())->setPtrToSongNodeInPlaysTree(songNode);
        }


void MusicManager::removingSongNodeCaseAlone(ArtistPlaysNode *artistPlaysNode, MostPlayedListNode *playsListNode,
                                             int artistId) {
    if (artistPlaysNode->getRight() == nullptr && artistPlaysNode->getLeft() == nullptr &&
        artistPlaysNode->getParent() == nullptr) {
        // the artist is alone in the MostPlaysListNode we need to remove the link
        if (playsListNode->getNumberOfPlays() != 0) {
            // This is not the list node with 0 plays, meaning it is now an empty node in the middle of linked
            // list, so we can delete it
            // We also need to connect the node after it to the one before it, to make sure the linked list is still
            // properly connected
            MostPlayedListNode *prev = playsListNode->getPrevious();
            MostPlayedListNode *next = playsListNode->getNext();
            if(prev){
                prev->setNext(next);
            }

                next->setPrevious(prev);
            delete playsListNode;
        } else {
            // Removing the last artist from the 0 plays list node
            playsListNode->getArtistPlaysTree()->Remove(artistId);
            // Updating pointers to lowest song and artist ID to null because there are no
            // artists or songs in this node
            playsListNode->setPtrToLowestArtistId(nullptr);
            playsListNode->setPtrToLowestSongId(nullptr);
        }
    } else {
        // there are more artists in this artistsPlaysNode
        // We need to remove only the artist, with it's (old) reference to the song we now added a stream to.
        // We also need to remember to update the pointer of this list node to the new lowest artist ID, if the
        // artist we just removed is the previous one with the lowest ID
        ArtistPlaysNode *oArtistPlaysNode = playsListNode->getArtistPlaysTree()->Find(artistId);
        if (playsListNode->getPtrToLowestArtistId()->getKey() == artistId) {
            playsListNode->setPtrToLowestArtistId(oArtistPlaysNode->getNext());
            playsListNode->setPtrToLowestSongId(
                    playsListNode->getPtrToLowestArtistId()->getData()->getPtrToLowestSongId());
        }
        playsListNode->getArtistPlaysTree()->Remove(artistId);
    }
}
