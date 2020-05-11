//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_GAME_H
#define DOOMCOPY_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>

#include "Array2D.h"
#include "Creature.h"

inline bool cmp(DoomCopy::Creature* i, DoomCopy::Creature* j) {
    return (i->distanceFromPlayer > j->distanceFromPlayer);
}

namespace DoomCopy {

    class Game {
        sf::RenderWindow* window = NULL;
        double degree = M_PI/180;
        Map* map;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int screenWidth;
        int screenHeight;
        Array2D<sf::Vertex*> verteces;
        Player* player;

    public:
        Game() {}
        void startGraphicalGame(const char* mapName, Point resolution, Point screenSize);

        void renderWalls();
        void renderEnemies();
        void renderProjectiles();
        void renderWeapon();
        void deleteDeadOrNonExistent();

        ~Game() {
            delete window;
            delete player;
            delete map;
        }
    };
}

#endif //DOOMCOPY_GAME_H
