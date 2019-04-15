#pragma once

#include "Actors.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

#include "include/Hero.h"
#include "include/Wall.h"
#include "include/Floor.h"
#include "include/Zombie.h"
#include "include/Dragon.h"
#include "include/Princess.h"

class Map {
public:
    std::vector<std::vector<Actor *>> v; //mobs_, hero_, map_cols_, max_rows
    void
    Load(std::vector<Actor *> &mobs_, Actor *&hero_, Actor *&princess_, int &map_cols_, int &map_rows_) {
        std::string buff;
        map_rows_ = 0;
        std::ifstream fin("map.txt"); // открыли файл для чтения
        Actor *new_actor = nullptr;
        while (!fin.eof()) {
            fin >> buff;
            std::vector<Actor *> mapAct;
            for (int i = 0; i < buff.length(); i++) {
                switch (buff[i]) {
                    case '#': {
                        new_actor = (Actor *) new Wall(map_rows_, i);
                        mapAct.push_back(new_actor);
                        break;
                    }
                    case 'P': {
                        princess_ = (Actor *) new Princess(map_rows_, i);
                        mapAct.push_back(princess_);
                        break;
                    }
                    case 'D': {
                        new_actor = (Actor *) new Dragon(map_rows_, i);
                        mapAct.push_back(new_actor);
                        mobs_.push_back(new_actor);
                        break;
                    }
                    case 'Z': {
                        new_actor = (Actor *) new Zombie(map_rows_, i);
                        mapAct.push_back(new_actor);
                        mobs_.push_back(new_actor);
                        break;
                    }
                    case 'H': {
                        hero_ = (Actor *) new Hero(map_rows_, i);
                        mapAct.push_back(hero_);
                        break;
                    }
                    case '.': {
                        new_actor = (Actor *) new Floor(map_rows_, i);
                        mapAct.push_back(new_actor);
                        break;
                    }
                }
            }
            map_cols_ = static_cast<int> (buff.length());
            v.push_back(mapAct);
            map_rows_++;
        }
        fin.close();
    }

    std::vector<Actor *> getArea(int row_pos, int col_pos) {
        std::vector<Actor *> f;
        f.push_back(v[row_pos - 1][col_pos]);
        f.push_back(v[row_pos][col_pos + 1]);
        f.push_back(v[row_pos + 1][col_pos]);
        f.push_back(v[row_pos][col_pos - 1]);
        return f;
    }

    void moveActor(int row_pos_, int col_pos_,
                   int row_pos2,
                   int col_pos2) {
        v[row_pos_][col_pos_]->row_pos_ = row_pos2;
        v[row_pos_][col_pos_]->col_pos_ = col_pos2;
        std::swap(v[row_pos_][col_pos_], v[row_pos2][col_pos2]);
    }

    Actor *CreateFireball(int row, int col, int dir) {
        std::map<int, std::pair<int, int>> position({
                                                            {0, {-1, 0}},
                                                            {1, {0,  1}},
                                                            {2, {1,  0}},
                                                            {3, {0,  -1}},
                                                    });

        if (v[row + position[dir].first][col + position[dir].second]->GetIdent() != '.') {
            return nullptr;
        }

        Actor *a = new FireBall(row + position[dir].first, col + position[dir].second, dir);
        delete v[row + position[dir].first][col + position[dir].second];
        v[row + position[dir].first][col + position[dir].second] = a;
        return a;
    }

    void DeleteActor(int row, int col) {
        delete v[row][col];
        v[row][col] = new Floor(row, col);
    }
};

