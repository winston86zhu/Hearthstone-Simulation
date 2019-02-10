#include "Giantstrength.h"

GiantStrength::GiantStrength():
	Enchantment{1, "Giant Strength", ""} {}

GiantStrength::~GiantStrength(){}


int GiantStrength::get_attack(){
	int tmp = target->get_attack();
	return tmp + 2;
}

int GiantStrength::get_defense(){
	int tmp = target->get_defense();
	return tmp + 2;
}

