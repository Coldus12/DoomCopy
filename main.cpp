#include <iostream>
//#include <SFML/Graphics.hpp>

#include "Game.h"


/*TODO
 * Menu - Done
 *  Settings - Done
 *  High score - Done
 * Map loading properly - Done
 * Weapon - Done
 * HP - Done
 * Projectile - Done
 * CLI-game - Done
 * Objective - Done
 * Score - Done
 * Documentation
 * */

int main(int argc, char **argv) {
    if (argc == 1) {
        DoomCopy::Game game(false);
    } else {
        std::string arg2 = argv[1];
        if (arg2.find("cli") != std::string::npos)
            DoomCopy::Game game(true);
        else
            DoomCopy::Game game(false);
    }
    return 0;
}
