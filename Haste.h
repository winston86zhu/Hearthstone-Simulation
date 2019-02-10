#ifndef __HASTE_H__
#define __HASTE_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class Haste: public Enchantment {

public:
    Haste();
    virtual ~Haste();
    virtual int get_action() override;
};

#endif

