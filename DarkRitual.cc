#include "DarkRitual.h"
#include "Ritual.h"
#include "Ability.h"

DarkRitual::DarkRitual(): Ritual {0, "Dark Ritual", std::make_unique<DarkRitualTrig>(), 5, 1} {}

DarkRitual::~DarkRitual() {}

string DarkRitual::get_ability_type() {
    return "activated";
}

