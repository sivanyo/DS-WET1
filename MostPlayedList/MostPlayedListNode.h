//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_MOSTPLAYEDLISTNODE_H
#define WET1_MOSTPLAYEDLISTNODE_H

#include <memory>
#include "../ArtistPlays/ArtistPlays.h"
#include "../SongPlays/SongPlays.h"

using std::shared_ptr;
using std::make_shared;

typedef TreeNode<ArtistPlays> ArtistPlaysNode;

//typedef TreeNode<SongPlays> SongPlaysNode;

class MostPlayedListNode {
private:
    int numberOfPlays;
    shared_ptr<ArtistPlaysNode> artistPlaysTree;
    shared_ptr<ArtistPlaysNode> ptrToLowestArtistId;
    shared_ptr<SongPlaysNode> ptrToLowestSongId;
    shared_ptr<MostPlayedListNode> previous;
    shared_ptr<MostPlayedListNode> next;

public:
    // Create the first node in the list (0 plays)
    MostPlayedListNode(int numOfPlays);

    // Create a new node with a new highest number of plays
    MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous);

    // Create a new node with a number of plays between to values (1<2<3)
    MostPlayedListNode(int numOfPlays, shared_ptr<MostPlayedListNode> previous, shared_ptr<MostPlayedListNode> next);

    bool AddArtist(shared_ptr<ArtistPlaysNode> artistNode);

    shared_ptr<ArtistPlaysNode> GetPtrToLowestArtist();

    void SetPtrToLowestArtist(shared_ptr<ArtistPlaysNode> artistPlaysNode);

    shared_ptr<SongPlaysNode> GetPtrToLowestSong();

    void SetPtrToLowestSong(shared_ptr<SongPlaysNode> songPlaysNode);

    shared_ptr<MostPlayedListNode> GetPrevious();
};


#endif //WET1_MOSTPLAYEDLISTNODE_H
