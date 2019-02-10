#include "RaiseDead.h"

RaiseDead::RaiseDead(): Spell{1, "RaiseDead", std::make_unique<RaiseDeadActv>()} {}

RaiseDead::~RaiseDead(){}

bool RaiseDead::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
    cout << "Raise Dead - Resurrent the dead minion" <<endl;
	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
	bool result = abl->execute(this_player, i, other, 0, player1, player2);
	if(result) {
        this_player->get_hand()->delete_ith(i);
    } else {
	    cerr << "Raise Dead Error - There is no card in the graveyard" <<endl;
	    return false;
	}
	return result;
}

string RaiseDead::get_ability_type() {
    return "trigger";
}
