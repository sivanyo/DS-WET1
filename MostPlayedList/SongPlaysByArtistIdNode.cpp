//
// Created by Mor on 27/04/2020.
//

#include "SongPlaysByArtistIdNode.h"

SongPlaysByArtistIdNode::SongPlaysByArtistIdNode(int songId, int numberOfPlays): TreeNode(songId) {
    this->songId = songId;
    this->numberOfPlays = 0;
}
