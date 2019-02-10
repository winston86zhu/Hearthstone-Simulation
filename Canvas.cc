#include <utility>

#include <utility>

//
// Created by winstzhu on 11/19/2018.
//

#include "Canvas.h"
#include "ascii_graphics.h"

#include <iostream>
using namespace std;

#include "Player.h"


Canvas::Canvas(unique_ptr<Player> p1, unique_ptr<Player> p2):p1{move(p1)},p2{move(p2)}{}

// We made a Player owns 2 Player pointers so players will be deleted
Canvas::~Canvas() = default;

unique_ptr<Player>& Canvas::get_p1() {
    return p1;
}

unique_ptr<Player>& Canvas::get_p2() {
    return p2;
}

void Canvas::printcanvas(int cur_player) {
    card_template_t player1 = display_player_card(1, p1->get_name(), p1->get_life(), p1->get_magic());
    card_template_t player2 = display_player_card(2, p2->get_name(), p2->get_life(), p2->get_magic());
    if(cur_player == 1){
        // print player 1
        p1->player_print(1,player1);
        // print center graphic
        for (auto it = CENTRE_GRAPHIC.begin() ; it != CENTRE_GRAPHIC.end(); ++it) {
            cout << *it << endl;
        }
        // print player 2
        p2->player_print(2,player2);
    }
    else{
        p2->player_print(1,player2);
        for (auto it = CENTRE_GRAPHIC.begin() ; it != CENTRE_GRAPHIC.end(); ++it) {
            cout << *it << endl;
        }
        p1->player_print(2,player1);
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 165; ++i) {
        cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << endl;
}


