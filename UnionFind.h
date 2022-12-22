//
// Created by annag on 21/12/2022.
//

#ifndef EX2_UNIONFIND_H
#define EX2_UNIONFIND_H

#include "RankTree.h"
#include "HashTable.h"
#include "wet2util.h"
#include "Player.h"
#include "Team.h"

class UFNode {
public:
    int id;
    int size;
    permutation_t rS;
    permutation_t spirit;
    Player *player;
    Team *team;
    UFNode *parent;

    UFNode(int id, Player *player) : id(id), size(1), rS(permutation_t::neutral()), player(player), team(nullptr),
                                     parent(nullptr) {}
};


class UnionFind {
public:
    HashTable<Player *> *Players;
    RankTree<int, Team *> *Teams;

    UnionFind() = default;

    UnionFind(HashTable<Player *> *Players, RankTree<int, Team *> *Teams) : Players(Players), Teams(Teams) {}

    Team *Find(int id);

    StatusType Union(Team *BuyerTeam, Team *BoughtTeam);

    ~UnionFind() = default;

};

Team *UnionFind::Find(int id) {
    Player *Player = Players->find_HT(id)->value;
    if (Player == nullptr) {
        return nullptr;
    }
    UFNode *node = Player->my_UFNode;
    while (node->parent != nullptr) {
        node = node->parent;
    }
    return node->team;
}


//Team1 buys Team2 -> Team1 will be "on top" of Team2 (because the players have been in the Team longer)
StatusType UnionFind::Union(Team *BuyerTeam, Team *BoughtTeam) {
    UFNode *Buyer = BuyerTeam->team_UFNode;
    UFNode *Bought = BoughtTeam->team_UFNode;
    //update pointers
    if (Bought->size >= Buyer->size) {
        Buyer->parent = Bought;
        Bought->size += Buyer->size;
        Buyer->team = Bought->team;
    } else {
        Bought->parent = Buyer;
        Buyer->size += Bought->size;
        Bought->team = Buyer->team;
    }
    //update spirit
    BuyerTeam->team_permutation = BuyerTeam->team_permutation * BoughtTeam->team_permutation;
    if (Buyer->size >= Bought->size) {

    }

    return StatusType::ALLOCATION_ERROR;
}


#endif //EX2_UNIONFIND_H
