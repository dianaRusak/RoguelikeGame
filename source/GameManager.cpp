#include <linux/input-event-codes.h>
#include "ncurses.h"
#include "../include/GameManager.h"

void GameManager::start() {
    config.conRead();
    clear();
    initscr();
    InitGM();
    while (!stop_) {
        switch (mode_) {
            case MainMenu: {
                clear();
                CreateMenu(mid_rows, mid_cols, choice);
                break;
                }

            case EndGame: {
                clear();
                mvaddstr(mid_rows, mid_cols - endgameMessage_.length() / 2, endgameMessage_.c_str());
                map_rows_ = 0;
                map_cols_ = 0;
                mobs_.clear();
                switch (getch()) {
                    case KEY_ENT:
                    case KEY_ESC: {
                        mode_ = MainMenu;
                        break;
                    }
                }
                break;
            }

            case InGame: {
                getmaxyx(stdscr, max_rows, max_cols);
                mid_rows = max_rows / 2;
                mid_cols = max_cols / 2;

                for (int row = 0; row <= max_rows; ++row) {
                    for (int col = 0; col <= max_cols; ++col) {
                        mvaddch(row, col, ' ');
                    }
                }
                mvaddch(mid_rows, mid_cols, map_.v[hero_->row_pos_][hero_->col_pos_]->GetIdent());
                int hero_row = hero_->row_pos_;
                int hero_col = hero_->col_pos_;

                int top_row_bound = hero_row - std::min<int>(max_rows, hero_row);
                int bottom_row_bound = hero_row + std::min<int>(max_rows, map_rows_ - hero_row - 1);
                int left_col_bound = hero_col - std::min<int>(max_cols, hero_col);
                int right_col_bound = hero_col + std::min(max_cols, map_cols_ - hero_col - 1);


                for (int row = top_row_bound; row < bottom_row_bound; ++row) {
                    for (int col = left_col_bound; col <= right_col_bound; ++col) {
                        mvaddch(mid_rows - hero_row + row,
                                mid_cols - hero_col + col,
                                map_.v[row][col]->GetIdent());
                    }
                }

                mvwprintw(stdscr, 0, 0, "%s %d ", "Health", hero_->cur_health_points_);
                mvwprintw(stdscr, 1, 0, "%s %d ", "Points", hero_->cur_score_points_);
                mvwprintw(stdscr, 2, 0, "%s %d ", "Mana", hero_->cur_mana_points_);

                std::map<int, int> mp({ // pair -> int
                                              {KEY_UP,    0},
                                              {KEY_RIGHT, 1},
                                              {KEY_DOWN,  2},
                                              {KEY_LEFT,  3},
                                              {KEY_W,     4},
                                              {KEY_D,     5},
                                              {KEY_S,     6},
                                              {KEY_A,     7},

                                      });
                std::map<CollideResult, std::pair<int, int>> mvDir({
                                                                           {CanMoveUp,    {-1, 0}},
                                                                           {CanMoveRigth, {0,  1}},
                                                                           {CanMoveDown,  {1,  0}},
                                                                           {CanMoveLeft,  {0,  -1}},
                                                                           {CannotMove,   {0,  0}},
                                                                           {MobDie,       {0,  0}},
                                                                   });
                auto sym = getch();
                if (sym == KEY_ESC) {
                    mode_ = MainMenu;
                    MemoryFree();
                } else {
                    switch (sym) {//Fireball
                        case KEY_W:
                        case KEY_D:
                        case KEY_S:
                        case KEY_A: {
                            if (hero_->cur_mana_points_ > 0) {
                                Actor *fireBall = map_.CreateFireball(hero_->row_pos_, hero_->col_pos_, mp[sym] % 4,
                                                                      config);
                                hero_->cur_mana_points_ -= config.mana_damage_hero;
                                if (fireBall != nullptr) {
                                    mobs_.push_back(fireBall);
                                }
                            }
                            break;
                        }
                        case KEY_UP:
                        case KEY_RIGHT:
                        case KEY_DOWN:
                        case KEY_LEFT: {
                            //others
                            CollideResult moveResult =
                                    hero_->Move(map_.getArea(hero_->row_pos_, hero_->col_pos_), mp[sym]);

                            switch (moveResult) {
                                case GameOver:
                                case Victory: {
                                    mode_ = EndGame;
                                    endgameMessage_ = moveResult == Victory ? "You win" : "You lose";
                                    MemoryFree();
                                    break;
                                }
                                case CannotMove:
                                case CanMoveUp:
                                case CanMoveRigth:
                                case CanMoveDown:
                                case CanMoveLeft: {
                                    map_.moveActor(hero_->row_pos_, hero_->col_pos_,
                                                   hero_->row_pos_ + mvDir[moveResult].first,
                                                   hero_->col_pos_ + mvDir[moveResult].second);
                                    break;
                                }
                                case MobDie: {
                                    moveResult = (CollideResult) mp[sym];
                                    Actor *actorToDelete = map_.v[hero_->row_pos_ + mvDir[moveResult].first]
                                    [hero_->col_pos_ + mvDir[moveResult].second];

                                    for (auto it = mobs_.begin(); it != mobs_.end(); ++it) {
                                        if ((*it)->row_pos_ == actorToDelete->row_pos_ &&
                                            (*it)->col_pos_ == actorToDelete->col_pos_) {
                                            mobs_.erase(it);
                                            break;
                                        }
                                    }
                                    map_.DeleteActor(actorToDelete->row_pos_, actorToDelete->col_pos_, config);
                                    break;
                                }
                            }
                            break;
                        }
                    }

                    if (mode_ == EndGame)
                        break;
                    for (int i = 0; i < mobs_.size(); ++i) {
                        auto mob = mobs_[i];
                        CollideResult moveResult2 = mob->Move(map_.getArea(mob->row_pos_, mob->col_pos_), mp[sym]);
                        switch (moveResult2) {
                            case GameOver:
                            case Victory: {
                                mode_ = EndGame;
                                endgameMessage_ = moveResult2 == Victory ? "You win" : "You lose";
                                MemoryFree();
                                break;
                            }
                            case CanMoveUp:
                            case CanMoveRigth:
                            case CanMoveLeft:
                            case CanMoveDown: {
                                map_.moveActor(mob->row_pos_, mob->col_pos_,
                                               mob->row_pos_ + mvDir[moveResult2].first,
                                               mob->col_pos_ + mvDir[moveResult2].second);
                                break;
                            }
                            case MobDie: {
                                if (mob->GetIdent() == '@') {
                                    //вытазили область и чувака который сдох
                                    Actor *actorToDelete =
                                            map_.getArea(mob->row_pos_, mob->col_pos_)[((FireBall *) mob)->dir_];
                                    //выкинули из массива трупак
                                    for (auto it = mobs_.begin(); it != mobs_.end(); ++it) {
                                        if ((*it)->row_pos_ == actorToDelete->row_pos_ &&
                                            (*it)->col_pos_ == actorToDelete->col_pos_) {
                                            mobs_.erase(it);
                                            break;
                                        }
                                    }
                                    //подчистили за ним
                                    map_.DeleteActor(actorToDelete->row_pos_, actorToDelete->col_pos_, config);
                                }

                                for (auto it = mobs_.begin(); it != mobs_.end(); ++it) {
                                    if ((*it)->row_pos_ == mob->row_pos_ &&
                                        (*it)->col_pos_ == mob->col_pos_) {
                                        mobs_.erase(it);
                                        break;
                                    }
                                }
                                map_.DeleteActor(mob->row_pos_, mob->col_pos_, config);
                                break;
                            }
                            case CannotMove: {
                                if (mob->GetIdent() == '@') {
                                    for (auto it = mobs_.begin(); it != mobs_.end(); ++it) {
                                        if ((*it)->row_pos_ == mob->row_pos_ &&
                                            (*it)->col_pos_ == mob->col_pos_) {
                                            mobs_.erase(it);
                                            break;
                                        }
                                    }
                                    map_.DeleteActor(mob->row_pos_, mob->col_pos_, config);
                                }
                                break;
                            }
                        }
                        if (mode_ == EndGame) {
                            break;
                        }
                    }
                    if (mode_ == EndGame) {
                        break;
                    }

                    break;
                }
            }
        }
    }
    endwin();
}


