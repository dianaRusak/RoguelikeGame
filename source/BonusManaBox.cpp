#include "../include/BonusManaBox.h"

BonusManaBox::BonusManaBox(int position_row, int position_col, char ident) {
    row_pos_ = position_row;
    col_pos_ = position_col;
    identifier = ident;
}

CollideResult BonusManaBox::Collide(Hero *_ci) {
    if (_ci->cur_mana_points_ + _ci->mana_damage_hero <= _ci->max_mana_points_) {
        _ci->cur_mana_points_ += _ci->mana_damage_hero;
        return MobDie;
    }
    return CannotMove;
}

CollideResult BonusManaBox::Collide(Dragon *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Collide(Wall *_ci) {
    return CannotMove;
}


CollideResult BonusManaBox::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult BonusManaBox::Collide(Zombie *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Collide(Princess *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Collide(Floor *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Collide(FireBall *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Collide(BonusManaBox *_ci) {
    return CannotMove;
}

CollideResult BonusManaBox::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;
}
