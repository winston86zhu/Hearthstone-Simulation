#ifndef SORCERY_CANVAS_H
#define SORCERY_CANVAS_H
//
// Created by winstzhu on 11/19/2018.
//


#include <iostream>
#include <memory>
using namespace std;

#include "Player.h"





class Canvas{
    unique_ptr<Player> p1;
    unique_ptr<Player> p2;
public:
    Canvas(unique_ptr<Player> p1,unique_ptr<Player> p2);
    ~Canvas();
    unique_ptr<Player>& get_p1();
    unique_ptr<Player>& get_p2();
    void printcanvas(int cur_player);
};


#endif //SORCERY_CANVAS_H