void GameManager::MemoryFree() {
    hero_ = nullptr;
    princess_ = nullptr;
    for (int row = 0; row < map_.v.size(); ++row) {
        for (int col = 0; col < map_.v[row].size(); ++col) {
            if (map_.v[row][col] != nullptr) {
                delete map_.v[row][col];
            }
        }
        map_.v[row].clear();
    }
    map_.v.clear();
}

void GameManager::CreateMenu(int mid_rows, int mid_cols, unsigned choice) {
    for (unsigned i = 0; i < MENU_SIZE; i++) //Проходим по всем элементам меню
    {
        move(mid_rows - 1 + i, mid_cols - 4);
        if (i == choice) {//Если текущий элемент совпадает с выбором пользователя
            move(mid_rows - 1 + i, mid_cols - 4 - 1);
            addch('>'); //Выводим указатель
        }
        printw("%s\n", items[i].c_str());
    }
    //Получаем нажатие пользователя
    switch (getch()) {
        case KEY_UP:
            if (choice) //Если возможно, переводим указатель вверх
                choice--;
            break;
        case KEY_DOWN:
            if (!choice) //Если возможно, переводим указатель вниз
                choice++;
            break;
        case KEY_ENT:
            if (choice) {
                stop_ = true;
            } else {
                map_.Load(mobs_, hero_, princess_, map_cols_, map_rows_, config);
                mode_ = InGame;
                clear();
            }
            break;
    }
}

void GameManager::InitGM() {
    stop_ = false;
    mode_ = MainMenu;
    choice = 0; //Выбор пользователя
    getmaxyx(stdscr, max_rows, max_cols);
    mid_rows = max_rows / 2;
    mid_cols = max_cols / 2;
    curs_set(0);
    keypad(stdscr, true);
}
