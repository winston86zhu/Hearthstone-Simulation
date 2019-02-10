#include "AuraOfPower.h"
#include "Ritual.h"
#include "Ability.h"

AuraOfPower::AuraOfPower(): Ritual {1, "Aura of Power", std::make_unique<AuraOfPowerTrig>(), 4, 1} {}

AuraOfPower::~AuraOfPower(){
};

bool AuraOfPower::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	this_player->get_ground()->attach(this_player->get_hand()->get_ith(i).get(), 1);

	this_player->get_ground()->set_ritual(this_player->get_hand()->get_ith(i));
	this_player->get_hand()->delete_ith(i);


	return true;
}
