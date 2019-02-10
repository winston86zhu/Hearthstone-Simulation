#include "Spell.h"

Spell::Spell(int cost, std::string name, unique_ptr<Ability> p): Card{cost, name}, abl{std::move(p)} {}

Spell::~Spell(){}

card_template_t Spell::card_display() {
    return display_spell(get_name(),get_cost(),get_ability_description());
}

string Spell::get_ability_description() {
    return abl->get_description();
}
