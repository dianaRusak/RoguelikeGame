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
                CreateMenu();
                break;
            }
            case EndGame: {
                ExitGM();
                break;
            }
            case InGame: {
                HeroCentralization();
                MapDrawing();
                auto sym = getch();

                GameHero(sym);
                if (mode_ == EndGame)
                    break;
                for (int i = 0; i < mobs_.size(); ++i) {
                    auto mob = mobs_[i];
                    if ((RechargeTimer % 5 == 0) && (mob->GetIdent() == 'D')) {
                        FireballAttackDragon(sym, mob);
                    }
                    moveResult = mob->Move(map_.getArea(mob->row_pos_, mob->col_pos_), mp[sym]);
                    MobStep(sym, mob);
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
    endwin();
}

void GameManager::MemoryFree() {
    hero_ = nullptr;
    princess_ = nullptr;
    RechargeTimer = 1;
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

void GameManager::FireballAttackDragon(int sym, Actor *mob) {
    if (mob->GetIdent() == 'D') {
        Actor *fireBall = map_.CreateFireball(mob->row_pos_, mob->col_pos_, mp[sym] % 4,
                                              config);
        if (fireBall != nullptr) {
            mobs_.push_back(fireBall);
        }
    }
}


void GameManager::CreateMenu() {
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
    halfdelay(5);
}

void GameManager::ExitGM() {
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
}

void GameManager::HeroCentralization() {
    getmaxyx(stdscr, max_rows, max_cols);
    mid_rows = max_rows / 2;
    mid_cols = max_cols / 2;

    for (int row = 0; row <= max_rows; ++row) {
        for (int col = 0; col <= max_cols; ++col) {
            mvaddch(row, col, ' ');
        }
    }
    mvaddch(mid_rows, mid_cols, map_.v[hero_->row_pos_][hero_->col_pos_]->GetIdent());
    hero_row = hero_->row_pos_;
    hero_col = hero_->col_pos_;

    top_row_bound = hero_row - std::min<int>(max_rows, hero_row);
    bottom_row_bound = hero_row + std::min<int>(max_rows, map_rows_ - hero_row - 1);
    left_col_bound = hero_col - std::min<int>(max_cols, hero_col);
    right_col_bound = hero_col + std::min(max_cols, map_cols_ - hero_col - 1);


}

void GameManager::MapDrawing() {
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
}

void GameManager::GameHero(int sym) {
    switch (sym) {
        case KEY_W:
        case KEY_D:
        case KEY_S:
        case KEY_A: {
            FireballAttackHero(sym);
            break;
        }
        case KEY_UP:
        case KEY_RIGHT:
        case KEY_DOWN:
        case KEY_LEFT: {
            moveResult = hero_->Move(map_.getArea(hero_->row_pos_, hero_->col_pos_), mp[sym]);
            RechargeTimer++;
            HeroStep(sym);
            break;
        }
    }
}

void GameManager::FireballAttackHero(int sym) {
    if (hero_->cur_mana_points_ > 0) {
        Actor *fireBall = map_.CreateFireball(hero_->row_pos_, hero_->col_pos_, mp[sym] % 4,
                                              config);
        hero_->cur_mana_points_ -= config.mana_damage_hero;
        if (fireBall != nullptr) {
            mobs_.push_back(fireBall);
        }
    }
}

void GameManager::HeroStep(int sym) {
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
}

void GameManager::MobStep(int sym, Actor *mob) {
    switch (moveResult) {
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
                           mob->row_pos_ + mvDir[moveResult].first,
                           mob->col_pos_ + mvDir[moveResult].second);
            break;
        }
        case MobDie: {
            if (mob->GetIdent() == config.identifier_fireBall) {
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
            if (mob->GetIdent() == config.identifier_fireBall) {
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
}

