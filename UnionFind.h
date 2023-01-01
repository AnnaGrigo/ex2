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
    int temp_plays; //if the buyer team is larger, assign to temp_plays of the bought team the minus all_games_played by the buyer team
    //if the buyer team is smaller, assign to temp_plays of the buyer team all the all_games_played of the buyer team
    //minus all_games_played of the bought team, and assign to temp_plays of the bought team all_games_played of the bought team
    //minus all_games_played of the buyer team
    Team *team; //only for root
    UFNode *parent; //if nullptr -> root


    UFNode(int id) : id(id) ,size(0), rS(permutation_t::neutral()),  team(nullptr), temp_plays(0) ,parent(nullptr) {}
};


class UnionFind {
public:
    HashTable<Player> *Players;

    UnionFind() = default;

    UnionFind(HashTable<Player> *Players) : Players(Players) {}

    Team *Find(int id);

    StatusType Union_Teams(Team *BuyerTeam, Team *BoughtTeam);

    StatusType Union_Players(UFNode *team, UFNode *player);

    ~UnionFind() = default;

};



#endif //EX2_UNIONFIND_H
