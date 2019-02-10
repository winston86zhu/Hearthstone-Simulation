#ifndef __DARKRITUAL_H__
#define __DARKRITUAL_H__

#include "Ritual.h"

class Player;
using namespace std;

class DarkRitual: public Ritual {
	
public:
    DarkRitual();
    ~DarkRitual();
    //bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    string get_ability_type() override;
};

#endif
