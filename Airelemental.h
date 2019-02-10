#ifndef __AIRELEMENTAL_H__
#define __AIRELEMENTAL_H__
#include <iostream>
#include <string>
#include "Minion.h"
#include "ascii_graphics.h"
#include <memory>
#include "Card.h"
#include "AbsMinion.h"
using namespace std;


class AirElemental: public Minion {

public:
    AirElemental();
    virtual ~AirElemental();
    card_template_t card_display() override;
    string get_ability_type() override;
    string get_ability_description() override;

};

#endif

