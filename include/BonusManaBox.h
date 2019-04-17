#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Floor.h"
#include "Princess.h"
#include "Wall.h"
#include "Dragon.h"
#include "FireBall.h"

class BonusManaBox : public Actor {
public:

    BonusManaBox(int position_row,
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

    CollideResult Move(std::vector<Actor *> v, int dir);

};
