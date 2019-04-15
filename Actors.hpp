#pragma once

#include <string>
#include <vector>
#include <iostream>
//#include <bits/shared_ptr.h>


//предварительное объявление-это объявление идентификатора, для которого ещё неt полного определения
// Объявление идентификатора требуется компилятору для того, чтобы знать тип идентификатора

class Dragon;

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
    int max_health_points_ = 0;
    int cur_health_points_ = 0;
    int row_pos_ = 0;
    int col_pos_ = 0;

    virtual CollideResult Move(std::vector<Actor *>, int dir = 0) = 0;

    virtual CollideResult Collide(Hero *) = 0;

    virtual CollideResult Collide(Wall *) = 0;

    virtual CollideResult Collide(Dragon *) = 0;

    virtual CollideResult Collide(Zombie *) = 0;

    virtual CollideResult Collide(Actor *) = 0;

    virtual CollideResult Collide(Princess *) = 0;

    virtual CollideResult Collide(Floor *) = 0;

    virtual CollideResult Collide(FireBall *) = 0;

    char GetIdent() {
        return identifier;
    };

    virtual ~Actor() = default;

//    virtual Actor* findActor(std::vector<Actor*> act, std::pair<int, int> dir = {-1, -1}) = 0;

protected:
    char identifier = ' ';
};


