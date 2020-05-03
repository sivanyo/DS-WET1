//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYS_H
#define WET1_ARTISTPLAYS_H

#include "../TreeNode/TreeNode.h"
#include "../SongPlays/SongPlays.h"

//class SongPlaysNode;

class MostPlayedListNode;

class ArtistPlays {
private:
    int artistId;
    SongPlaysNode* SongPlaysTree = nullptr;
    SongPlaysNode* ptrToLowestSongId = nullptr;
    MostPlayedListNode* ptrToListNode = nullptr;
public:
    explicit ArtistPlays(int artistId);
    ArtistPlays(int artistId, MostPlayedListNode* ptrToListNode);
    ArtistPlays(int artistId, SongPlaysNode* SongPlaysTree, SongPlaysNode* ptrToLowestSongId,
                    MostPlayedListNode* ptrToListNode);

    int getArtistId() const;

    SongPlaysNode *getSongPlaysTree() const;

    void setSongPlaysTree(SongPlaysNode *songPlaysTree);

    SongPlaysNode *getPtrToLowestSongId() const;

    void setPtrToLowestSongId(SongPlaysNode *ptrToLowestSongId);

    MostPlayedListNode *getPtrToListNode() const;

    void setPtrToListNode(MostPlayedListNode *ptrToListNode);
};

typedef TreeNode<ArtistPlays> ArtistPlaysNode;

#endif //WET1_ARTISTPLAYS_H
