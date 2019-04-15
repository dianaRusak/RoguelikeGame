#include "../include/FireBall.h"

FireBall::FireBall(int position_row, int position_col, int direction, int damage) {
    row_pos_ = position_row; //  TODO initializer list
    col_pos_ = position_col;
    dir_ = direction;
    damage_ = damage;
    identifier = '@';
}

CollideResult FireBall::Collide(Hero *_ci) {
    _ci->cur_health_points_ -= this->damage_;
//    _ci->cur_score_points_ -= FireHero;
    return _ci->cur_health_points_ <= 0 ? GameOver : CannotMove;
}

CollideResult FireBall::Collide(Dragon *_ci) {
    _ci->cur_health_points_ -= this->damage_;
    return _ci->cur_health_points_ <= 0 ? MobDie : CannotMove;
}

CollideResult FireBall::Collide(Wall *_ci) {
    return CannotMove; ////хзхзхзхзхз, его же надо убирать
}


CollideResult FireBall::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult FireBall::Collide(Zombie *_ci) {
    _ci->cur_health_points_ -= this->damage_;
    return _ci->cur_health_points_ <= 0 ? MobDie : CannotMove;
}

CollideResult FireBall::Collide(Princess *_ci) {
    return CannotMove;
}

CollideResult FireBall::Collide(FireBall *) {
    return CannotMove;
}

CollideResult FireBall::Collide(Floor *_ci) {
    return CanMove;
}

CollideResult FireBall::Move(std::vector<Actor *> v, int dir) {
    CollideResult k = Collide(v[dir_]);
    if (k == CanMove) {
        switch (dir_) {
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
