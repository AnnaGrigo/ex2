
#include "Player.h"

Player::Player(int player_id, int team_id, const permutation_t &spirit, int games_played, int ability, int cards,
               bool is_goalkeeper) {
    this->player_id = player_id;
    this->team_id = team_id;
    this->my_spirit = spirit;
    this->own_games_played = games_played;
    this->org_team_spirit_join = permutation_t::neutral();
    this->ability = ability;
    this->cards = cards;
    this->is_goalkeeper = is_goalkeeper;
    this->games_team_played = 0;
}

