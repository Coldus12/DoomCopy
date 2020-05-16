cmake_minimum_required(VERSION 3.16)
project(DoomCopy)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 11)

add_executable(DoomCopy main.cpp Array2D.h List.h StringManager.h Texture.h Point.h BlockType.cpp BlockType.h Map.cpp Map.h Creature.cpp Creature.h Player.h Game.cpp Game.h MeleeEnemy.h Player.cpp Weapon.cpp Weapon.h Projectile.cpp Projectile.h Menu.h)

target_link_libraries(DoomCopy sfml-graphics sfml-audio)