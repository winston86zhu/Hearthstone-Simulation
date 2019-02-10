#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>
#define DBG false
using namespace std;
#include "CardCollection.h"
#include "Card.h"


CardCollection::CardCollection(int capacity):capacity{capacity}{}

CardCollection::~CardCollection() {
    /*for (auto &i : cardvec) {
        delete i;
    }*/ //Comment out because of uique_ptr
}

void CardCollection::emplace_card(unique_ptr<Card> cd) {
    if((int)cardvec.size() < capacity){
        cardvec.emplace_back(move(cd));        
    }
}

//Note Sure
void CardCollection::delete_ith(int i) {
    cardvec.erase(cardvec.begin() + i);
}

unique_ptr<Card>& CardCollection::get_ith(int i) {
    return cardvec[i];
}

int CardCollection::get_size() {
    return (int)cardvec.size();
}

unique_ptr<Card>& CardCollection::get_top() {
    return cardvec.back();
}

int CardCollection::get_index(Card * cd){
    int i = 0;
    for(auto it = cardvec.begin(); it != cardvec.end(); ++it, ++i) {
        if ((*it).get() == cd) {
            return i;
            break;
        }
    }
    return -1;
}

unique_ptr<Card> CardCollection::pop() {
    auto p = move(cardvec.back());
    cardvec.pop_back();
    return p;
}

vector<unique_ptr<Card>>& CardCollection::get_cardvec() {
    return cardvec;
}

bool CardCollection::is_empty() {
    return (cardvec.empty());
}


