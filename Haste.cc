#include "Haste.h"

Haste::Haste():
	Enchantment{1, "Haste", "Enchanted minions gain +1 action each turn"} {}

Haste::~Haste(){}

int Haste::get_action(){
	return target->get_action() + 1;
}
