#include <random>
#include "MapGenerator.h"

void MapGenerator::setSize(const int rows, const int cols) {
    this->canvas_.resize((unsigned long) rows);
    for (auto &row: this->canvas_) {
        row.resize((unsigned long) cols);
    }
    this->canvas_rows_ = rows;
    this->canvas_cols_ = cols;
}

//инициализирует канвас перед генерациней карты
void MapGenerator::initCanvas() {
    //TODO: add check if tiles are uploaded
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 7);

    for (int i = 0; i < this->canvas_rows_; ++i) {
        for (int j = 0; j < this->canvas_cols_; ++j) {
            this->canvas_[i][j] = 0;
        }
    }
    //using random to initialize canvas with different tile types (a - number of map tile)
    for (int i = 1; i < this->canvas_rows_ - 1; ++i) {
        for (int j = 1; j < this->canvas_cols_ - 1; ++j) {
            int a = dis(gen);
            while ((a == this->canvas_[i][j - 1]) or (a == this->canvas_[i - 1][j])) {
                a = dis(gen);
            }
            this->canvas_[i][j] = a;
        }
    }

}

const std::vector<std::vector<int>> MapGenerator::getCanvas() const {
    return this->canvas_;
}

//заполняем карту по количеству клеток на канвасе
void MapGenerator::fillCanvas() {

    this->map_rows_ = this->canvas_rows_ * tile_rows_;
    this->map_cols_ = this->canvas_cols_ * tile_cols_;

    this->map_.resize((unsigned long) this->canvas_rows_ * 5);
    for (auto &row: this->map_) {
        row.resize((unsigned long) this->canvas_cols_ * 5);
    }
    for (int k = 0; k < this->canvas_rows_; ++k)
        for (int h = 0; h < this->canvas_cols_; ++h)
            for (int i = 0; i < this->tile_rows_; ++i)
                for (int j = 0; j < this->tile_cols_; ++j)
                    this->map_[i + 5 * k][j + 5 * h] = this->tiles_[this->canvas_[k][h]][i % 5][j % 5];

}

//read tiles from template directory
void MapGenerator::readTiles() {

    this->tile_rows_ = 5;
    this->tile_cols_ = 5;

    std::ifstream tile_file;
    for (int i = 0; i < 8; ++i) {
        tile_file.open("/home/botinok/CLionProjects/testRogulike/map/template/tile_" + std::to_string(i) + ".txt");
        this->tiles_.emplace_back(std::vector<std::string>());
        for (int j = 0; j < 5; ++j) {
            std::string str;
            tile_file >> str;
            this->tiles_[this->tiles_.size() - 1].push_back(str);
        }
        tile_file.close();
    }
    tile_file.close();
}

const std::vector<std::string> MapGenerator::getMap() const {
    return this->map_;
}

void MapGenerator::addActors() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, this->map_rows_ - 2 * this->tile_rows_ - 1);
    std::uniform_int_distribution<> dis_y(0, this->map_cols_ - 2 * this->tile_cols_ - 1);

    std::uniform_int_distribution<> dis(0, 100);

    int hero_pos_row, hero_pos_col, princess_pos_row, princess_pos_col;

    do {
        hero_pos_row = dis_x(gen) + this->tile_rows_;
        hero_pos_col = dis_y(gen) + this->tile_cols_;
        princess_pos_col = dis_y(gen) + this->tile_cols_;
        princess_pos_row = dis_x(gen) + this->tile_rows_;
    } while (!checkReach(hero_pos_row, hero_pos_col, princess_pos_row, princess_pos_col));

    this->map_[hero_pos_row][hero_pos_col] = 'H';
    this->map_[princess_pos_row][princess_pos_col] = 'P';

    std::vector<char> actors_symbols(4);
    actors_symbols[0] = 'Z';
    actors_symbols[1] = 'D';
    actors_symbols[2] = 'v';
    actors_symbols[3] = '^';
    for (int i = 0; i < 4; ++i) {
        int generated = 0, amount = dis(gen) % 25 + 25;
        if (i == 1) {
            amount = dis(gen) % 2 + 3;
        }
        for (std::pair<int, int> pos = {dis_x(gen) + this->tile_rows_, dis_y(gen) + this->tile_cols_};
             generated < amount;
             pos = {dis_x(gen) + this->tile_rows_, dis_y(gen) + this->tile_cols_}) {
            if (this->map_[pos.first][pos.second] == '.') {
                this->map_[pos.first][pos.second] = actors_symbols[i];
            }
            ++generated;
        }
    }
}


///проверяет, есть ли путь из one в two, bfs ван лаф

bool MapGenerator::checkReach(int row_one, int col_one, int row_two, int col_two) {

    if ((this->map_[row_one][col_one] == '#') or (this->map_[row_two][col_two] == '#')) {
        return false;
    }

    std::vector<std::vector<bool>>
            visited(this->map_rows_, std::vector<bool>(this->map_cols_, false));
    std::queue<std::pair<int, int>> q;

    q.push(std::make_pair(row_one, col_one));
    visited[row_one][col_one] = true;

    while (!q.empty()) {
        std::pair<int, int> p = q.front();
        visited[p.first][p.second] = true;
        q.pop();
        if ((this->map_[p.first - 1][p.second] == '.') and (!visited[p.first - 1][p.second])) {
            if (this->map_[p.first - 1][p.second] == this->map_[row_two][col_two]) {
                visited[row_two][col_two] = true;
                break;
            }
            q.push({p.first - 1, p.second});
        }
        if ((this->map_[p.first + 1][p.second] == '.') and (!visited[p.first + 1][p.second])) {
            if (this->map_[p.first + 1][p.second] == this->map_[row_two][col_two]) {
                visited[row_two][col_two] = true;
                break;
            }
            q.push({p.first + 1, p.second});
        }
        if ((this->map_[p.first][p.second - 1] == '.') and (!visited[p.first][p.second - 1])) {
            if (this->map_[p.first][p.second - 1] == this->map_[row_two][col_two]) {
                visited[row_two][col_two] = true;
                break;
            }
            q.push({p.first, p.second - 1});
        }
        if ((this->map_[p.first][p.second + 1] == '.') and (!visited[p.first][p.second + 1])) {
            if (this->map_[p.first][p.second + 1] == this->map_[row_two][col_two]) {
                visited[row_two][col_two] = true;
                break;
            }
            q.push({p.first, p.second + 1});
        }
    }
    return (visited[row_one][col_one]) and (visited[row_two][col_two]);
}

void MapGenerator::saveMap(const std::string &path) {

    std::ofstream map_file;
    map_file.open(path);
    for (int i = 0; i < this->map_rows_; ++i) {
        map_file << this->map_[i] << std::endl;
    }
    map_file.close();
}