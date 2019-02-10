#ifndef __EARTHELEMENTAL_H__
#define __EARTHELEMENTAL_H__
#include <iostream>
#include <string>
#include "Minion.h"
#include <memory>
#include "Card.h"
#include "AbsMinion.h"

class EarthElemental: public Minion {

public:
    EarthElemental();
    ~EarthElemental();
    card_template_t card_display() override;
};

#endif

