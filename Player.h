#ifndef SORCERY_PLAYER_H
#define SORCERY_PLAYER_H
#include <iostream>
#include <memory>
#include "CardCollection.h"
#include "GroundCollection.h"
using namespace std;
#include "DeckCollection.h"
#include "ascii_graphics.h"

class Player {
    string name;
    int life;
    int magic;
    unique_ptr<CardCollection> Hand;
    unique_ptr<CardCollection> Graveyard;
    unique_ptr<DeckCollection> Deck;
    unique_ptr<GroundCollection> Ground;
public:
    Player(string name, ifstream &in);//make need another field to construct all the cardcollections
    ~Player();
    /*********Getters*********/
    unique_ptr<CardCollection>& get_hand();
    unique_ptr<CardCollection>& get_graveyard();
    unique_ptr<DeckCollection>& get_deck();
    unique_ptr<GroundCollection>& get_ground();
    int get_magic();
    int get_life();
    void set_life(int i);
    string get_name();
    //***********Setter*******************
    void set_magic(int i);
    //*********Actions A Player May Perform*********//*
    void draw();
    void discard(int i);
    void play(int i, unique_ptr<Player>& this_player,unique_ptr<Player>& other, istream &in, int current_player);
     //current_player is 1 pr 2, when current_player = 1, it means this _player is p1, otherwise this_player is p2.
     void use(int i,unique_ptr<Player>& this_player, unique_ptr<Player>& other, istream &in,int current_player);
     //*********Print Function*********//*
     void player_print(int i,card_template_t player_tem);
    /*********Controller Function for Stages*********/
    void round_start(unique_ptr<Player>& this_player,unique_ptr<Player>& other, int current_player);
    void round_end(unique_ptr<Player>& this_player,unique_ptr<Player>& other, int current_player);
    void RaiseDead();
    void minion_dead(int dead_index);
    void showhand();
};


#endif //HEARTHSTONE_HAND_PLAYER_H
