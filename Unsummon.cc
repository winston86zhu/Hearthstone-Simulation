#include "Unsummon.h"
#include "Spell.h"

Unsummon::Unsummon(): Spell{1, "Unsummon", std::make_unique<UnsummonActv>()} {}

Unsummon::~Unsummon(){}

bool Unsummon::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	unique_ptr<Player> &player1 = (current_player == 1)? this_player:other;
	unique_ptr<Player> &player2 = (current_player == 2)? this_player:other;

	int p, t;
	if(!(in >> p >> t)){
		cerr << "Unsummon error - please specify the target" << endl;
		return false;
	}
	else if(p != 1 && p != 2){
		cerr << "Unsummon error - please specify player by 1 or 2" << endl;
		return false;
	}

	unique_ptr<Player> &target_player = (p == 1) ? player1:player2;
	if(t < 1 || t > target_player->get_ground()->get_size()){
		cerr << "Unsummon error - minion index not in range" << endl;
		return false;
	}

	t = t - 1;

	bool result = abl->execute(this_player, i, target_player, t, player1, player2);
    this_player->get_hand()->delete_ith(i);
    return result;
}

string Unsummon::get_ability_type() {
    return "trigger";
}
