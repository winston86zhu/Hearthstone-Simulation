#include "NovicePyromancer.h"

NovicePyromancer::NovicePyromancer(): Minion{1, "Novice Pyromancer", 0, 1}, abl{new NovicePyromancerActv} {}

NovicePyromancer::~NovicePyromancer(){
	//delete dealdamage;
}

std::string NovicePyromancer::get_ability_description(){
	return abl->get_description();
}

int NovicePyromancer::get_activation_cost(){
	return abl->get_activation_cost();
}

bool NovicePyromancer::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	// magic checking in Player::use
	// read in the targetreturn Card::get_ability_type();
	if(get_action() <= 0){
	    cerr << "Use Error - This minion does not have enough action" <<endl;
	}
	int p, t;
	in >> p >> t;
	t = t - 1;
	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
	unique_ptr<Player> &target_player = (p == 1) ? player1:player2;
	bool result =  abl->execute(this_player, i, target_player, t, player1, player2);
	if(result) {
        reset_action(get_action() - 1);
    }
	return result;
}

string NovicePyromancer::get_ability_type() {
	return "activated";
}
