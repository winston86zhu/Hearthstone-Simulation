#include "Blizzard.h"

Blizzard::Blizzard(): Spell{3, "Blizzard", std::make_unique<BlizzardActv>()} {}

Blizzard::~Blizzard(){}

bool Blizzard::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){

	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;

	bool result = abl->execute(this_player, i, other, 0, player1, player2);
	this_player->get_hand()->delete_ith(i);
	return result;
}

string Blizzard::get_ability_type() {
	return "trigger";
}
