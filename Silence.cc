#include "Silence.h"

Silence::Silence():
	Enchantment{1, "Silence", "Enchanted minion cannot use abilities"} {}

Silence::~Silence(){}

bool Silence::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	std::cout << "Silenced minion cannot use ability" << std::endl;
	return false;
}


