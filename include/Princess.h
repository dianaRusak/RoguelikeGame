#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Floor.h"
#include "Wall.h"
#include "Dragon.h"
#include "FireBall.h"
#include "BonusManaBox.h"

//#include "Config.h"

class Princess : public Actor {
public:

    Princess(int position_row,
             int position_col,
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
                       int dir) override;

};
