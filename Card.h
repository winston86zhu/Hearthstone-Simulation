#ifndef __CARD_H__
#define __CARD_H__
#include <iostream>
#include <string>
#include <memory>

#include "Player.h"
#include "ascii_graphics.h"
using namespace std;

class Ability;

class Card{
protected:
    int cost;
    std::string name;
public:
    Card(int cost, std::string name);
    virtual ~Card();
    //**************Getter*******************
    int get_cost();
    std::string get_name();
    virtual int get_activation_cost();
    //******************functions for Minion
    virtual int get_attack();
    virtual int get_defense();
    virtual int get_action();
    virtual std::string get_ability_description();
    virtual void attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other);
    virtual void attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j);
    virtual void reset_action(int val);
    virtual void use_one_action();
    virtual bool is_minion();
    //************************Functions for enchantment
    virtual bool is_enchantment();
    virtual bool is_disenchantable();
    virtual Card* get_above_top_enchantment();
    virtual unique_ptr<Card>& get_target();
    virtual unique_ptr<Card>& get_bottom_minion();// Get underlying decorated minion
    //*******************Functions for Polymorphism**********
    virtual bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player);
    virtual bool use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player);
    virtual bool execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player,
                                 int target_minion, unique_ptr<Player> &player_1, unique_ptr<Player> &player_2);
    //*******************Functions for Ritual****************
    virtual int get_charge();
    virtual void add_charge(int i);
    virtual int get_charge_cost();
    // ******************Functions for Display**************
    virtual card_template_t card_display();
    virtual string get_ability_type();
    virtual vector<card_template_t> inspect();
};

#endif

