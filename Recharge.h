#ifndef __RECHARGE_H__
#define __RECHARGE_H__

#include "Card.h"
#include "Ability.h"
#include "Spell.h"
using namespace std;

class Recharge: public Spell {
	
public:
    Recharge();
    ~Recharge();
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    string get_ability_type() override;


};

#endif
