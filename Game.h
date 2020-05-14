//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_GAME_H
#define DOOMCOPY_GAME_H


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


#include "Array2D.h"
#include "Creature.h"
#include "Menu.h"

inline bool cmp(DoomCopy::Creature* i, DoomCopy::Creature* j) {
    return (i->distanceFromPlayer > j->distanceFromPlayer);
}

namespace DoomCopy {

    class Game {
        double degree = M_PI/180;
        Map* map = NULL;
        int SCREEN_WIDTH;
        int SCREEN_HEIGHT;
        int screenWidth;
        int screenHeight;
        Array2D<sf::Vertex*> verteces;
        Player* player = NULL;

        bool cli = false;
        sf::Keyboard::Key bindings[10];

    public:
        sf::RenderWindow* window = NULL;

        Game();
        void startGraphicalGame(const char* mapName, Point resolution, Point screenSize);

        void renderWalls();
        void renderEnemies();
        void renderProjectiles();
        void renderWeapon();
        void deleteDeadOrNonExistent();
        void loadSettings();

        int getScreenWidth() {
            return SCREEN_WIDTH;
        }

        int getScreenHeight() {
            return SCREEN_HEIGHT;
        }

        int getResWidth() {
            return screenWidth;
        }

        int getResHeight() {
            return screenHeight;
        }

        bool isCLI() {return cli;}

        ~Game() {
            if (window != NULL)
                delete window;
            if (player != NULL)
                delete player;
            if (map != NULL)
                delete map;
        }
    };

    class GStartGame : public Menu {
    public:
        Game* game;
        GStartGame(Game& game, std::string name, Menu* back = NULL) : Menu(0, name, back) {
            this->game = &game;
        }

        void doAction() {
            game->startGraphicalGame(text.c_str(),Point(game->getResWidth(),game->getResHeight()),Point(game->getScreenWidth(),game->getScreenHeight()));
        }
    };

    class Start : public Menu {
    public:
        Game* game;
        Start(Game& game, size_t arraySize, std::string name, Menu* back = NULL) : Menu(arraySize, name, back) {
            std::fstream file;
            file.open("maps.conf");
            std::string line = "";
            this->game = &game;

            do {
                std::getline(file,line);
                this->addItem(new GStartGame(game, line, this));
            } while(!file.eof());
        }
    };

    class ScreenSettings : public Menu {
    public:
        ScreenSettings(Menu* back) : Menu(0,"Display Settings",back) {}

        void doAction() {

        }
    };

    class Settings : public Menu {
    public:
        Settings(size_t arraySize, std::string name, Menu* back) : Menu(arraySize, name, back) {}
    };

    class Exit : public Menu {
    public:
        Game* game;
        Exit(Game& game, Menu* back) : Menu(0,"Exit",back) {
            this->game = &game;
        }

        void doAction() {
            game->window->close();
        }
    };

    class MainMenu : public Menu {
    public:
        Game* game;
        MainMenu(std::string name, Game& game) : Menu(2, name) {
            this->game = &game;
            this->addItem(new Start(game,4,"Start",this));
            this->addItem(new Settings(2,"Settings",this));
            this->addItem(new Exit(game,this));
        }
    };

}

#endif //DOOMCOPY_GAME_H
