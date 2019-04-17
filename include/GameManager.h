#pragma once

#include <cstdio>
#include <ncurses.h>
#include <map>
//#include <bits/shared_ptr.h>
#include "Map.hpp"
#include "Actors.hpp"
//#include "Config.h"
#define  KEY_ESC 27
#define  KEY_ENT 10
#define  MENU_SIZE 2
#define  KEY_W 119
#define  KEY_D 100
#define  KEY_S 115
#define  KEY_A 97

enum GameMode {
    MainMenu, InGame, EndGame
};

class GameManager {
public:
    void start();

    void MemoryFree();

    void CreateMenu();

    void InitGM();

    void ExitGM();

    void HeroCentralization();

    void MapDrawing();

    void GameHero(int sym);

    void FireballAttackHero(int sym);

    void HeroStep(int sym);

    void FireballAttackDragon(int sym, Actor *mob);

    void MobStep(int sym, Actor *mob);

    const std::string items[MENU_SIZE] = {
            "Start",
            "Exit",
    };

private:
    std::vector<Actor *> mobs_;
    bool stop_;
    Map map_;
    int RechargeTimer = 1;
    Hero *hero_;
    Actor *princess_;
    int max_rows, max_cols, mode_, map_cols_, map_rows_;
    std::string endgameMessage_;
    Config config;
    int mid_rows, mid_cols;
    CollideResult moveResult;
    unsigned choice;
    int hero_row, hero_col, top_row_bound, bottom_row_bound, left_col_bound, right_col_bound;
    std::map<int, int> mp{
            {KEY_UP,    0},
            {KEY_RIGHT, 1},
            {KEY_DOWN,  2},
            {KEY_LEFT,  3},
            {KEY_W,     4},
            {KEY_D,     5},
            {KEY_S,     6},
            {KEY_A,     7},

    };
    std::map<CollideResult, std::pair<int, int>> mvDir{
            {CanMoveUp,    {-1, 0}},
            {CanMoveRigth, {0,  1}},
            {CanMoveDown,  {1,  0}},
            {CanMoveLeft,  {0,  -1}},
            {CannotMove,   {0,  0}},
            {MobDie,       {0,  0}},
    };
};
