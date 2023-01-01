#include "worldcup23a2.h"

world_cup_t::world_cup_t() : teams_by_id(), teams_by_ability(), teams_to_delete(),
    all_players_by_id(), UF(&all_players_by_id), counter_to_delete(1) {}


template<class Key, class Value>
void Delete_All(RankNode<Key, Value> *root)
{
    if (!root)
    {
        return;
    }
    Delete_All(root->left_son);
    Delete_All(root->right_son);
    delete root->value;
}

void Delete_UF(UnionFind *UF)
{
    for (int i = 0; i < UF->Players->size; i++)
    {
        if (UF->Players->array[i].head != nullptr)
        {
            Node<Player> *current = UF->Players->array[i].head;
            Node<Player> *next;
            while (current != nullptr) {
                next = current->next;
                delete current->value.my_UFNode;
                current = next;
            }
        }
    }
}

world_cup_t::~world_cup_t()
{
    Delete_All(teams_by_id.root);
    Delete_All(teams_to_delete.root);
    Delete_UF(&UF);
}

StatusType world_cup_t::add_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    if(teams_by_id.find(teamId) != nullptr)
        return StatusType::FAILURE;
    StatusType status;
    Team* new_team;
    try {
        new_team = new Team(teamId);
    }
    catch (std::bad_alloc& ba)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    status = teams_by_id.insert(teamId, new_team);
    if(status == StatusType::ALLOCATION_ERROR)
        return StatusType::ALLOCATION_ERROR;
    status = teams_by_ability.insert(Ability(new_team->team_ability,teamId), new_team);
    if(status == StatusType::ALLOCATION_ERROR)
        return StatusType::ALLOCATION_ERROR;

    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    if(teams_by_id.find(teamId) == nullptr)
        return StatusType::FAILURE;
    Team* team_to_remove = teams_by_id.find(teamId)->value;
    team_to_remove->is_active = false;
    teams_by_id.remove(teamId);
    teams_by_ability.remove(Ability(team_to_remove->team_ability,teamId));
    teams_to_delete.insert(counter_to_delete, team_to_remove);
    counter_to_delete++;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <=0 || teamId <=0 || gamesPlayed <0 || cards <0 ||!(spirit.isvalid()))
    {
        return StatusType::INVALID_INPUT;
    }
    if(all_players_by_id.find_HT(playerId) != nullptr || teams_by_id.find(teamId) == nullptr)
    {
        return StatusType::FAILURE;
    }
    all_players_by_id.insert_HT(playerId, Player(playerId, teamId, spirit, gamesPlayed, ability,
                                                         cards, goalKeeper));
    Team* team = teams_by_id.find(teamId)->value;
    UFNode *new_UF;
    try {
        new_UF = new UFNode(playerId);
    }
    catch (std::bad_alloc& ba)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    if(team->team_UFNode == nullptr)
    {
        team->team_UFNode = new_UF;
        all_players_by_id.find_HT(playerId)->value.my_UFNode = new_UF;
        new_UF->team = team;
        new_UF->size++;
    }
    else
    {
        all_players_by_id.find_HT(playerId)->value.my_UFNode = new_UF;
        UF.Union_Players(team->team_UFNode, new_UF);
    }
    team->team_permutation = team->team_permutation * spirit;
    all_players_by_id.find_HT(playerId)->value.org_team_spirit_join = team->team_permutation;
    if(goalKeeper)
    {
        team->is_there_goalkeeper = true;
    }
    teams_by_ability.remove(Ability(team->team_ability,teamId));
    team->team_ability += ability;
    return teams_by_ability.insert(Ability(team->team_ability,teamId), team);
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <=0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    RankNode<int,Team*>* team1node = teams_by_id.find(teamId1);
    RankNode<int,Team*>* team2node = teams_by_id.find(teamId2);
    if(team1node == nullptr || team2node == nullptr)
        return StatusType::FAILURE;

    Team* team1 = team1node->value;
    Team* team2 = team2node->value;

    if(!(Is_Team_Legal(team1) && Is_Team_Legal(team2)))
        return StatusType::FAILURE;

    if(team1->points + team1->team_ability > team2->points + team2->team_ability){
        team1->points += 3;
        team1->all_team_games_played++;
        team2->all_team_games_played++;
        return output_t<int>(1);
    }
    else if(team1->points + team1->team_ability < team2->points + team2->team_ability){
        team2->points += 3;
        team1->all_team_games_played++;
        team2->all_team_games_played++;
        return output_t<int>(3);
    }
    else{
        permutation_t team1_spirit = team1->team_permutation;
        permutation_t team2_spirit = team2->team_permutation;
        if(team1_spirit.strength() > team2_spirit.strength()){
            team1->points += 3;
            team1->all_team_games_played++;
            team2->all_team_games_played++;
            return output_t<int>(2);
        }
        else if(team1_spirit.strength() < team2_spirit.strength()){
            team2->points += 3;
            team1->all_team_games_played++;
            team2->all_team_games_played++;
            return output_t<int>(4);
        }
        else{
            team1->points++;
            team2->points++;
            team1->all_team_games_played++;
            team2->all_team_games_played++;
            return output_t<int>(0);
        }
    }
}



