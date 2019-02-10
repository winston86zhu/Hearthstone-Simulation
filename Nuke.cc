#include "Nuke.h"
#include "Spell.h"
#include "Ability.h"

Nuke::Nuke(): Spell{2, "Nuke", std::make_unique<NukeAbv>()} {}

Nuke::~Nuke(){}

bool Nuke::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
    int p;
    char t;
    if(!(in >> p >> t)){
        cerr << "Nuke - Enter target player and minion you want to destroy" <<endl;
        return false;
    }
    unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
    unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
    unique_ptr<Player> &target_player = (p == 1) ? player1:player2;
    int t_int;
    if(t == 'r')
        t_int = 6;
    else{
        t_int = t - '0';
        if(t_int < 1 || t_int > target_player->get_ground()->get_size()){
            cerr << "Banish - target minion index out of range" <<endl;
            return false;
        }
    }

    t_int = t_int - 1;
    //cout << "reached before execute" <<endl;
    bool result = abl->execute(this_player, i, target_player, t_int, player1, player2);
    if(result) {
        this_player->get_hand()->delete_ith(i);
    }
    return result;
}

string Nuke::get_ability_type() {
    return "trigger";
}

bool Nuke::execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player,
                             int target_minion, unique_ptr<Player> &player_1, unique_ptr<Player> &player_2){
    return abl->execute(triggered_player,triggered_minion,target_player,target_minion,player_1,player_2);
}
