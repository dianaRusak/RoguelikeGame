#pragma once

#include <vector>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>

class MapGenerator {
public:

    void setSize(int rows, int cols);

    void initCanvas();

    void fillCanvas();

    void readTiles();

    void addActors();

    void saveMap(const std::string &);

    bool checkReach(int row_one, int col_one, int row_two, int col_two);

    const std::vector<std::vector<int>> getCanvas() const;

    const std::vector<std::string> getMap() const;

    std::vector<std::vector<int>> canvas_;
    std::vector<std::string> map_;
    std::vector<std::vector<std::string>> tiles_;
    int canvas_rows_ = 0, canvas_cols_ = 0, map_rows_ = 0, map_cols_ = 0, tile_rows_ = 0, tile_cols_ = 0;
};

