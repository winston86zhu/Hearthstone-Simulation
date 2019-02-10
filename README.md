Written in C++14

Overview:
The sorcery game is an instance of collectible card game, where the two plays collect cards from input and the command is issue and passed on terminal. As the game goes, the card will flow around different locations and the underlying data of cards might be altered by the player’s command in the game. At the end of the project, we tend to achieve the goal of having the requested data accurately and timely at any time during a game.

Run the main.cc function and do the following:

1. Input the Player names
2. Cin the card names 
3. Use the instruction for each player - attack. play. use . discard...
* Every player has 20 lives, 3 magic, 5 card slots
4. Use -help to pull the helper guidance.

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
