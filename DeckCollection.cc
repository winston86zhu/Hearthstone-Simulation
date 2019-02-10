#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <fstream>

#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>

#define DBG false
using namespace std;

#include "DeckCollection.h"
#include "Banish.h"
#include "PotionSeller.h"
#include "RaiseDead.h"
#include "Recharge.h"
#include "Spell.h"
#include "MasterSummoner.h"
#include "Card.h"
#include "AuraOfPower.h"
#include "Silence.h"
#include "Standstill.h"
#include "Unsummon.h"
#include "Airelemental.h"
#include "Blizzard.h"
#include "BoneGolem.h"
#include "Disenchant.h"
#include "Enrage.h"
#include "FireElemental.h"
#include "Giantstrength.h"
#include "Haste.h"
#include "MagicFatigue.h"
#include "NovicePyromancer.h"
#include "Earthelemental.h"
#include "ApprenticeSummoner.h"
#include "DarkRitual.h"
#include "Nuke.h"


DeckCollection::DeckCollection(ifstream &src) : CardCollection{30}{
    string one_card;
    unique_ptr<Card> new_card;
    while (getline(src, one_card)) {

        new_card = (read_card(one_card));
        if (new_card == nullptr) {
            //cout << new_card->get_name()<<endl;
            cerr << "- Read Card Error: You have entered the wrong card name." << endl;
        } else {
           // cout << "Now the read_name is " << new_card->get_name() << new_card->get_attack() << endl;
            emplace_card(move(new_card));
        }
        //emplace_card((read_card(one_card)));
    }
}

DeckCollection::~DeckCollection() {
}

unique_ptr<Card> DeckCollection::read_card(string name) {//else return nullptr
    string ability_name;
    string card_name;
    string ability_description;
    string enchantment_description;
    unique_ptr<Card> new_card;
    if (name == "Banish") {
        //ability_description = "Destroy target minion or ritual";
        //unique_ptr<Activated_Ability> activated = make_unique<Destroy_MinionRitual>();
        //unique_ptr<Triggered_Ability> triggered = nullptr;
        //cout << "reaching banish" << endl;
        new_card = std::make_unique<Banish>();
        // or
        /* Banish* new_card_2 = make_unique<Banish>().release();
         Card * new_card_cardptr = new_card_2;
         unique_ptr<Card> final_card = make_unique<Card>(*new_card_cardptr);*/
    } else if (name == "Potion Seller") {
        new_card = std::make_unique<PotionSeller>();
    } else if (name == "Unsummon") {
        new_card = std::make_unique<Unsummon>();
    } else if (name == "Recharge") {
        ability_description = "Your ritual gains 3 charges";
        new_card = std::make_unique<Recharge>();
    } else if (name == "Disenchant") {
        ability_description = "Destroy the top enchantment on target minion";
        new_card = std::make_unique<Disenchant>();
    } else if (name == "Raise Dead") {
        ability_description = "Resurrect the top minion in your graveyard and set its defence to 1";
        new_card = std::make_unique<RaiseDead>();
    } else if (name == "Blizzard") {
        new_card = std::make_unique<Blizzard>();
    } else if (name == "Air Elemental") {
        new_card = std::make_unique<AirElemental>();
    } else if (name == "Earth Elemental") {
        new_card = std::make_unique<EarthElemental>();
    } else if (name == "Bone Golem") {
        new_card = make_unique<BoneGolem>();
    } else if (name == "Fire Elemental") {
        ability_description = "Whenever an opponents minion enters play, deal 1 damage to it.";
        new_card = make_unique<FireElemental>();
    } else if (name == "Novice Pyromancer") {
        ability_description = "Deal 1 damage to target minion";
        new_card = make_unique<NovicePyromancer>();
    } else if (name == "Apprentice Summoner") {
        ability_description = "Summon a 1/1 air elemental";
        new_card = make_unique<ApprenticeSummoner>();
    } else if (name == "Master Summoner") {
        ability_description = "Summon up to three 1/1 Air Elemental";
        new_card = make_unique<MasterSummoner>();
        //***************Enchantment*********************8
    } else if (name == "Giant Strength") {
        new_card = make_unique<GiantStrength>();
    } else if (name == "Enrage") {
        new_card = make_unique<Enrage>();
    } else if (name == "Haste") {
        //Make_unique a Haste pointer, test if it follows polymor
        enchantment_description = "Enchanted minion gains +1 action each turn";
        new_card = make_unique<Haste>();
    } else if (name == "Magic Fatigue") {
        enchantment_description = "Enchanted minion's activated ability costs 2 more";
        new_card = make_unique<MagicFatigue>();
    } else if (name == "Silence") {
        new_card = make_unique<Silence>();
    }
        //*****************Ritual**************************
    else if (name == "Dark Ritual") {
        new_card = make_unique<DarkRitual>();
    } else if (name == "Aura of Power") {
        new_card = make_unique<AuraOfPower>();
    } else if (name == "Standstill") {
        new_card = make_unique<StandStill>();
    } else if (name == "Nuke"){
        new_card = make_unique<Nuke>();
    }
    else {
        return nullptr;
    }
    return (new_card);
}

void DeckCollection::shuffle() {
    //Check Fisher Yeats
    for (int i = 0; i < get_size(); i++) {
        srand(time(NULL) + i);
        random_shuffle(cardvec.begin(), cardvec.end());
    }
}
