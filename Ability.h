#ifndef SORCERY_ABILITY_H
#define SORCERY_ABILITY_H
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

using namespace std;

#define DBG false

class Player;
class Card;
class Minion;
class Ritual;

class Ability {
protected:
    string description;
public:
    Ability(string description);
    virtual ~Ability();
    string get_description();
    virtual int get_activation_cost();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) = 0;
};


class Triggered_Ability: public Ability{
public:
    Triggered_Ability(string description);
};

class Activated_Ability: public Ability{
    int activation_cost;
public:
    Activated_Ability(string description, int action_cost);
    int get_activation_cost() override;
};

// Three Minion's activation ability ==========
class NovicePyromancerActv: public Activated_Ability{
public:
    NovicePyromancerActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class ApprenticeSummonerActv: public Activated_Ability{
public:
    ApprenticeSummonerActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class MasterSummonerActv: public Activated_Ability{
public:
    MasterSummonerActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
// ============================================

// Six Spell activation ability ===============
class NukeAbv: public Activated_Ability{
public:
    NukeAbv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};



class BanishActv: public Activated_Ability{
public:
    BanishActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class UnsummonActv: public Activated_Ability{
public:
    UnsummonActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class RechargeActv: public Activated_Ability{
public:
    RechargeActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class DisenchantActv: public Activated_Ability{
public:
    DisenchantActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class RaiseDeadActv: public Activated_Ability{
public:
    RaiseDeadActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

class BlizzardActv: public Activated_Ability{
public:
    BlizzardActv();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
// ============================================

// Trigger abilities ===============
class BoneGolemTrig: public Triggered_Ability{
public:
    BoneGolemTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
class FireElementalTrig: public Triggered_Ability{
public:
    FireElementalTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
class PotionSellerTrig: public Triggered_Ability{
public:
    PotionSellerTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
class DarkRitualTrig: public Triggered_Ability{
public:
    DarkRitualTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
class AuraOfPowerTrig: public Triggered_Ability{
public:
    AuraOfPowerTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};
class StandstillTrig: public Triggered_Ability{
public:
    StandstillTrig();
    virtual bool execute(unique_ptr<Player> &using_player, int using_minion, unique_ptr<Player> &target_player, int target_minion, unique_ptr<Player> &player1, unique_ptr<Player> &player2) override;
};

// ============================================

#endif //SORCERY_ABILITY_H
