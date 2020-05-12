#include <iostream>
//#include <SFML/Graphics.hpp>

#include "Game.h"


/*TODO
 * Menu - Almost
 *  Settings
 *  High score
 *  Choose
 * Map loading properly - Done
 * Weapon - Done
 * Projectile - Done
 * CLI-game
 * Objective
 * Score
 * Documentation
 * */

int main() {
    DoomCopy::Game game;
    game.startGraphicalGame("mapV1",DoomCopy::Point(216,144),DoomCopy::Point(1080,720));
    return 0;
}
