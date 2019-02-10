#include <utility>

#include <string>
#include <memory>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>

#define DBG false
using namespace std;

#include "GroundCollection.h"
#include "Minion.h"
#include "Player.h"

GroundCollection::GroundCollection() :
        CardCollection{5}, ritual_card{nullptr} {}

GroundCollection::~GroundCollection() {

}

bool GroundCollection::SummonMinion(unique_ptr<Card> &new_minion, unique_ptr<Player> &this_player,
                                    unique_ptr<Player> &other, int current_player) {

    unique_ptr<Player> &player1 = ( current_player == 1 ) ? this_player : other;
    unique_ptr<Player> &player2 = ( current_player == 2 ) ? this_player : other;
    //UPDATE for APSNP Order*************************************
    //Do not need to check minion cuz no minion card has my_enter/ both_enter effect
    //check active player ground
    int size_tmp = get_size();
    for (auto& card : this_player->get_ground()->get_cardvec()) {
        Card* address;
        if(card->is_minion())
            address = card.get();
        else
            address = card->get_bottom_minion().get();

        if(find(enter.begin(),enter.end(), address) != enter.end()){
            //cout << "My exit minion is triggered" <<endl;
            cout << "Ground.cc index = " << this_player->get_ground()->get_index(card.get()) << endl;
            if(size_tmp == get_size())
                card->execute_trigger(this_player, this_player->get_ground()->get_index(card.get()), this_player, get_size() - 1, player1, player2);
        }
    }
    //check active player ritual
    if(this_player->get_ground()->get_ritual() != nullptr){
        if(find(enter.begin(),enter.end(),this_player->get_ground()->get_ritual().get()) != enter.end()){
            if(size_tmp == get_size())
                this_player->get_ground()->get_ritual()->execute_trigger(this_player, 0, this_player, get_size() - 1, player1, player2);
        }
    }
    //Check Opp ground card
    for (auto& card : other->get_ground()->get_cardvec()) {
        //cout << "Ground.cc other loop" << endl;
        //cout << "Ground.cc card address" << card.get() << endl;
        Card* address;
        if(card->is_minion())
            address = card.get();
        else
            address = card->get_bottom_minion().get();
        if(find(enter.begin(),enter.end(),address) != enter.end()){
            cout << "Ground.cc index = " << other->get_ground()->get_index(card.get()) << endl;
            if(size_tmp == get_size())
                card->execute_trigger(other, other->get_ground()->get_index(card.get()), this_player, get_size() - 1, player1, player2);
        }
    }
    // check opp ritual
    if(other->get_ground()->get_ritual() != nullptr){
        if(find(enter.begin(),enter.end(),other->get_ground()->get_ritual().get()) != enter.end()){
            if(size_tmp == get_size())
                other->get_ground()->get_ritual()->execute_trigger(other, 0, this_player, get_size() - 1, player1, player2);
        }
    }
    return true;
}

void GroundCollection::set_ritual(unique_ptr<Card> &r) {
    ritual_card = std::move(r);
}

unique_ptr<Card> &GroundCollection::get_ritual() {
    return ritual_card;
}

void GroundCollection::ExitMinion(unique_ptr<Card> &exit_minion, unique_ptr<Player> &this_player, unique_ptr<Player> &other,
                             int current_player) {

    unique_ptr<Player> &player1 = ( current_player == 1 ) ? this_player : other;
    unique_ptr<Player> &player2 = ( current_player == 2 ) ? this_player : other;

    //This is not needed cuz I checked every card by ASPNP turn and if it in exit, it does exceute..
    for (auto& card : this_player->get_ground()->get_cardvec()) {
        cout << "Ground.cc this loop" << endl;
        cout << "Ground.cc card address" << card.get() << endl;
        Card* address;
        if(card->is_minion())
            address = card.get();
        else
            address = card->get_bottom_minion().get();
        if(find(exit.begin(),exit.end(), address) != exit.end()){
            //cout << "My exit minion is triggered" <<endl;
            cout << "Ground.cc index = " << this_player->get_ground()->get_index(card.get()) << endl;
            card->execute_trigger(this_player, this_player->get_ground()->get_index(card.get()), this_player, get_size() - 1, player1, player2);
        }
    }
    for (auto& card : other->get_ground()->get_cardvec()) {
      //  cout << "Ground.cc other loop" << endl;
      //  cout << "Ground.cc card address" << card.get() << endl;
        Card* address;
        if(card->is_minion())
            address = card.get();
        else
            address = card->get_bottom_minion().get();
        if(find(exit.begin(),exit.end(),address) != exit.end()){
            cout << "Ground.cc index = " << other->get_ground()->get_index(card.get()) << endl;
            card->execute_trigger(other, other->get_ground()->get_index(card.get()), this_player, get_size() - 1, player1, player2);
        }
    }
}

void GroundCollection::start_round(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int current_player) {
    unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
    unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
    //magic++ in Player::round_start()
    for (auto &card : cardvec) {
        //At the start of every turn, every minion owned by the player whose turn, it is is restored to 1 action.
        card->reset_action(1);
    }
    if(ritual_card != nullptr) {
        if (find(start.begin(), start.end(), ritual_card.get()) != start.end()) {
            ritual_card->execute_trigger(this_player, 0, this_player, get_size(), player1, player2);
        }
    }
    
}


void GroundCollection::end_round(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int current_player) {
    unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
    unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
    for (auto& card : this_player->get_ground()->get_cardvec()) {
        Card* address;
        if(card->is_minion())
            address = card.get();
        else
            address = card->get_bottom_minion().get();
        if(find(end.begin(),end.end(),address) != end.end()){
            card->execute_trigger(this_player, this_player->get_ground()->get_index(card.get()), this_player, get_size(), player1, player2);
        }
    }
}

void GroundCollection::delete_ritual() {
    ritual_card = nullptr;
}

void GroundCollection::update_ritual(int val) {
    if (ritual_card != nullptr) {
        ritual_card->add_charge(val);
    }
}

void GroundCollection::set_ith(int i, unique_ptr<Card> &cd) {
    cardvec.at(static_cast<unsigned long>(i)).swap(cd);
}

void GroundCollection::attach(Card *cd, int i) {
    if (i == 1)
        enter.emplace_back(cd);
    else if (i == 4)
        exit.emplace_back(cd);
    else if (i == 5)
        start.emplace_back(cd);
    else if (i == 6)
        end.emplace_back(cd);
}

void GroundCollection::dettach(Card *cd, vector<Card *> &target_observer_vec) {
    for (auto it = target_observer_vec.begin(); it != target_observer_vec.end(); ++it) {
        if (*it == cd) {
            target_observer_vec.erase(it);
            break;
        }
    }
}

void GroundCollection::dettach_all(Card *cd) {
    dettach(cd, enter);
    dettach(cd, end);
    dettach(cd, exit);
    dettach(cd, start);
}






