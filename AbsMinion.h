#ifndef __ABSMINION_H__
#define __ABSMINION_H__
#include <iostream>
#include <string>
#include "Card.h"
using namespace std;

class AbsMinion: public Card {
public:
    AbsMinion(int cost, std::string name);
    virtual ~AbsMinion() = 0;
};

#endif
