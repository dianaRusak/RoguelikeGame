#pragma once

#include <cstdio>
#include <ncurses.h>
#include <map>
//#include <bits/shared_ptr.h>
#include "Map.hpp"
#include "Actors.hpp"

#define KEY_ENT 10
#define KEY_ESC 27
#define MENU_SIZE 2
#define KEY_W 119
#define KEY_D 100
#define KEY_S 115
#define KEY_A 97

enum GameMode {
    MainMenu, InGame, EndGame
};

class GameManager {
public:
    void start();

    void MemoryFree();

    const std::string items[MENU_SIZE] = {
            "Start",
            "Exit",
    };

private:
    std::vector<Actor *> mobs_;
    bool stop_;
    Map map_;
    Actor *hero_, *princess_;
    int max_rows, max_cols, mode_, map_cols_, map_rows_;
    std::string endgameMessage_;
};


