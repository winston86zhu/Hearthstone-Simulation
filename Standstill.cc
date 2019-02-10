#include "Standstill.h"
#include "Ability.h"

StandStill::StandStill(): Ritual {3, "Standstill", std::make_unique<StandstillTrig>(), 4, 2} {}

bool StandStill::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	this_player->get_ground()->attach(this_player->get_hand()->get_ith(i).get(), 1);
	other->get_ground()->attach(this_player->get_hand()->get_ith(i).get(), 1);

	this_player->get_ground()->set_ritual(this_player->get_hand()->get_ith(i));
	
	this_player->get_hand()->delete_ith(i);


	return true;
}

StandStill::~StandStill() {
}
