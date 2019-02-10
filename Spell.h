#ifndef __SPELL_H__
#define __SPELL_H__

#include "Card.h"
#include "Ability.h"
#include "ascii_graphics.h"
#include <memory>

class Spell: public Card {
public:
	std::unique_ptr<Ability> abl;
    Spell(int cost, std::string name, unique_ptr<Ability> p);
    ~Spell() = 0;
	card_template_t card_display() override;
	string get_ability_description() override;

};

#endif
