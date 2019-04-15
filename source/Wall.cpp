#include "../include/Wall.h"

Wall::Wall(int position_row, int position_col) {
    row_pos_ = position_row; //  TODO initializer list
    col_pos_ = position_col;
    identifier = '#';
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

CollideResult Wall::Move(std::vector<Actor *> v, int dir) {
    return CannotMove;
}

//Actor *Wall::findActor(std::vector<Actor *> act, std::pair<int, int> dir) {
//    std::pair<int, int> kek = {-1, -1};
//    if (dir == kek){
//        //random выбираем направление условно хочу наверх, лево-0, верх 1, и тд
//        return act[1];
//    }else{
//        //вернем - наверх 0,-1 . направо 1,0 . вниз 0,1 . налево -1,0 и возвращаем аналогично , условно передали 0,-1, хотим вверх
//        return act[1];
//    }
//}
