#include "FireElemental.h"
#include "Ability.h"

FireElemental::FireElemental(): Minion{2, "Fire Elemental", 2, 2}, abl{make_unique<FireElementalTrig>()} {}

FireElemental::~FireElemental(){}

std::string FireElemental::get_ability_description(){
	return abl->get_description();
}

bool FireElemental::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){

	auto& ground = this_player->get_ground();

	if(ground->get_size() >= 5){
		cerr << "Ground is full already!" << endl;
		return false;
	}
	Card* minion = this_player->get_hand()->get_ith(i).get();

	// do the actually summoning
	auto p = move(this_player->get_hand()->get_ith(i));//!!!
	this_player->get_ground()->emplace_card(move(p));

	other->get_ground()->attach(minion, 1);

	this_player->get_hand()->delete_ith(i);

	// trigger the triggers
	ground->SummonMinion(this_player->get_ground()->get_ith(this_player->get_ground()->get_size() - 1), this_player, other, current_player);
	
	return true;

}

bool FireElemental::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;

	return abl->execute(this_player, i, other, 0, player1, player2);
}


string FireElemental::get_ability_type() {
	return "trigger";
}

bool FireElemental::execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player,
		int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2){
	
	return abl->execute(triggered_player, triggered_minion, target_player, target_minion, player1, player2);
}

