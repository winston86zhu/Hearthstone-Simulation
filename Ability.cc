#include <utility>

//
// Created by winstzhu on 11/24/2018.
//

#include "Ability.h"
#include "Airelemental.h"
#include "Player.h"
#include "Minion.h"
#include "Customized.h"
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

using namespace std;
#define DBG false

Ability::Ability(string description) : description{description} {}

Ability::~Ability() {}

string Ability::get_description() {
    return description;
}

int Ability::get_activation_cost() {
    return -1;
}


Triggered_Ability::Triggered_Ability(string description) : Ability{description} {}

Activated_Ability::Activated_Ability(string description, int activation_cost) : Ability{description},
                                                                                activation_cost{activation_cost} {}

int Activated_Ability::get_activation_cost() {
    return activation_cost;
}

// Three Minion's activation ability =============================
// Novice Pyromancer
NovicePyromancerActv::NovicePyromancerActv() : Activated_Ability{"Deal 1 damage to target minion", 1} {}

bool
NovicePyromancerActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                              int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {

    target_player->get_ground()->get_ith(target_minion) = make_unique<Customized>(0, -1,
                                                                                  target_player->get_ground()->get_ith(
                                                                                          target_minion));
    return true;
}

// Apprentice Summoner
ApprenticeSummonerActv::ApprenticeSummonerActv() : Activated_Ability{"Summon a 1/1 air elemental", 1} {}

bool
ApprenticeSummonerActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                                int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {

    auto &ground = using_player->get_ground();
    // checking for space
    if (ground->get_size() >= 5) {
        cerr << "Ground is full already!" << endl;
        return false;
    }

    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;
    unique_ptr<Card> tmp = make_unique<AirElemental>();

    // do the actually summoning
    using_player->get_ground()->emplace_card(move(tmp));

    // trigger the triggers
    ground->SummonMinion(using_player->get_ground()->get_ith(using_player->get_ground()->get_size() - 1), using_player,
                         not_using_player, current_player);

    return true;

}

// Master Summoner
MasterSummonerActv::MasterSummonerActv() : Activated_Ability{"Summon up to three 1/1 air elementals", 2} {}

bool MasterSummonerActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                                 int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    bool final_result = false;
    int amount = min(3, 5 - using_player->get_ground()->get_size());

    cout << "Master Summoner will summon " << amount << " Air Elemental" << endl;

    for (int i = 0; i < amount; i++) {
        unique_ptr<Card> tmp = make_unique<AirElemental>();
        auto &ground = using_player->get_ground();
        int current_player = ( using_player == player1 ) ? 1 : 2;
        unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;

        using_player->get_ground()->emplace_card(move(tmp));

        ground->SummonMinion(using_player->get_ground()->get_ith(using_player->get_ground()->get_size() - 1),
                             using_player, not_using_player, current_player);

        if (!final_result)
            final_result = true;
    }

    return final_result;

}

// ============================================

// Six Spell activation ability =============================
BanishActv::BanishActv() : Activated_Ability{"Destroy target minion or ritual", 0} {}

bool BanishActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                         int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {

    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;

    if (target_minion == 5) {
        // delete ritual
        target_player->get_ground()->delete_ritual();
    } else {
        // remove ownership of card from ground and emplace_back at graveyard
        target_player->get_ground()->ExitMinion(target_player->get_ground()->get_ith(target_minion), using_player,
                                                not_using_player, current_player);
        target_player->minion_dead(target_minion);
    }
    return true;
}

UnsummonActv::UnsummonActv() : Activated_Ability{"Return target minion to its owner's hand", 0} {}

bool UnsummonActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                           int target_minion,
                           unique_ptr<Player> &player1, unique_ptr<Player> &player2) {

    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;
    //Reached

    target_player->get_ground()->ExitMinion(target_player->get_ground()->get_ith(target_minion), using_player,
                                            not_using_player, current_player);
    auto &dead_minion = target_player->get_ground()->get_ith(target_minion);
    if (dead_minion->is_minion()) {
        cout << target_player->get_name() << "'s " << dead_minion->get_name() << " is unsummoned." << endl;
        target_player->get_hand()->emplace_card(move(dead_minion));
        target_player->get_ground()->delete_ith(target_minion);
    } else {
        cout << target_player->get_name() << "'s " << dead_minion->get_bottom_minion()->get_name() << " is unsummoned."
             << endl;
        target_player->get_hand()->emplace_card(move(dead_minion->get_bottom_minion()));
        target_player->get_ground()->delete_ith(target_minion);
    }

    return true;
}

NukeAbv::NukeAbv() : Activated_Ability{"Clear the target player's ground cards", 2} {}

bool NukeAbv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                      int target_minion,
                      unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;
    for (int dummy = 0; dummy < target_player->get_ground()->get_size(); dummy++) {
        target_player->get_ground()->ExitMinion(target_player->get_ground()->get_ith(dummy), using_player,
                                                not_using_player, current_player);
        target_player->minion_dead(dummy);
    }
    return true;
}


RechargeActv::RechargeActv() : Activated_Ability{"Your ritual gains 3 charges", 0} {}

