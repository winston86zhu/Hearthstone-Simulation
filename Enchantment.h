#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include <iostream>
#include <string>
#include "AbsMinion.h"
#include "ascii_graphics.h"

class Enchantment: public AbsMinion {
protected:
	unique_ptr<Card> target;
    std::string description;
public:
    Enchantment(int cost, std::string name,std::string description);
    Enchantment(int cost, std::string name, unique_ptr<Card> &target,string description);
    virtual ~Enchantment();
    int get_attack() override;
    int get_defense() override;
    int get_action() override;
    std::string get_ability_description() override;
    virtual void reset_action(int val) override;
    virtual int get_activation_cost() override;
    virtual bool play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    virtual bool use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) override;
    virtual bool is_enchantment() override;
    virtual bool is_disenchantable() override;
    virtual unique_ptr<Card>& get_target() override;
    virtual unique_ptr<Card>& get_bottom_minion() override;
    virtual Card* get_above_top_enchantment() override;
    card_template_t card_display() override;
    void set_target(unique_ptr<Card> &t);
    virtual vector<card_template_t> inspect() override;
    virtual card_template_t inspect_display();

    virtual void attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other) override;
    virtual void attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j) override;
    virtual string get_ability_type() override;

    virtual bool execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
    virtual void use_one_action() override;

};

#endif
