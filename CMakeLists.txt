cmake_minimum_required(VERSION 3.13)
project(testRogulike)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses")
set(CMAKE_CXX_FLAGS "-lncurses -fsanitize=address")

add_executable(testRogulike source/main.cpp include/GameManager.h include/Actors.hpp include/Map.hpp source/Hero.cpp include/Hero.h source/Dragon.cpp include/Dragon.h source/Wall.cpp include/Wall.h source/Zombie.cpp include/Zombie.h source/Princess.cpp include/Princess.h source/Dragon.cpp include/Dragon.h source/GameManager.cpp include/Floor.h source/Floor.cpp source/FireBall.cpp include/FireBall.h source/Floor.cpp include/Floor.h source/BonusManaBox.cpp include/BonusManaBox.h source/Config.cpp include/Config.h source/BonusHealth.cpp)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries(testRogulike ${CURSES_LIBRARIES})
endif ()