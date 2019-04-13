#include "ncurses.h"
#include "GameManager.h"

void GameManager::start() {
    stop_ = false;
    mode_ = MainMenu;
    clear();
    initscr();
    unsigned choice = 0; //Выбор пользователя
    getmaxyx(stdscr, max_rows, max_cols);
    int mid_rows = max_rows / 2;
    int mid_cols = max_cols / 2;
    curs_set(0);
    keypad(stdscr, true);
    while (!stop_) {
        switch (mode_) {
            case MainMenu: {
                clear();
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
                            map_.Load(mobs_, hero_, princess_, map_cols_, map_rows_);
                            mode_ = InGame;
                            clear();
                        }
                        break;
                }
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
//                clear();
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
                mvwprintw(stdscr, 1, 0, "%s %d ", "Points", ((Hero *) hero_)->cur_score_points_);

                std::map<int, int> mp({ // pair -> int
                                              {KEY_UP,    0},
                                              {KEY_RIGHT, 1},
                                              {KEY_DOWN,  2},
                                              {KEY_LEFT,  3},
                                      });
                std::map<CollideResult, std::pair<int, int>> moveDirection({
                                                                                   {CanMoveUp,    {-1, 0}},
                                                                                   {CanMoveRigth, {0,  1}},
                                                                                   {CanMoveDown,  {1,  0}},
                                                                                   {CanMoveLeft,  {0,  -1}},
                                                                                   {CannotMove,   {0,  0}},
                                                                           });
                auto sym = getch();
                if (sym == KEY_ESC) {
                    mode_ = MainMenu;
                    MemoryFree();
                } else {
                    CollideResult moveResult = hero_->Move(map_.getArea(hero_->row_pos_, hero_->col_pos_), mp[sym]);
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
                            map_.moveActor(hero_->row_pos_,
                                           hero_->col_pos_,
                                           hero_->row_pos_ + moveDirection[moveResult].first,
                                           hero_->col_pos_ + moveDirection[moveResult].second);
                            break;
                        }
                        case MobDie: {
                            moveResult = (CollideResult) mp[sym];
                            map_.v[hero_->row_pos_ +
                                   moveDirection[moveResult].first][hero_->col_pos_ +
                                                                    moveDirection[moveResult].second] = (Actor *) new Floor(
                                    hero_->row_pos_ + moveDirection[moveResult].first,
                                    hero_->row_pos_ + moveDirection[moveResult].second);
                            break;
                        }
                    }
                    if (mode_ == EndGame) {
                        break;
                    }
                    for (int i = 0; i < mobs_.size(); ++i) {
                        auto mob = mobs_[i];
                        CollideResult moveResult2 = mob->Move(map_.getArea(mob->row_pos_, mob->col_pos_), mp[sym]);
                        switch (moveResult2) {
                            case GameOver:
                            case Victory: {
                                mode_ = EndGame;
                                endgameMessage_ = moveResult == Victory ? "You win" : "You lose";
                                MemoryFree();
                                break;
                            }
                            case CanMoveUp:
                            case CanMoveRigth:
                            case CanMoveLeft:
                            case CanMoveDown: {
                                map_.moveActor(mob->row_pos_, mob->col_pos_,
                                               mob->row_pos_ + moveDirection[moveResult2].first,
                                               mob->col_pos_ + moveDirection[moveResult2].second);
                                break;
                            }
                            case MobDie:
                            case CannotMove: {
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
                }

                break;
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
