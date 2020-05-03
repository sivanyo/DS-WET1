//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYS_H
#define WET1_ARTISTPLAYS_H

#include <memory>
#include "../SongPlays/SongPlays.h"

using std::shared_ptr;
using std::make_shared;

//class SongPlaysNode;

class MostPlayedListNode;

class ArtistPlays {
private:
    int artistId;
    shared_ptr<SongPlaysNode> SongPlaysTree;
    shared_ptr<SongPlaysNode> ptrToLowestSongId;
    shared_ptr<MostPlayedListNode> ptrToListNode;
public:
    explicit ArtistPlays(int artistId);
    ArtistPlays(int artistId, shared_ptr<MostPlayedListNode> ptrToListNode);
    ArtistPlays(int artistId, shared_ptr<SongPlaysNode> ptrToSongPlaysTree, shared_ptr<SongPlaysNode> ptrToLowestSongId,
                    shared_ptr<MostPlayedListNode> ptrToListNode);

    const shared_ptr<SongPlaysNode> &GetPtrToLowestSongId() const;

    int GetArtistId();

    const shared_ptr<MostPlayedListNode> &getPtrToListNode() const;

    shared_ptr<SongPlaysNode> GetSongPlaysTree();

    void SetSongPlaysTree(shared_ptr<SongPlaysNode> ptr);

    void SetPtrToLowestSongId(shared_ptr<SongPlaysNode> ptrToLowestSongId);

    void SetPtrToListNode(shared_ptr<MostPlayedListNode> ptr);
};

typedef AvlTree<int, ArtistPlays> ArtistPlaysNode;

#endif //WET1_ARTISTPLAYS_H
