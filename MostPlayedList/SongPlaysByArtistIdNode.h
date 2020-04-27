//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_SONGPLAYSBYARTISTIDNODE_H
#define WET1_SONGPLAYSBYARTISTIDNODE_H


#include "../TreeNode/TreeNode.h"

class SongPlaysByArtistIdNode : public TreeNode {
private:
    int songId;
    int numberOfPlays;

public:
    SongPlaysByArtistIdNode(int songId, int numberOfPlays);
};


#endif //WET1_SONGPLAYSBYARTISTIDNODE_H
