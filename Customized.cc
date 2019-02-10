#include "Customized.h"
#include "ascii_graphics.h"


Customized::Customized(int inc_attack, int inc_defense, unique_ptr<Card> &target):
	Enchantment{0, "Customized", target, ""}, inc_attack{inc_attack}, inc_defense{inc_defense} {}

Customized::~Customized(){}


int Customized::get_attack(){
	int tmp = target->get_attack();
	return tmp + inc_attack;
}

int Customized::get_defense(){
	int tmp = target->get_defense();
	return tmp + inc_defense;
}

bool Customized::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	return false; // Customized isn't a card, will not be played
}

bool Customized::is_enchantment(){
	return true;
}

bool Customized::is_disenchantable(){
	return false;
}

card_template_t Customized::inspect_display(){
	if(inc_defense < 0)
		return display_enchantment_attack_defence("Attacked", 0, "", to_string(inc_attack), to_string(inc_defense));
	else 
		return display_enchantment_attack_defence("Power Up", 0, "", to_string(inc_attack), to_string(inc_defense));

}


