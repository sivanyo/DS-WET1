//
// Created by Mor on 26/04/2020.
//

#include "MostPlayedListNode.h"

MostPlayedListNode::MostPlayedListNode(int numOfPlays) {
    this->numberOfPlays = numOfPlays;
    this->previous = nullptr;
    this->next = nullptr;
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = nullptr;
}

MostPlayedListNode::MostPlayedListNode(int numOfPlays, MostPlayedListNode *previous, MostPlayedListNode *next) {
    this->numberOfPlays = numOfPlays;
    this->previous = previous;
    this->next = next;
}

