#ifndef SORCERY_DECKCOLLECTION_H
#define SORCERY_DECKCOLLECTION_H
#include <iostream>
#include <memory>
#include "CardCollection.h"
#define DBG false
using namespace std;
class Player;

class DeckCollection: public CardCollection {
public:
    explicit DeckCollection(ifstream &src);
    ~DeckCollection();
    unique_ptr<Card> read_card(string name);
    void shuffle();
};


#endif //SORCERY_DECKCOLLECTION_H
