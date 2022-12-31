
#include "Team.h"

Team::Team(int team_id) {
    this->team_id = team_id;
    this->points = 0;
    this->team_ability = 0;
    this->is_there_goalkeeper = false;
    this->all_team_games_played = 0;
    this->is_active = true;
    this->team_permutation = permutation_t::neutral();
}

bool Is_Team_Legal(Team *team) {
    return team->is_there_goalkeeper;
}
