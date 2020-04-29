//
// Created by Mor on 27/04/2020.
//

#include "ArtistPlaysNode.h"


ArtistPlaysNode::ArtistPlaysNode(int artistId, shared_ptr<SongPlaysNode> ptrToSongPlaysTree, shared_ptr<MostPlayedListNode> ptrToListNode) : TreeNode(
        artistId) {
    this->artistId = artistId;
    this->SongPlaysTree = ptrToSongPlaysTree;
    this->ptrToListNode = ptrToListNode;
}

ArtistPlaysNode::ArtistPlaysNode(int artistId) : TreeNode(artistId), artistId(artistId) {}

int ArtistPlaysNode::GetArtistId() {
    shared_ptr<ArtistPlaysNode> test = make_shared<ArtistPlaysNode>(5);
    test->AddNode(make_shared<ArtistPlaysNode>(4));
    return this->artistId;
}
