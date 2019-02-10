#include "Enchantment.h"
#include "Player.h"
#include "ascii_graphics.h"
#include "Customized.h"

Enchantment::Enchantment(int cost, std::string name, std::string description):
	AbsMinion{cost, name}, target{nullptr}, description{description} {}

Enchantment::Enchantment(int cost, std::string name, unique_ptr<Card> &target, string description):
	AbsMinion{cost, name}, target{std::move(target)}, description{description} {}

Enchantment::~Enchantment(){}

int Enchantment::get_attack(){
	return target->get_attack();
}

int Enchantment::get_defense(){
	return target->get_defense();
}

int Enchantment::get_action(){
	return target->get_action();
}

std::string Enchantment::get_ability_description(){
	return description;
}

void Enchantment::reset_action(int val){
	target->reset_action(val);
}

int Enchantment::get_activation_cost(){
	return target->get_activation_cost();
}

void Enchantment::set_target(unique_ptr<Card> &t){
	target = std::move(t);
}

bool Enchantment::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	int p, t;
	if(!(in >> p >> t)){
		cout << "Error: You need to give a target for enchantment" << endl;
		return false;
	}
	t -= 1;
	// set enchantment on target and move ownership of minion to enchantment
	auto& p_target = (p == current_player) ? this_player:other;
	set_target(p_target->get_ground()->get_ith(t));
	// move enchantment from hand to ground
	p_target->get_ground()->get_ith(t) = std::move(this_player->get_hand()->get_ith(i));
	this_player->get_hand()->delete_ith(i);
	return true;
}

bool Enchantment::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	return target->use(this_player, other, i, in, current_player);
}

bool Enchantment::is_enchantment(){
	return true;
}

bool Enchantment::is_disenchantable(){
	return true;
}

unique_ptr<Card>& Enchantment::get_target(){
	return target;
}

unique_ptr<Card>& Enchantment::get_bottom_minion(){
	if(target->is_minion()){
		return target;
	}
	else
		return target->get_bottom_minion();
}

Card* Enchantment::get_above_top_enchantment(){
	if(target->is_disenchantable()){
		return this;
	}
	else
		return target->get_above_top_enchantment();
}

card_template_t Enchantment::card_display() {
    if(target){// display minion
    	auto name = get_bottom_minion()->get_name();
    	if (get_bottom_minion()->get_ability_type() == "None") {
			return display_minion_no_ability(name, get_bottom_minion()->get_cost(),
										 get_attack(), get_defense());
		} else if (get_bottom_minion()->get_ability_type() == "trigger") {
			return display_minion_triggered_ability(name,
													get_bottom_minion()->get_cost(), get_attack(), get_defense(), get_bottom_minion()->get_ability_description());
		} else if(get_bottom_minion()->get_ability_type() == "activated"){
			return display_minion_activated_ability(name,
													get_bottom_minion()->get_cost(), get_attack(),
													get_defense(), get_bottom_minion()->get_activation_cost(),
													get_bottom_minion()->get_ability_description());
		} else{
			return CARD_TEMPLATE_BORDER;
		}
    }
	else{
	    if(get_name() == "Giant Strength"){
	        return display_enchantment_attack_defence("Giant Strength", get_cost(),
	                                                  "","+2","+2");
	    } else if(get_name() == "Magic Fatigue"){
	        return display_enchantment("Magic Fatigue", get_cost(),
	                                   get_ability_description());
	    } else if(get_name() == "Silence"){
	        return display_enchantment("Silence", get_cost(),
	                                   get_ability_description());
	    } else if(get_name() == "Haste"){
	        return display_enchantment("Haste", get_cost(),
	                                   get_ability_description());
	    } else if(get_name() == "Enrage"){
	        return display_enchantment_attack_defence("Enrage", get_cost(),
	                                                  "","*2","*2");
	    } else{
	    	return CARD_TEMPLATE_BORDER;
	    }
	}
}

card_template_t Enchantment::inspect_display() {
	if(get_name() == "Giant Strength"){
        return display_enchantment_attack_defence("Giant Strength", get_cost(),
                                                  "","+2","+2");
    } else if(get_name() == "Magic Fatigue"){
        return display_enchantment("Magic Fatigue", get_cost(),
                                   get_ability_description());
    } else if(get_name() == "Silence"){
        return display_enchantment("Silence", get_cost(),
                                   get_ability_description());
    } else if(get_name() == "Haste"){
        return display_enchantment("Haste", get_cost(),
                                   get_ability_description());
    } else if(get_name() == "Enrage"){
        return display_enchantment_attack_defence("Enrage", get_cost(),
                                                  "","*2","*2");
    } else{
    	return CARD_TEMPLATE_BORDER;
    }
}

vector<card_template_t> Enchantment::inspect(){
	vector<card_template_t> tmp;
	Card *itr = this;
	while(itr->is_enchantment()){
		tmp.emplace(tmp.begin(), dynamic_cast<Enchantment *>(itr)->inspect_display());
		itr = dynamic_cast<Enchantment *>(itr)->target.get();
	}
	tmp.emplace(tmp.begin(), card_display());

	return tmp;
}

void Enchantment::use_one_action(){
	target->use_one_action();
}

void Enchantment::attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other){
	if(get_action() <= 0){
        cerr << "Attack Error - This Minion does not have action"<<endl;
        return;
    }

    cout << "Enchanment.cc action" << get_action() << endl;

	int attack_val = this_player->get_ground()->get_ith(i)->get_attack();
	other->set_life(other->get_life() - attack_val);
	use_one_action();

}

void Enchantment::attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j){
	if(get_action() <= 0){
        cerr << "Attack Error - This Minion does not have action"<<endl;
        return;
    }

	int i_attack = this_player->get_ground()->get_ith(i)->get_attack();
	int j_attack = other->get_ground()->get_ith(j)->get_attack();

	this_player->get_ground()->get_ith(i) = make_unique<Customized>(0, -j_attack, this_player->get_ground()->get_ith(i));
	other->get_ground()->get_ith(j) = make_unique<Customized>(0, -i_attack, other->get_ground()->get_ith(j));
	use_one_action();
}

string Enchantment::get_ability_type() {
	return target->get_ability_type();
}

bool Enchantment::execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2){
	return target->execute_trigger(triggered_player, triggered_minion, target_player, target_minion, player1, player2);
}


