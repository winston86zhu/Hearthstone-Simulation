#include "Ritual.h"
#include "Card.h"
#include "Ability.h"
#include <memory>

Ritual::Ritual(int cost, std::string name, unique_ptr<Ability> p, int charge, int charge_cost):

	Card{cost, name}, charge{charge}, charge_cost{charge_cost}, abl{std::move(p)} {}


Ritual::~Ritual(){}

void Ritual::add_charge(int i){
	charge += i;
}

bool Ritual::execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player,
		int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2){
	if(charge >= charge_cost){
		abl->execute(triggered_player, triggered_minion, target_player, target_minion, player1, player2);
		charge -= charge_cost;
		return true;
	}
	else
		return false;
}



int Ritual::get_charge() {
	return charge;
}

std::string Ritual::get_ability_description(){
	return abl->get_description();
}

card_template_t Ritual::card_display() {
    return display_ritual(get_name(), get_cost(),
                          get_charge_cost(),
                          get_ability_description(),
                          get_charge());
}

int Ritual::get_charge_cost() {
    return charge_cost;
}

bool Ritual::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player) {
	if(this_player->get_ground()->get_ritual() == nullptr){
		this_player->get_ground()->set_ritual(this_player->get_hand()->get_ith(i));
	} else {
	    this_player->get_ground()->delete_ritual();
        this_player->get_ground()->set_ritual(this_player->get_hand()->get_ith(i));
	}
	this_player->get_hand()->delete_ith(i);

	//this_player->get_hand()->delete_ith(i);
	if(get_name() == "Dark Ritual"){
	    this_player->get_ground()->attach(this,5);
	} else if(get_name() == "Aura of Power"){
	    this_player->get_ground()->attach(this, 1);
	} else if (get_name() == "Standstill") {
        this_player->get_ground()->attach(this, 3);
    } else {
	    return false;
    }
    return true;
}


