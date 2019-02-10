#ifndef __AURAOFPOWER_H__
#define __AURAOFPOWER_H__

#include "Ritual.h"
#include "Ability.h"

class Player;

class AuraOfPower: public Ritual {
	
public:
    AuraOfPower();
    ~AuraOfPower();
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
};

#endif
