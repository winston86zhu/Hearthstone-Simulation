#ifndef __MINION_H__
#define __MINION_H__
#include <iostream>
#include <string>
#include <memory>
#include "Card.h"
#include "AbsMinion.h"
#include "ascii_graphics.h"
#include "Minion.h"
class Ability;

class Minion: public AbsMinion {
	int attack;
	int defense;
	int action;
public:
    Minion(int cost, std::string name, int attack, int defense);
    virtual ~Minion();
    //**************************getter***********************
    virtual int get_attack() override;
    virtual int get_defense() override;
    virtual int get_action() override;
    virtual void reset_action(int val) override;
    //**************************Key Command*******************
    virtual bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    virtual bool use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    virtual bool is_minion() override;
	void attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other) override;
	void attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j) override;
    //**************************Display***********************
    virtual card_template_t card_display() override;
    virtual vector<card_template_t> inspect() override;
    virtual void use_one_action() override;

};

#endif

