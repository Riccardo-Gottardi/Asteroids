cmake_minimum_required(VERSION 3.27)
project(Asteroids)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(Asteroids main.cpp
        SpaceShip.cpp
        SpaceShip.h
        Asteroid.cpp
        Asteroid.h
        Projectile.cpp
        Projectile.h
        ProjectilesManager.cpp
        ProjectilesManager.h)

include(FindPkgConfig)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})