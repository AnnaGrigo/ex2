
#ifndef RATUV1_PLAYER_H
#define RATUV1_PLAYER_H
#include "Team.h"
#include "wet2util.h"

class Player
{
public:
    int player_id;
    int team_id;
    permutation_t my_spirit;
    int own_games_played; //games played by this player when initialized
    int ability;
    int cards;
    bool is_goalkeeper;
    int games_team_played; //games played by the team when initialized

    Player() = default;
    Player(int player_id, int team_id,const permutation_t &spirit , int games_played,
           int ability, int cards, bool is_goalkeeper);
    ~Player() = default;
};
#endif //RATUV1_PLAYER_H
