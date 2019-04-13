#include "../include/Hero.h"

CollideResult Hero::Collide(Actor *_co) {
    return _co->Collide(this);
}

// Две реализации взаимодействия
CollideResult Hero::Collide(Hero *_ci) {
    return GameOver;
}

CollideResult Hero::Collide(Dragon *_ci) {
    this->cur_health_points_ -= _ci->damage_;
    if (this->cur_health_points_ > 0) {
        _ci->cur_health_points_ -= this->damage_;
        if (_ci->cur_health_points_ > 0) {
            return CannotMove;
        } else {
            return MobDie;
        }
    }
    return GameOver;
}

CollideResult Hero::Collide(Wall *_ci) {
    return CannotMove;
}

CollideResult Hero::Collide(Floor *_ci) {
    return CanMove;
}

CollideResult Hero::Collide(Zombie *_ci) {
    this->cur_health_points_ -= _ci->damage_;
    if (this->cur_health_points_ > 0) {
        _ci->cur_health_points_ -= this->damage_;
        if (_ci->cur_health_points_ > 0) {
            return CannotMove;
        } else {
            return MobDie;
        }
    }
    return GameOver;
}

CollideResult Hero::Collide(Princess *_ci) {
    return Victory;
}

CollideResult Hero::Move(std::vector<Actor *> v, int dir) {
    CollideResult k = Collide(v[dir]);
    if (k == CanMove) {
        switch (dir) {
            case 0:
                return CanMoveUp;
            case 1:
                return CanMoveRigth;
            case 2:
                return CanMoveDown;
            case 3:
                return CanMoveLeft;

        }
    }
    return k;
}
