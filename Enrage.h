#ifndef __ENRAGE_H__
#define __ENRAGE_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class Enrage: public Enchantment {

public:
    Enrage();
    virtual ~Enrage();
    virtual int get_attack() override;
    virtual int get_defense() override;

};

#endif