output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;
    Node<Player>* player_node = all_players_by_id.find_HT(playerId);
    if(player_node == nullptr)
        return StatusType::FAILURE;
    UFNode* player_UFNode = player_node->value.my_UFNode;
    if(player_UFNode == nullptr)
        return StatusType::FAILURE;
    int games_played = 0;
    while (player_UFNode->parent != nullptr)
    {
        games_played += player_UFNode->temp_plays;
        player_UFNode = player_UFNode->parent;
    }
    games_played += player_UFNode->temp_plays;
    games_played += player_UFNode->team->all_team_games_played;
    Player player = player_node->value;
    games_played += player.own_games_played;
    games_played -= player.games_team_played;
    return games_played;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if(playerId<= 0 || cards < 0)
        return StatusType::INVALID_INPUT;
    Node<Player>* player_node = all_players_by_id.find_HT(playerId);
    if(player_node == nullptr)
        return StatusType::FAILURE;
    Team* team = UF.Find(playerId)->team_UFNode->team;
    if(!team->is_active)
        return StatusType::FAILURE;
    player_node->value.cards += cards;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId) {

    if (playerId <= 0)
        return StatusType::INVALID_INPUT;

    Node<Player> *player_node = all_players_by_id.find_HT(playerId);
    if (!player_node)
        return StatusType::FAILURE;

    return player_node->value.cards;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;

    RankNode<int,Team*>* team_node = teams_by_id.find(teamId);
    if(team_node == nullptr)
        return StatusType::FAILURE;

    return team_node->value->points;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
    if(i < 0 || i >= teams_by_ability.size || teams_by_ability.size == 0)
        return StatusType::FAILURE;
    return teams_by_ability.findIndex(i)->value->team_id;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;
    Node<Player>* player_node = all_players_by_id.find_HT(playerId);
    if(player_node == nullptr)
        return StatusType::FAILURE;
    UFNode* player_UFNode = player_node->value.my_UFNode;
    if(player_UFNode == nullptr)
        return StatusType::FAILURE;
    if(!UF.Find(playerId)->is_active)
        return StatusType::FAILURE;
    permutation_t spirit = player_node->value.org_team_spirit_join;
    while (player_UFNode->parent != nullptr)
    {
        spirit = player_UFNode->rS * spirit;
        player_UFNode = player_UFNode->parent;
    }
    spirit = player_UFNode->rS * spirit;
    return spirit;
}

//team1 buys team2
StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    if(teams_by_id.find(teamId1) == nullptr || teams_by_id.find(teamId2) == nullptr)
        return StatusType::FAILURE;
    Team *team1 = teams_by_id.find(teamId1)->value;
    Team *team2 = teams_by_id.find(teamId2)->value;
    //if team1 (buyer) is empty
    if(team2->team_UFNode && !team1->team_UFNode){
        team1->team_UFNode = team2->team_UFNode;
        team1->team_UFNode->team = team1;
        team1->team_UFNode->temp_plays -= team2->all_team_games_played - team1->all_team_games_played;
    }
        //if both teams are not empty
    else if (team1->team_UFNode && team2->team_UFNode){
        UF.Union_Teams(team1,team2);
    }
    if(team2->is_there_goalkeeper){
        team1->is_there_goalkeeper = true;
    }
    team1->points += team2->points;
    team1->team_permutation =  team1->team_permutation * team2->team_permutation;
    teams_by_ability.remove(Ability(team1->team_ability,teamId1));
    team1->team_ability += team2->team_ability;
    teams_by_id.remove(teamId2);
    teams_by_ability.remove(Ability(team2->team_ability,teamId2));
    delete team2;
    teams_by_ability.insert(Ability(team1->team_ability,teamId1),team1);
    return StatusType::SUCCESS;
}
