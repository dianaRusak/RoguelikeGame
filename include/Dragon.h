#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Floor.h"
#include "Princess.h"
#include "Wall.h"
#include "FireBall.h"
#include "BonusManaBox.h"
#include "BonusHealthBox.h"

class Dragon : public Actor {
public:

    Dragon(int position_row,
           int position_col,
           int max_health,
           int cur_health,
           int damage,
           int max_mana,
           int cur_mana,
           int score,
           char ident);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Collide(FireBall *) override;

    CollideResult Collide(BonusManaBox *) override;

    CollideResult Collide(BonusHealthBox *) override;

    CollideResult Move(std::vector<Actor *>, int dir = 0) override;

    int max_mana_points_;
    int damage_;
    int cur_mana_points_;
    int score_kill_D;
};
