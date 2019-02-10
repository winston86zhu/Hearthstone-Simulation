//
// Created by winstzhu on 11/19/2018.
//
#include <string>
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

#ifndef SORCERY_CARDCOLLECTION_H
#define SORCERY_CARDCOLLECTION_H

class Card;

class CardCollection {
protected:
    vector<unique_ptr<Card>> cardvec;
    int capacity;
public:
    CardCollection(int capacity);
    virtual ~CardCollection();
    //********************Getter Function********************//
    int get_size();
    int get_index(Card * cd);
    unique_ptr<Card>& get_ith(int i);
    unique_ptr<Card>& get_top();
    vector<unique_ptr<Card>>& get_cardvec();
    bool is_empty();
    //********************Modifier to Vector********************//
    void emplace_card(unique_ptr<Card> cd);
    void delete_ith(int i);
    unique_ptr<Card> pop();
};


#endif //SORCERY_CARDCOLLECTION_H
