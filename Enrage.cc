#include "Enrage.h"

Enrage::Enrage():
	Enchantment{2, "Enrage", ""} {}

Enrage::~Enrage(){}

int Enrage::get_attack(){
	
	int tmp = target->get_attack();
	return tmp * 2;
}

int Enrage::get_defense(){
	int tmp = target->get_defense();
	return tmp * 2;
}




