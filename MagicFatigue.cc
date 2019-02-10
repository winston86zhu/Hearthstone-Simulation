#include "MagicFatigue.h"

MagicFatigue::MagicFatigue():
	Enchantment{1, "Magic Fatigue", "Enchanted minion's activated ability cost two more"} {}

MagicFatigue::~MagicFatigue(){}

int MagicFatigue::get_activation_cost(){
	return target->get_activation_cost() + 2;
}


