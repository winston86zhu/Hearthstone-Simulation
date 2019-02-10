#include "ascii_graphics.h"
#include "Airelemental.h"
#include "Minion.h"
#include "Card.h"
#include "AbsMinion.h"


AirElemental::AirElemental(): Minion{0, "Air Elemental", 1, 1} {}

AirElemental::~AirElemental(){}

card_template_t AirElemental::card_display() {
    return display_minion_no_ability("Air Elemental", 0, 1, 1);
}

string AirElemental::get_ability_type() {
    return "None";
}

std::string AirElemental::get_ability_description(){
	return "";
}
