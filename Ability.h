
#ifndef EX2_ABILITY_H
#define EX2_ABILITY_H

class Ability
{
public:
    int ability;
    int team_id;

    Ability() : ability(0), team_id(0) {}
    Ability(int ability, int team_id)
       : ability(ability), team_id(team_id) {}


    Ability(const Ability &other)
    {
        this->ability = other.ability;
        this->team_id = other.team_id;
    }

    friend bool operator<(const Ability& Ability1, const Ability& Ability2)
    {
        if(Ability1.ability < Ability2.ability)
        {
            return true;
        }
        else if(Ability1.ability == Ability2.ability)
        {
            if(Ability1.team_id < Ability2.team_id)
            {
                return true;
            }
        }
        return false;
    }

    friend bool operator>(const Ability& Ability1, const Ability& Ability2)
    {
        if(Ability1.ability > Ability2.ability)
        {
            return true;
        }
        else if(Ability1.ability == Ability2.ability)
        {
            if(Ability1.team_id > Ability2.team_id)
            {
                return true;
            }
        }
        return false;
    }

    friend bool operator==(const Ability& Ability1, const Ability& Ability2)
    {
        if(Ability1.ability == Ability2.ability)
        {
            if(Ability1.team_id == Ability2.team_id)
            {
                return true;
            }
        }
        return false;
    }

    friend bool operator<=(const Ability& Ability1, const Ability& Ability2)
    {
        return Ability1 < Ability2 || Ability1 == Ability2;
    }

    friend bool operator>=(const Ability& Ability1, const Ability& Ability2)
    {
        return Ability1 > Ability2 || Ability1 == Ability2;
    }


};


#endif //EX2_ABILITY_H
