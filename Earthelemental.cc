#include "Earthelemental.h"
#include "ascii_graphics.h"

EarthElemental::EarthElemental(): Minion{3, "Earth Elemental", 4, 4} {}

EarthElemental::~EarthElemental(){}

 card_template_t EarthElemental::card_display() {
     return display_minion_no_ability("Earth Elemental", 3, 4, 4);
 }
