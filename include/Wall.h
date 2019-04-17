#pragma once

#include "Actors.hpp"
#include "Hero.h"
#include "Zombie.h"
#include "Floor.h"
#include "Princess.h"
#include "Dragon.h"
#include "FireBall.h"
#include "BonusManaBox.h"
#include "BonusHealthBox.h"

class Wall : public Actor {
public:

    Wall(int position_row,
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

    CollideResult Collide(BonusHealthBox *) override;

    CollideResult Move(std::vector<Actor *>,
                       int dir) override;
};
