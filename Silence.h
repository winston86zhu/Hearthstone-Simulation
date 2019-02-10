#ifndef __SILENCE_H__
#define __SILENCE_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class Silence: public Enchantment {

public:
    Silence();
    virtual ~Silence();
    virtual bool use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;

};

#endif

