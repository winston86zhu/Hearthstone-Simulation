#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__

#include "Card.h"
#include "Ability.h"
#include "Spell.h"

class Blizzard: public Spell {
	
public:
    Blizzard();
    ~Blizzard();
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    string get_ability_type() override;

};

#endif