bool RechargeActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                           int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    cout << "Ability.cc racharge 1" << endl;
    using_player->get_ground()->get_ritual()->add_charge(3);
    cout << "Ability.cc racharge 1" << endl;

    return true;
}

DisenchantActv::DisenchantActv() : Activated_Ability{"Destroy the top enchantment on target minion", 0} {}

bool DisenchantActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                             int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    std::string valid_number{"01234"};

    Card *minion = target_player->get_ground()->get_ith(target_minion).get();
    Card *above_top;
    if (minion->is_disenchantable()) {
        // set the minion
        target_player->get_ground()->get_ith(target_minion) = std::move(minion->get_target());
    } else {
        above_top = minion->get_above_top_enchantment();
        if (above_top) {
            above_top->get_target() = std::move(above_top->get_target()->get_target());
        } else {
            std::cerr << "Oops! No enchantment on minion. Better check next time!" << endl;
        }
    }

    return true;
}

RaiseDeadActv::RaiseDeadActv() : Activated_Ability{
        "Resurrect the top minion in your graveyard and set its defence to 1", 0} {}

bool RaiseDeadActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                            int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;
    if (using_player->get_graveyard()->get_size() == 0) {
        cerr << "Raise Dead Error - You do not have any card in the graveyard" << endl;
    }
    // transfer from graveyard to ground
    bool result = using_player->get_ground()->SummonMinion(using_player->get_graveyard()->get_top(), using_player,
                                                           not_using_player, current_player);
    if (result) {
        auto p = using_player->get_graveyard()->pop();//!!!
        using_player->get_ground()->emplace_card(move(p));
        //using_player->get_hand()->delete_ith(i);

        // set defense to 1
        int size = using_player->get_ground()->get_size();
        Card *minion = using_player->get_ground()->get_ith(size - 1).get();
        int defense = minion->get_defense();
        using_player->get_ground()->get_ith(size) = make_unique<Customized>(0, -( defense - 1 ),
                                                                            using_player->get_ground()->get_ith(size));
        return true;
    } else {
        return false;
    }
}


BlizzardActv::BlizzardActv() : Activated_Ability{"Deal 2 damages to all minions", 0} {}

bool BlizzardActv::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                           int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;

    GroundCollection *ground = using_player->get_ground().get();
    for (int i = 0; i < ground->get_size(); i++) {
        ground->get_ith(i) = make_unique<Customized>(0, -2, ground->get_ith(i));
    }

    ground = not_using_player->get_ground().get();
    for (int i = 0; i < ground->get_size(); i++) {
        ground->get_ith(i) = make_unique<Customized>(0, -2, ground->get_ith(i));
    }

    return true;

}
// ============================================

// Trigger abilities ===============

BoneGolemTrig::BoneGolemTrig() : Triggered_Ability{"Gain +1/+1 whenever a minion leaves play"} {}

bool BoneGolemTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                            int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    using_player->get_ground()->get_ith(using_minion) = make_unique<Customized>(1, 1,
                                                                                using_player->get_ground()->get_ith(
                                                                                        using_minion));
    cout << "Ability.cc Bone golem" << endl;
    return true;

}


FireElementalTrig::FireElementalTrig() : Triggered_Ability{
        "Whenever an opponent's minion enters play, deal one damage to it"} {}

bool FireElementalTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                                int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    target_player->get_ground()->get_ith(target_minion) = make_unique<Customized>(0, -1,
                                                                                  target_player->get_ground()->get_ith(
                                                                                          target_minion));
    return true;

}


PotionSellerTrig::PotionSellerTrig() : Triggered_Ability{"At the end of your turn, all your minions gain +0/+1"} {}

bool PotionSellerTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                               int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    GroundCollection *ground = using_player->get_ground().get();
    for (int i = 0; i < ground->get_size(); i++) {
        ground->get_ith(i) = make_unique<Customized>(0, 1, ground->get_ith(i));
    }
    return true;
}


DarkRitualTrig::DarkRitualTrig() : Triggered_Ability{"At the start of your turn, gain one magic"} {}

bool DarkRitualTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                             int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    using_player->set_magic(using_player->get_magic() + 1);
    return true;
}

AuraOfPowerTrig::AuraOfPowerTrig() : Triggered_Ability{
        "Whenever a minion enters play under your control, it gains +1/+1"} {}

bool AuraOfPowerTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                              int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {

    using_player->get_ground()->get_ith(target_minion) = make_unique<Customized>(1, 1,
                                                                                 using_player->get_ground()->get_ith(
                                                                                         target_minion));
    return true;
}

StandstillTrig::StandstillTrig() : Triggered_Ability{"Whenever a minion enters play, destroy it"} {}

bool StandstillTrig::execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player,
                             int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) {
    int current_player = ( using_player == player1 ) ? 1 : 2;
    unique_ptr<Player> &not_using_player = ( current_player == 1 ) ? player2 : player1;

    Card *tmp = target_player->get_ground()->get_ith(target_minion).get();

    target_player->get_ground()->ExitMinion(target_player->get_ground()->get_ith(target_minion), using_player,
                                            not_using_player, current_player);
    target_player->minion_dead(target_minion);

    using_player->get_ground()->dettach_all(tmp);
    not_using_player->get_ground()->dettach_all(tmp);

    return true;
}

// ============================================
