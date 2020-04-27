//
// Created by Mor on 27/04/2020.
//

#include "ArtistPlaysByIdNode.h"

ArtistPlaysByIdNode::ArtistPlaysByIdNode(int artistId, SongPlaysByArtistIdNode artistSongsTree) : TreeNode(artistId) {
    this->artistId = artistId;
    this->artistSongsTree = artistSongsTree;
}
