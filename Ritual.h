#ifndef __RITUAL_H__
#define __RITUAL_H__
#include <iostream>
#include <string>
#include "Card.h"
#include "ascii_graphics.h"

class Player;
class Ability;

class Ritual: public Card {
	
protected:
    int charge;
    int charge_cost;
	unique_ptr<Ability> abl;

public:

    Ritual(int cost, std::string name, unique_ptr<Ability> p, int charge, int charge_cost);
    virtual ~Ritual();
    void add_charge(int i) override;
    bool execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player,
                                 int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
    int get_charge() override;
    std::string get_ability_description() override;
    card_template_t card_display() override;
	int get_charge_cost() override;
    bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
};

#endif
