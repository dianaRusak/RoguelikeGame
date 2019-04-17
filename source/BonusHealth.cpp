#include "../include/BonusHealthBox.h"

BonusHealthBox::BonusHealthBox(int position_row, int position_col, char ident) {
    row_pos_ = position_row;
    col_pos_ = position_col;
    identifier = ident;
}

CollideResult BonusHealthBox::Collide(Hero *_ci) {
    if (_ci->cur_health_points_ + _ci->hp_bonus_hero_ <= _ci->max_health_points_) {
        _ci->cur_health_points_ += _ci->hp_bonus_hero_;
        return BonusUsed;
    }
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(Dragon *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(Wall *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult BonusHealthBox::Collide(Zombie *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(Princess *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(Floor *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(FireBall *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(BonusManaBox *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Collide(BonusHealthBox *_ci) {
    return CannotMove;
}

CollideResult BonusHealthBox::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;
}