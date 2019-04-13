#include "../include/Floor.h"

Floor::Floor(int position_row, int position_col) {
    row_pos_ = position_row; //  TODO initializer list
    col_pos_ = position_col;
    identifier = '.';
}

CollideResult Floor::Collide(Hero *_ci) {
    return _ci->Collide(this);
}

CollideResult Floor::Collide(Dragon *_ci) {
    return _ci->Collide(this);
}

CollideResult Floor::Collide(Wall *_ci) {
    return _ci->Collide(this);
}


CollideResult Floor::Collide(Actor *_ci) {
    return _ci->Collide(this);
}

CollideResult Floor::Collide(Zombie *_ci) {
    return _ci->Collide(this);
}

CollideResult Floor::Collide(Princess *_ci) {
    return _ci->Collide(this);
}

CollideResult Floor::Collide(Floor *_ci) {
    return CannotMove;
}

CollideResult Floor::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;//return Victory;
}
