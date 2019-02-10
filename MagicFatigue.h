#ifndef __MAGICFATIGUE_H__
#define __MAGICFATIGUE_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class MagicFatigue: public Enchantment {

public:
    MagicFatigue();
    virtual ~MagicFatigue();
    virtual int get_activation_cost() override;

};

#endif

