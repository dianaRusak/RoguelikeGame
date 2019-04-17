#pragma once

#include "Actors.hpp"
#include "Zombie.h"
#include "Floor.h"
#include "Princess.h"
#include "Wall.h"
#include "Dragon.h"
#include "FireBall.h"
#include "BonusManaBox.h"
#include "BonusHealthBox.h"

class Hero : public Actor {
public:

    Hero(int position_row,
         int position_col,
         int max_health,
         int cur_health,
         int damage,
         int max_mana,
         int cur_mana,
         int score,
         char ident,
         int mana_damage_hero,
         int hp_bonus_hero);

    CollideResult Move(std::vector<Actor *>, int dir) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Collide(FireBall *) override;

    CollideResult Collide(BonusManaBox *) override;

    CollideResult Collide(BonusHealthBox *) override;

    int cur_score_points_;
    int max_mana_points_;
    int cur_mana_points_;
    int damage_;
    int mana_damage_hero;
    int hp_bonus_hero_;
};
