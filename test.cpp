//
// Created by Mor on 26/04/2020.
//

#include <iostream>
#include "ArtistTree/ArtistNode.h"


int main() {
    ArtistNode artistTree(34, 5);
    std::cout << artistTree.GetKey() << std::endl;
    artistTree.AddNode(artistTree);
    return 0;
}