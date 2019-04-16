#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Floor.h"
#include "Princess.h"
#include "Wall.h"
#include "Dragon.h"
#include "BonusManaBox.h"

//#include "Config.h"

class FireBall : public Actor {
public:

    FireBall(int position_row,
             int position_col,
             int direction,
             int damage,
             int ident);

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
                       int dir) override;

    int dir_;
    int damage_;
};
