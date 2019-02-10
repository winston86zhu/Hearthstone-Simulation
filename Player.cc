#include <utility>

#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include "Player.h"
#include "Card.h"
#include "DeckCollection.h"
#include "CardCollection.h"
#include "GroundCollection.h"
#include "ascii_graphics.h"
#include "Minion.h"
#define DBG false
using namespace std;


Player::Player(string name, ifstream &in): name{std::move(name)}, life{20}, magic{2} {
    Deck = make_unique<DeckCollection>(in);
    Graveyard = make_unique<CardCollection>(30);
    Hand = make_unique<CardCollection>(5);
    Ground = make_unique<GroundCollection>();// ctor constructs a cardcollection with size 5
}

Player::~Player() {
}


unique_ptr<CardCollection>& Player::get_hand() {
    return Hand;
}

unique_ptr<CardCollection>& Player::get_graveyard() {
    return Graveyard;
}
unique_ptr<DeckCollection>& Player::get_deck() {
    return Deck;
}

unique_ptr<GroundCollection>& Player::get_ground() {
    return Ground;
}

int Player::get_magic() {
    return magic;
}

int Player::get_life() {
    return life;
}

string Player::get_name() {
    return name;
}

void Player::draw() {
    if(Deck->get_size() == 0){
        //could throw an exception?
        cerr << "Draw Error - Your Deck is empty, so you can not draw card anymore" <<endl;
    } else if (Hand->get_size() >= 5){
        cerr << "Draw Error - Hand is in Fill Size!" << endl;
    } else {
        auto p = Deck->pop();
        Hand->emplace_card(move(p));
    }
}

void Player::discard(int i) {
    // Only discard hand card
    Hand->delete_ith(i);
}


void Player::set_magic(int i) {
    this->magic = i;
}

