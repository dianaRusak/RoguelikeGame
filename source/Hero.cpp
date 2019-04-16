#include "../include/Hero.h"

Hero::Hero(int position_row, int position_col, int max_health, int cur_health, int damage, int max_mana, int cur_mana,
           int score, char ident, int mana) {
    cur_score_points_ = score;
    max_mana_points_ = max_mana;
    cur_mana_points_ = cur_mana;
    row_pos_ = position_row;
    col_pos_ = position_col;
    damage_ = damage;
    max_health_points_ = max_health;
    cur_health_points_ = cur_health;
    identifier = ident;
    mana_damage_hero = mana;
}

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
            this->cur_score_points_ += _ci->score_kill_D;
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

CollideResult Hero::Collide(BonusManaBox *_ci) {
    return _ci->Collide(this);
}

CollideResult Hero::Collide(Zombie *_ci) {
    this->cur_health_points_ -= _ci->damage_;
    if (this->cur_health_points_ > 0) {
        _ci->cur_health_points_ -= this->damage_;
        if (_ci->cur_health_points_ > 0) {
            return CannotMove;
        } else {
            this->cur_score_points_ += _ci->score_kill_Z;
            return MobDie;
        }
    }
    return GameOver;
}

CollideResult Hero::Collide(FireBall *_ci) {
    return _ci->Collide(this);
}

CollideResult Hero::Collide(Princess *) {
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
