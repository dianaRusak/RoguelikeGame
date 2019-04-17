#include "../include/Princess.h"

Princess::Princess(int position_row,
                   int position_col,
                   char ident) {
    row_pos_ = position_row;
    col_pos_ = position_col;
    identifier = ident;
}

CollideResult Princess::Collide(Hero *_ci) {
    return _ci->Collide(this);
}

CollideResult Princess::Collide(Dragon *_ci) {
    return CannotMove;
}

CollideResult Princess::Collide(Wall *_ci) {
    return _ci->Collide(this);
}

CollideResult Princess::Collide(Zombie *_ci) {
    return CannotMove;
}

CollideResult Princess::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult Princess::Collide(Princess *_ci) {
    return CannotMove;
}

CollideResult Princess::Collide(Floor *_ci) {
    return CannotMove;
}

CollideResult Princess::Collide(BonusManaBox *_ci) {
    return _ci->Collide(this);
}

CollideResult Princess::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;
}

CollideResult Princess::Collide(BonusHealthBox *_ci) {
    return _ci->Collide(this);
}

CollideResult Princess::Collide(FireBall *_ci) {
    return _ci->Collide(this);
}
