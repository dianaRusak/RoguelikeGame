#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Wall.h"
#include "Dragon.h"
#include "Princess.h"
#include "Floor.h"
#include "FireBall.h"
//#include "Config.h"

class Zombie : public Actor {
public:

    Zombie(
            int position_row,
            int position_col,
            int max_health,
            int cur_health,
            int damage,
            int score,
            char ident);

    CollideResult Collide(Hero *) override;

    CollideResult Collide(Dragon *) override;

    CollideResult Collide(Wall *) override;

    CollideResult Collide(Zombie *) override;

    CollideResult Collide(Actor *) override;

    CollideResult Collide(Princess *) override;

    CollideResult Collide(Floor *) override;

    CollideResult Collide(FireBall *) override;

    CollideResult Collide(BonusManaBox *) override;

    CollideResult Move(std::vector<Actor *>,
                       int dir = 0) override;

    int damage_;
    int score_kill_Z;
};

