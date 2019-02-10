#ifndef __GIANTSTRENGTH_H__
#define __GIANTSTRENGTH_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class GiantStrength: public Enchantment {

public:
    GiantStrength();
    virtual ~GiantStrength();
    virtual int get_attack() override;
    virtual int get_defense() override; 
};

#endif

