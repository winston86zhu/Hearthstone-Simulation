#include <iostream>
#include <memory>
#include <sstream>
#include <fstream>
#include <string>

#include "Card.h"
#include "Minion.h"
#include "Earthelemental.h"
#include "Airelemental.h"
#include "AuraOfPower.h"
#include "Enchantment.h"
#include "Giantstrength.h"
#include "Enrage.h"
#include "Haste.h"
#include "MagicFatigue.h"
#include "Silence.h"
#include "Customized.h"
#include "Canvas.h"

using namespace std;

void game_start(bool test_mode, bool init_mode, string file_name, string deck_1_name, string deck_2_name) {
    std::streambuf *cinbuf;
    std::ifstream in;

    if(init_mode){
        in.open (file_name, std::ifstream::in);
        cinbuf = std::cin.rdbuf(); //save old buf
        std::cin.rdbuf(in.rdbuf());
    }

    ifstream deck_player_1(deck_1_name);
    ifstream deck_player_2(deck_2_name);

    string p1_name;
    string p2_name;
    
    cout << "Please enter Player 1's Name: " << endl;
    cin >> p1_name;
    unique_ptr<Player> p1 = make_unique<Player>(p1_name, deck_player_1);
    cout << "Please enter Player 2's Name: " << endl;
    cin >> p2_name;
    unique_ptr<Player> p2 = make_unique<Player>(p2_name, deck_player_2);
    unique_ptr<Canvas> canvas = make_unique<Canvas>(move(p1), move(p2));

    string read_line;
    getline(cin, read_line);

    int current_player =1;
    int non_current = 2;

    unique_ptr<Player>& active = canvas->get_p1();
    unique_ptr<Player>& inactive = canvas->get_p2();

    if(!test_mode){
        active->get_deck()->shuffle();
        inactive->get_deck()->shuffle();
    }

    for(int i = 0; i < 4; ++i){
        active->draw();
        inactive->draw();
    }
    active->round_start(active, inactive,current_player);
    while (true) {
        if (!getline(cin, read_line)) {
            std::cin.rdbuf(cinbuf);
            continue;
        }
        istringstream iss{read_line};
        iss >> read_line;
        if (read_line == "quit") {
            cout << "Quiting the Game - Goodbye" << endl;
            break;
        } else if (read_line == "end") {
            cout << "Player " << active->get_name() << " 's turn is over. Now switch to " << inactive->get_name()
                 << " 's turn" << endl;
            active->round_end(active, inactive,current_player);
            active.swap(inactive);
            cout << "This is the start of " << active->get_name() << "'s turn" << endl;
            swap(current_player,non_current);
            active->round_start(active, inactive,current_player); // magic++  & start-trigger
            continue;
        } else if (read_line == "draw") {
            if (test_mode) {
                active->draw();
            } else {
                cerr << "draw error - Draw could only be performed in testing mode" << endl;
            }
        } else if (read_line == "discard") {
            int dis_index;
            if (test_mode) {
                if(!(iss >> dis_index)){
                    cerr << "discard error - Specify the card you want to discard" << endl;
                    continue;
                }
                
                active->discard(dis_index);
            } else {
                cerr << "discard error - Draw could only be performed in testing mode" << endl;
            }
        } else if (read_line == "attack") { // attack the opponent
            int my_minion;
            int attack_target;
            if(!(iss >> my_minion)){
                cerr << "attack error - specify a minion to attack" << endl;
                continue;
            }

            if (my_minion < 1 || my_minion > 5) {
                cerr << "attack error - minion index ranges from 1 to 5" << endl;
            }
            auto &card_ptr = active->get_ground()->get_ith(static_cast<unsigned long>(my_minion) - 1);
            if (iss >> attack_target) { // attack minion
                if (attack_target < 1 || attack_target > 5) {
                    cerr << "attack error - minion index ranges from 1 to 5" << endl;
                    continue;
                }
                card_ptr->attack_minion(active, my_minion - 1, inactive, attack_target - 1);
            } else { // attack on the opposite player
                iss.clear();
                card_ptr->attack_player(active, my_minion - 1, inactive);
            }
        } else if (read_line == "play") {
            int play_i;
            if(!(iss >> play_i)){
                cerr << "play error - specify a card to play" << endl;
                continue;
            }

            if (play_i < 1 || play_i > 5) {
                cerr << "play error - minion index ranges from 1 to 5" << endl;
                continue;
            } else if (play_i > active->get_hand()->get_size()) {
                cerr << "play error - index exceeds number of cards in hand" << endl;
                continue;
            }
            if(!test_mode) {
                if (active->get_magic() < active->get_hand()->get_ith(play_i - 1)->get_cost()) {
                    cerr << "play error -" << active->get_name() + " does not have enought magic to play " +
                                              active->get_hand()->get_ith(play_i - 1)->get_name() << endl;
                    continue;
                }
            }
            active->play(play_i - 1, active, inactive, iss, current_player);
        } else if (read_line == "inspect") {
            int inspect_index;
            if(!(iss >> inspect_index)){
                cerr << "inspect error - Please specify a target" << endl;
                continue;
            }

            if (inspect_index < 1 || inspect_index > active->get_ground()->get_size()) {
                cerr << "inspect error - minion index not in range" << endl;
                continue;
            }
            auto tmp = active->get_ground()->get_ith(inspect_index - 1)->inspect();
            // print the inspected_minion vector card_template_t

            int vec_size = tmp.size();
            for(int i = 0; i < (int)tmp[0].size(); ++i){
                cout << tmp[0][i];
                cout << endl;
            }
            //print out the rows with five enchantments
            int full_rows = (vec_size - 1) / 5;
            for(int rows = 0; rows < full_rows; ++rows){
                for(int i = 0; i < (int)tmp[0].size(); ++i){
                    for(int j = 1 + rows * 5; j < 1 + rows * 5 + 5; ++j){
                        cout << tmp[j][i];
                    }
                    cout << endl;
                }
            }
            // do the remaining enchantments
            if(1 + full_rows * 5 < vec_size){
                for(int i = 0; i < (int)tmp[0].size(); ++i){
                    for(int j = 1 + full_rows * 5; j < vec_size; ++j){
                        cout << tmp[j][i];
                    }
                    cout << endl;
                }
            }

        } else if (read_line == "hand") {
            cout << "hand" << endl;
            active->showhand();
        } else if (read_line == "board") {
            canvas->printcanvas(current_player);
        } else if (read_line == "use") {
            int use_i;
            if(!(iss >> use_i)){
                cerr << "use error - specify a minion to use" << endl;
                continue;
            }

            if (use_i < 1 || use_i > 5) {
                cerr << "use error - minion index ranges from 1 to 5" << endl;
                continue;
            }
            active->use(use_i - 1, active, inactive, iss, current_player);
        } else if (read_line == "help"){
            cout << "Commands: " << "help -- Display this message." << endl;
            cout << "          end -- End the current player's turn." << endl;
            cout << "          quit -- End the game." << endl;
            cout << "          attack minion other-minion -- Orders minion to attack other-minion." << endl;
            cout << "          attack minion -- Orders minion to attack the opponent." << endl;
            cout << "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
            cout << "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player." << endl;
            cout << "          inspect minion -- View a minion's card and all enchantments on that minion." << endl;
            cout << "          hand -- Describe all cards in your hand." << endl;
            cout << "          board -- Describe all cards on the board." << endl;
        } else if (read_line == ""){
            continue;
        } else {
            cerr << "Command Error - This is an invalid command" << endl;
        }
        // Check Dead Minion
        vector<int> dead_list;
        int dummy = 0;
        for(auto& card : active->get_ground()->get_cardvec()) {
            if(card->get_defense() <= 0) {
                dead_list.emplace_back(dummy);
            }
            dummy++;
        }

        
        for(int i = 0, deleted_minion = 0; i < (int)dead_list.size(); ++i, ++deleted_minion){
            int index = dead_list[i] - deleted_minion;
            cout << "active main.cc index = " << index << endl;
            Card * tmp = active->get_ground()->get_ith(index).get();
            active->get_ground()->ExitMinion(active->get_ground()->get_ith(index), active, inactive, current_player);
            active->minion_dead(index);
            
            active->get_ground()->dettach_all(tmp);
            inactive->get_ground()->dettach_all(tmp);
        }

        dead_list.clear();
        dummy = 0;
        for(auto& card : inactive->get_ground()->get_cardvec()) {
            if(card->get_defense() <= 0) {
                dead_list.emplace_back(dummy);
                cout << "main dummy = " << dummy << endl;
            }
            dummy++;
        }
        for(int i = 0, deleted_minion = 0; i < (int)dead_list.size(); ++i, ++deleted_minion){
            int index = dead_list[i] - deleted_minion;
            cout << "inactive main.cc index = " << index << endl;
            Card * tmp = inactive->get_ground()->get_ith(index).get();
            inactive->get_ground()->ExitMinion(inactive->get_ground()->get_ith(index), active, inactive, current_player);
            inactive->minion_dead(index);
            active->get_ground()->dettach_all(tmp);
            inactive->get_ground()->dettach_all(tmp);
        }
        // Check if the player is still alive
        if (inactive->get_life() <= 0) {
            cout << active->get_name() << " wins the game!!!!!" << endl;
            break;
        }
        if (active->get_life() <= 0) {
            cout << inactive->get_name() << " wins the game!!!!!" << endl;
            break;
        }
    }
}

int main (int argc, char *argv[]) {
    bool test_mode = false;
    bool init_mode = false;
    string deck1_name = "default.deck";
    string deck2_name = "default.deck";
    string file_name;

    for (int i = 1; i < argc; i++) {
        string theArg = argv[i];
        if (theArg == "-deck1") {
            deck1_name = argv[i + 1];
        } else if (theArg == "-deck2") {
            deck2_name = argv[i + 1];
        } else if (theArg == "-testing") {
            test_mode = true;
        } else if (theArg == "-init") {
            init_mode = true;
            file_name = argv[i + 1];
        }
    }
    game_start(test_mode, init_mode, file_name, deck1_name, deck2_name);
    return 0;
}

