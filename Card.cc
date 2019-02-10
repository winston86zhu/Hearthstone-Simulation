#include "Card.h"
using namespace std;

Card::Card(int cost, std::string name): cost{cost}, name{name} {}

Card::~Card(){}

int Card::get_cost(){
	return cost;
}

std::string Card::get_name(){
	return name;
}

int Card::get_attack(){
	return 0;
}

int Card::get_defense(){
	return -1;
}

int Card::get_action(){
	return 1;
}

std::string Card::get_ability_description(){
	return std::string(); // empty string
}

void Card::reset_action(int val){
	return;
}

int Card::get_activation_cost(){
	return -1;
}

bool Card::play(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	return false;
}
bool Card::use(unique_ptr<Player> &this_player, unique_ptr<Player> &other, int i, istream &in, int current_player){
	return false;
}


void Card::attack_player(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other){

}
void Card::attack_minion(unique_ptr<Player> &this_player, int i, unique_ptr<Player> &other, int j){

}

bool Card::is_enchantment(){
	return false;
}

bool Card::is_disenchantable(){
	return false;
}

Card* Card::get_above_top_enchantment(){
	return nullptr;
}

unique_ptr<Card>& Card::get_target(){
	static unique_ptr<Card> not_found;
    return not_found;
}

bool Card::is_minion(){
	return false;
}

unique_ptr<Card>& Card::get_bottom_minion(){
    static unique_ptr<Card> not_found;
    return not_found;
}

card_template_t Card::card_display() {
    return CARD_TEMPLATE_EMPTY;
}

string Card::get_ability_type() {
    return "None";
}

void Card::add_charge(int i){
	return;
}

int Card::get_charge() {
    return -1;
}

bool Card::execute_trigger(unique_ptr<Player> &triggered_player, int triggered_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2){
	return false;
}

vector<card_template_t> Card::inspect(){
	vector<card_template_t> tmp;
	cerr << "Inspect only apply on minions" << endl;
	return tmp;
}

int Card::get_charge_cost() {
    return -1;
}

void Card::use_one_action(){

}






