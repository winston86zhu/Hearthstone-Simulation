#ifndef SORCERY_GROUNDCOLLECTION_H
#define SORCERY_GROUNDCOLLECTION_H
#include <iostream>
#include <memory>
#include "CardCollection.h"
#define DBG false
using namespace std;
class Player;
class Ritual;
class Minion;

class GroundCollection :public CardCollection{
    unique_ptr<Card> ritual_card;
    vector<Card *> enter;
    vector<Card *> exit;
    vector<Card *> start;
    vector<Card *> end;
public:
    GroundCollection();
    ~GroundCollection();
    //****************Getter**************
    unique_ptr<Card>& get_ritual();
    //****************Setter**************
    void set_ritual(unique_ptr<Card> &r);
    void delete_ritual();
    void update_ritual(int val);
    //*****************Stage Controller*******************8
    bool SummonMinion(unique_ptr<Card> &new_minion, unique_ptr<Player> &this_player,
                                    unique_ptr<Player> &other, int current_player);
    void ExitMinion(unique_ptr<Card> &exit_minion, unique_ptr<Player>& this_player, unique_ptr<Player>& other,int current_player);
    void start_round(unique_ptr<Player>& this_player, unique_ptr<Player>& other, int current_player);
    void end_round(unique_ptr<Player>& this_player, unique_ptr<Player>& other, int current_player);
    void set_ith(int i, unique_ptr<Card>& cd);
    //*****************For Observer Pattern***********************
    void attach(Card *cd, int i);
    void dettach(Card *cd,vector<Card *>& target_observer_vec);
    void dettach_all(Card *cd);
};

#endif //SORCERY_GROUNDCOLLECTION_H
