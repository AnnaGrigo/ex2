
#include "UnionFind.h"

Team *UnionFind::Find(int id) {
    Player Player = Players->find_HT(id)->value;
    UFNode *node = Player.my_UFNode;
    permutation_t temp_rS = permutation_t::neutral();
    int sum_temp_plays = 0;
    while (node->parent != nullptr) {
        temp_rS = node->rS * temp_rS;
        sum_temp_plays += node->temp_plays;
        node = node->parent;
    }
    UFNode *nodePlayer = Player.my_UFNode;
    while (nodePlayer != node) {
        nodePlayer->rS =  temp_rS * permutation_t::neutral();
        nodePlayer->temp_plays = sum_temp_plays;
        temp_rS = temp_rS * nodePlayer->rS.inv();
        sum_temp_plays -= nodePlayer->temp_plays;
        nodePlayer->parent = node;
        nodePlayer = nodePlayer->parent;
    }
    return node->team;
}


//Team1 buys Team2 -> Team1 will be "on top" of Team2 (because the players have been in the Team longer)
StatusType UnionFind::Union_Teams(Team *BuyerTeam, Team *BoughtTeam) {
    UFNode *Buyer = BuyerTeam->team_UFNode;
    UFNode *Bought = BoughtTeam->team_UFNode;
    //update pointers
    if (Bought->size <= Buyer->size) {
        Bought->parent = Buyer;
        Buyer->size += Bought->size;
        //update temp_plays
        Bought->temp_plays += BoughtTeam->all_team_games_played - BuyerTeam->all_team_games_played -Buyer->temp_plays;
        //update rS
        Bought->rS =  (Buyer->rS.inv()) * BuyerTeam->team_permutation * Bought->rS;
        //update team pointer
        Bought->team = Buyer->team;
        return StatusType::SUCCESS;

    } else { //Bought->size > Buyer->size
        Buyer->parent = Bought;
        Bought->size += Buyer->size;
        //update temp_plays
        Buyer->temp_plays += BuyerTeam->all_team_games_played - BoughtTeam->all_team_games_played - Bought->temp_plays;
        Bought->temp_plays += BoughtTeam->all_team_games_played - BuyerTeam->all_team_games_played;
        //update rS
        Bought->rS =  BuyerTeam->team_permutation * Bought->rS;
        Buyer->rS =  (Bought->rS.inv()) * Buyer->rS;
        //update team pointer
        Bought->team = Buyer->team;
        Buyer->team = nullptr;
        //update head of teams
        BuyerTeam->team_UFNode = Bought;
    }
    return StatusType::SUCCESS;
}

StatusType UnionFind::Union_Players(UFNode *team, UFNode *player) {
    player->parent = team;
    team->size++;
    //update rS
    team->rS = team->rS * player->rS;
    //update team pointer
    player->team = team->team;
    return StatusType::SUCCESS;
}

