#include "../include/Zombie.h"

Zombie::Zombie(int position_row,
               int position_col,
               int max_health,
               int cur_health,
               int damage,
               int max_mana,
               int cur_mana) {
    row_pos_ = position_row;
    col_pos_ = position_col;
    max_health_points_ = max_health;
    cur_health_points_ = cur_health;
    damage_ = damage;
    max_mana_points_ = max_mana;
    cur_mana_points_ = cur_mana;
    identifier = 'Z';
}

CollideResult Zombie::Collide(Hero *_ci) {
    return _ci->Collide(this);
}

CollideResult Zombie::Collide(Floor *_ci) {
    return CanMove;
}

CollideResult Zombie::Collide(Dragon *_ci) {
    return _ci->Collide(this);
}

CollideResult Zombie::Collide(Wall *_ci) {
    return CannotMove;
}

CollideResult Zombie::Collide(Zombie *_ci) {
    return CannotMove;
}

CollideResult Zombie::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult Zombie::Collide(Princess *_ci) {
    return _ci->Collide(this);
}


CollideResult Zombie::Collide(FireBall *_ci) {
    return _ci->Collide(this);
}

CollideResult Zombie::Move(std::vector<Actor *> v, int dir) {
    dir = rand() % 4;
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
            default:
                return CannotMove;
        }
    }
    return k;
}

