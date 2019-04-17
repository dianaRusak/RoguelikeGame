#include "../include/Wall.h"

Wall::Wall(int position_row,
           int position_col,
           char ident) {
    row_pos_ = position_row;
    col_pos_ = position_col;
    identifier = ident;
}


CollideResult Wall::Collide(Hero *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(Dragon *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(Wall *_ci) {
    return CannotMove;
}

CollideResult Wall::Collide(Actor *_ci) {
    return CannotMove;
}

CollideResult Wall::Collide(Zombie *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(Princess *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(Floor *_ci) {
    return CannotMove;
}


CollideResult Wall::Collide(FireBall *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(BonusManaBox *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Collide(BonusHealthBox *_ci) {
    return _ci->Collide(this);
}

CollideResult Wall::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;
}
