#ifndef __RAISEDEAD_H__
#define __RAISEDEAD_H__

#include "Card.h"
#include "Ability.h"
#include "Spell.h"


class RaiseDead: public Spell {
	
public:
    RaiseDead();
    ~RaiseDead();
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    string get_ability_type() override;

};

#endif
