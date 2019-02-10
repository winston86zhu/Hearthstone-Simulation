#ifndef __CUSTOMIZED_H__
#define __CUSTOMIZED_H__
#include <iostream>
#include <string>
#include "Enchantment.h"

class Customized: public Enchantment {
	int inc_attack;
	int inc_defense;

public:
    Customized(int inc_attack, int inc_defense, unique_ptr<Card> &target);
    virtual ~Customized();
    virtual int get_attack() override;
    virtual int get_defense() override;
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    //virtual Card* get_above_top_enchantment() override;
    virtual bool is_enchantment() override;
    virtual bool is_disenchantable() override;

    virtual card_template_t inspect_display() override;



};

#endif

