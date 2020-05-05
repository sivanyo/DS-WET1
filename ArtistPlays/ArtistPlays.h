//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYS_H
#define WET1_ARTISTPLAYS_H

#include "../TreeNode/Tree.h"
#include "../SongPlays/SongPlays.h"

typedef Tree<SongPlays> SongPlaysTree;

class MostPlayedListNode;


class ArtistPlays {
private:
    int artistId;
    SongPlaysTree *SongPlaysTree = nullptr;
    SongPlaysNode *ptrToLowestSongId = nullptr;
    MostPlayedListNode *ptrToListNode = nullptr;
public:
    explicit ArtistPlays(int artistId);

    ArtistPlays(int artistId, MostPlayedListNode *ptrToListNode);

    ArtistPlays(int artistId, ::SongPlaysTree *SongPlaysTree, SongPlaysNode *ptrToLowestSongId,
                MostPlayedListNode *ptrToListNode);

    ~ArtistPlays();

    int getArtistId() const;

    ::SongPlaysTree *getSongPlaysTree() const;

    void setSongPlaysTree(::SongPlaysTree *songPlaysTree);

    SongPlaysNode *getPtrToLowestSongId() const;

    void setPtrToLowestSongId(SongPlaysNode *ptr);

    MostPlayedListNode *getPtrToListNode() const;

    void setPtrToListNode(MostPlayedListNode *ptr);
};

typedef TreeNode<ArtistPlays> ArtistPlaysNode;
typedef Tree<ArtistPlays> ArtistPlaysTree;

#endif //WET1_ARTISTPLAYS_H
