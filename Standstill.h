#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__

#include "Ritual.h"
#include "Card.h"
class Player;

class StandStill: public Ritual {
	
public:
    StandStill();
    ~StandStill();
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
};

#endif

