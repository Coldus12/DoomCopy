#include <iostream>
//#include <SFML/Graphics.hpp>

#include "Game.h"


/*TODO
 * Menu
 *  Settings
 *  High score
 *  Choose
 * Map loading properly
 * Weapon - Done
 * Projectile - Done
 * CLI-game
 * Objective
 * Score
 * Documentation
 * */

int main() {
    DoomCopy::Game game;
    game.startGraphicalGame("textures/mapV1.png",DoomCopy::Point(216,144),DoomCopy::Point(1080,720));
    return 0;
}
