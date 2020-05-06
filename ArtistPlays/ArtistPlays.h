//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYS_H
#define WET1_ARTISTPLAYS_H

#include "../TreeNode/Tree.h"
#include "../SongPlays/SongPlays.h"

class MostPlayedListNode;
class SongPlays;

class ArtistPlays {
private:
    int artistId;
    Tree<SongPlays> *SongPlaysTree = nullptr;
    TreeNode<SongPlays> *ptrToLowestSongId = nullptr;
    MostPlayedListNode *ptrToListNode = nullptr;
public:
    explicit ArtistPlays(int artistId);

    ArtistPlays(int artistId, MostPlayedListNode *ptrToListNode);

    ArtistPlays(int artistId, Tree<SongPlays> *SongPlaysTree, TreeNode<SongPlays> *ptrToLowestSongId,
                MostPlayedListNode *ptrToListNode);

    ~ArtistPlays();

    int getArtistId() const;

    Tree<SongPlays> *getSongPlaysTree() const;

    void setSongPlaysTree(Tree<SongPlays> *songPlaysTree);

    TreeNode<SongPlays> *getPtrToLowestSongId() const;

    void setPtrToLowestSongId(TreeNode<SongPlays> *ptr);

    MostPlayedListNode *getPtrToListNode() const;

    void setPtrToListNode(MostPlayedListNode *ptr);
};

typedef TreeNode<ArtistPlays> ArtistPlaysNode;
typedef Tree<ArtistPlays> ArtistPlaysTree;

#endif //WET1_ARTISTPLAYS_H
