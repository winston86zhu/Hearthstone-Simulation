#include "ApprenticeSummoner.h"

ApprenticeSummoner::ApprenticeSummoner(): Minion{1, "Apprentice Summoner", 1, 1}, abl{new ApprenticeSummonerActv} {}
ApprenticeSummoner::~ApprenticeSummoner(){
	//delete dealdamage;
}

std::string ApprenticeSummoner::get_ability_description(){
	return abl->get_description();
}

int ApprenticeSummoner::get_activation_cost(){
	return abl->get_activation_cost();
}

bool ApprenticeSummoner::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	// magic checking in Player::use
	// read in the target
	if(get_action() <= 0){
		cerr << "Use Error - This minion does not have enough action" <<endl;
	}
	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;
    bool result =  abl->execute(this_player, i, other, 0, player1, player2);
    if(result) {
        reset_action(get_action() - 1);
    }
    return result;
}

string ApprenticeSummoner::get_ability_type() {
	return "activated";
}
