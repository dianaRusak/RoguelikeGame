#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "Config.h"


//предварительное объявление-это объявление идентификатора, для которого ещё неt полного определения
// Объявление идентификатора требуется компилятору для того, чтобы знать тип идентификатора

class Dragon;

class BonusManaBox;

class FireBall;

class Hero;

class Actor;

class Wall;

class Zombie;

class Princess;

class Floor;

enum CollideResult {
    CanMoveUp = 0, CanMoveRigth, CanMoveDown, CanMoveLeft, GameOver, Victory, CannotMove, MobDie, CanMove
};

class Actor {
public:
    int max_health_points_;
    int cur_health_points_;
    int cur_score_points_;
    int cur_mana_points_;
    int row_pos_;
    int col_pos_;

    virtual CollideResult Move(std::vector<Actor *>, int dir = 0) = 0;

    virtual CollideResult Collide(Hero *) = 0;

    virtual CollideResult Collide(Wall *) = 0;

    virtual CollideResult Collide(Dragon *) = 0;

    virtual CollideResult Collide(Zombie *) = 0;

    virtual CollideResult Collide(Actor *) = 0;

    virtual CollideResult Collide(Princess *) = 0;

    virtual CollideResult Collide(Floor *) = 0;

    virtual CollideResult Collide(FireBall *) = 0;

    virtual CollideResult Collide(BonusManaBox *) = 0;

    char GetIdent() {
        return identifier;
    };

    virtual ~Actor() = default;

protected:
    char identifier = ' ';
};