void Player::player_print(int i,card_template_t player_tem) {
    if (i == 1) {
        //Top celling
        cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for (int i = 0; i < 165; ++i) {
            cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
        for (int i = 0; i < 11; i++) {
            // if graveyard and ritual are empty
            //cout <<"The current size is " << Ground->get_size() <<endl;
            if (get_ground()->get_ritual() == nullptr && get_graveyard()->get_size() == 0) {
                //cout << "reach print emty card" << endl;
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << CARD_TEMPLATE_BORDER[i] << CARD_TEMPLATE_EMPTY[i]
                     << player_tem[i] << CARD_TEMPLATE_EMPTY[i] << CARD_TEMPLATE_BORDER[i]
                     << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            } else if (get_ground()->get_ritual() == nullptr){
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << CARD_TEMPLATE_BORDER [i]
                     << CARD_TEMPLATE_EMPTY[i] << player_tem[i]
                     << CARD_TEMPLATE_EMPTY[i] << Graveyard->get_top()->card_display()[i] << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            } else if (get_graveyard()->get_size() == 0){
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << Ground->get_ritual()->card_display()[i]<< CARD_TEMPLATE_EMPTY[i]
                     << player_tem[i] << CARD_TEMPLATE_EMPTY[i] <<
                     CARD_TEMPLATE_BORDER[i] << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            } else{
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << Ground->get_ritual()->card_display()[i] <<
                     CARD_TEMPLATE_EMPTY[i] << player_tem[i] <<
                     CARD_TEMPLATE_EMPTY[i] << Graveyard->get_top()->card_display()[i] <<
                     EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            }
        }
        // ADD more
        //Minion Row
        for (int i = 0; i < 11; i++) {
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
            for (int j = 0; j < 5; j++) {
                if(j < Ground->get_size()) {
                    cout << get_ground()->get_cardvec().at(j)->card_display()[i];
                } else{
                    cout << CARD_TEMPLATE_BORDER[i];
                }
            }
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
        }
    } else {
        //Minion Row - player 2
        for (int i = 0; i < 11; i++) {
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
            for (int j = 0; j < 5; j++) {
                if(j < Ground->get_size()) {
                    cout << get_ground()->get_cardvec().at(j)->card_display()[i];
                } else{
                    cout << CARD_TEMPLATE_BORDER[i];
                }
            }
            cout << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
        }
        //Card Row
        cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for (int i = 0; i < 165; ++i) {
            cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << endl;
        for (int i = 0; i < 11; i++) {
            // if graveyard and ritual are empty
            //cout <<"The current size is " << Ground->get_size() <<endl;
            if (get_ground()->get_ritual() == nullptr && get_graveyard()->get_size() == 0) {
                //cout << "reach print emty card" << endl;
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << CARD_TEMPLATE_BORDER[i] << CARD_TEMPLATE_EMPTY[i]
                     << player_tem[i] << CARD_TEMPLATE_EMPTY[i] << CARD_TEMPLATE_BORDER[i]
                     << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
            } else if (get_ground()->get_ritual() == nullptr){
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << CARD_TEMPLATE_BORDER [i]
                     << CARD_TEMPLATE_EMPTY[i] << player_tem[i]
                     << CARD_TEMPLATE_EMPTY[i] << Graveyard->get_top()->card_display()[i] << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            } else if (get_graveyard()->get_size() == 0){
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << Ground->get_ritual()->card_display()[i]<< CARD_TEMPLATE_EMPTY[i]
                     << player_tem[i] << CARD_TEMPLATE_EMPTY[i] <<
                     CARD_TEMPLATE_BORDER[i] << EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            } else{
                cout << EXTERNAL_BORDER_CHAR_UP_DOWN << Ground->get_ritual()->card_display()[i] <<
                     CARD_TEMPLATE_EMPTY[i] << player_tem[i] <<
                     CARD_TEMPLATE_EMPTY[i] << Graveyard->get_top()->card_display()[i] <<
                     EXTERNAL_BORDER_CHAR_UP_DOWN <<endl;
            }
        }
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 165; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}

void Player::RaiseDead(){
    if(Ground->get_size() >= 5) {
        cerr << "Ability Error - Cannot use this card since Ground has 5 cards already" << endl;
    } else if (Graveyard->get_size() == 0){
        cerr << "Ability Error - Cannot use this card since Graveyard is empty" << endl;
    } else {
        auto revive = Graveyard->pop();
        Ground->emplace_card(move(revive));
    }
}

void Player::minion_dead(int dead_index) {
    auto& dead_minion = Ground->get_ith(dead_index);
    if(dead_minion->is_minion()){
        cout << name << "'s " << dead_minion->get_name() << " is dead." << endl;
        Graveyard->emplace_card(move(dead_minion));
        Ground->delete_ith(dead_index);
    }
    else{
        cout << name << "'s " << dead_minion->get_bottom_minion()->get_name() << " is dead." << endl;
        Graveyard->emplace_card(move(dead_minion->get_bottom_minion()));
        Ground->delete_ith(dead_index);
    }
    //The Minion could be in the observer vector
}

void Player::showhand(){
    vector<card_template_t> handvec;
    int j = 0;

    while(j < Hand->get_size()) {
        unique_ptr<Card>& c = Hand->get_ith(j);
        //cout << "this is " << get_name() << "show hand"<< c->get_name()<< endl;
        card_template_t h;
        h = c->card_display();
        handvec.emplace_back(h);
        j++;

    }

    int diff =  5 - j;
    for (int m = 0; m < diff; m++) {
        handvec.emplace_back(CARD_TEMPLATE_BORDER);
    }

    int turn = handvec.size() / 5;
    int left = handvec.size() % 5;
    //cout <<"left is" <<left <<endl;
    for (int k = 0; k < turn; ++k) {
        for (int i = 0; i < 11; ++i) {
            for (int j = 0; j < 5; ++j) {
                cout << handvec[j][i];
            }
            cout << endl;
        }
    }
    if (left == 0) {
        return;
    }
    for (int i = 0; i < 11; ++i) {
        for (int j = 0; j < left; ++j) {
            cout << handvec[j][i];
        }
        cout << endl;
    }



}

void Player::set_life(int i) {
    life = i;
}

void Player::round_start(unique_ptr<Player>& this_player,unique_ptr<Player>& other, int current_player) {
    magic += 1;
    draw();
    Ground->start_round(this_player,other,current_player); // all triggered abilities get executed
}

void Player::round_end(unique_ptr<Player>& this_player,unique_ptr<Player>& other,int current_player){
    Ground->end_round(this_player,other,current_player); // all triggered abilities get executed
}


void Player::play(int i, unique_ptr<Player>& this_player, unique_ptr<Player>& other, istream &in, int current_player) {
    // Play a Minion. Ritual, Spell
    unique_ptr<Card>& played_card = Hand->get_ith(i);
    int cost = played_card->get_cost();
    bool play_success = false;
    play_success = played_card->play(this_player, other, i, in, current_player);
    if(play_success) {
        int new_magic = this->get_magic() - cost;
        set_magic(new_magic);
    } else {
        cerr << "play error - This play is invalid, check your input" <<endl;
    }
}



void Player::use(int i,unique_ptr<Player>& this_player, unique_ptr<Player>& other, istream &in,int current_player) {
    //Use is only for activated ability with no target
    if(i > this->Ground->get_size()){
        cerr <<  "- use error: input i is not valid" << endl;
    }
    unique_ptr<Card>& my_minion = Ground->get_ith(i);
    if(my_minion->get_action() > 0) {
        int cost = my_minion->get_activation_cost();
        if(magic >= cost && my_minion->get_ability_type() == "activated" && my_minion->use(this_player,other, i, in, current_player)) {
            set_magic(magic - cost);
        }
        else
            cerr << "Activate ability failed" << endl;
    } else {
        cerr << "- use error: The minion has no action left" << endl;
    }
}


