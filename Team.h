#ifndef RATUV1_TEAM_H
#define RATUV1_TEAM_H

#include "wet2util.h"

class Player;

class Team {
public:
    int team_id;
    int points;
    int team_ability;
    bool is_there_goalkeeper;
    int all_team_games_played;
    bool is_active;
    Player *UF_player;
    permutation_t team_permutation;



    Team() = default;
    Team(int team_id);
    ~Team() = default;

};

bool Is_Team_Legal(Team* );

#endif //RATUV1_TEAM_H