#include "Minion.h"
#include "Player.h"
#include "AbsMinion.h"
#include "Customized.h"


Minion::Minion(int cost, std::string name, int attack, int defense): 
	AbsMinion{cost, name}, attack{attack}, defense{defense}, action{0} {}


Minion::~Minion(){}

int Minion::get_attack(){
	return attack;
}

int Minion::get_defense(){
	return defense;
}

int Minion::get_action(){
	return action;
}

void Minion::reset_action(int val) {
    action = val;
}

bool Minion::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	// check for space
	auto& ground = this_player->get_ground();
	if(ground->get_size() >= 5){
		cerr << "Ground is full already!" << endl;
		return false;
	}
	
	// do the actually summoning
	auto p = move(this_player->get_hand()->get_ith(i));//!!!
	this_player->get_ground()->emplace_card(move(p));
	this_player->get_hand()->delete_ith(i);

	// trigger the triggers
	ground->SummonMinion(this_player->get_ground()->get_ith(this_player->get_ground()->get_size() - 1), this_player, other, current_player);
	
	return true;
}

bool Minion::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	std::cerr << "This Minion doesn't have activation ability." << std::endl;
	return false;
}

bool Minion::is_minion(){
	return true;
}

void Minion::use_one_action(){
	action--;
}

card_template_t Minion::card_display() {
	if (get_ability_type() == "None") {
		return display_minion_no_ability(get_name(), get_cost(),
										 get_attack(), get_defense());
	} else if (get_ability_type() == "trigger") {
		return display_minion_triggered_ability(get_name(),
												get_cost(), get_attack(), get_defense(), get_ability_description());
	} else if(get_ability_type() == "activated"){
		return display_minion_activated_ability(get_name(),
												get_cost(), get_attack(),
												get_defense(), get_activation_cost(),
												get_ability_description());
	} else {
		return CARD_TEMPLATE_BORDER;
	}
}

vector<card_template_t> Minion::inspect() {
	vector<card_template_t> tmp;
	tmp.emplace_back(card_display());
	return tmp;
}

void Minion::attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other) {
    if(get_action() <= 0){
        cerr << "Attack Error - This Minion does not have action"<<endl;
        return;
    }
	int attack_val = this_player->get_ground()->get_ith(i)->get_attack();
	other->set_life(other->get_life() - attack_val);
	use_one_action();
}

void Minion::attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j) {
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


