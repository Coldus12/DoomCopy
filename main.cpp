#include <iostream>
//#include <SFML/Graphics.hpp>
#include "DoomCopy.h"

int main() {
    DoomCopy::Game game;
    game.startGraphicalGame("textures/mapV1.png",DoomCopy::Point(216,144),DoomCopy::Point(1080,720));
    return 0;
}
