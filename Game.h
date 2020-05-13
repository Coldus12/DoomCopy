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

    class StartGameG : public MenuItem {
    public:
        Game* game;
        StartGameG(const char* nameOfTheLevel, Game& game) : MenuItem(0) {
            text = nameOfTheLevel;
            this->game = &game;

            //sf::Font font;
            //font.loadFromFile("FunSize.ttf");

            //sfText.setFont(font);
            sfText.setFillColor(sf::Color::White);
            sfText.setString(text);
            sfText.setCharacterSize(20);
        }

        void doSomething() {
            if (!game->isCLI())
                game->startGraphicalGame(text.c_str(),Point(game->getResWidth(), game->getResHeight()),Point(game->getScreenWidth(), game->getScreenHeight()));
        }
    };

    class Start : public MenuItem {
    public:
        Start(Game& game) : MenuItem(10) {
            text = "Start";
            loadMaps(*this, game);

            sfText.setFillColor(sf::Color::White);
            sfText.setString(text);
            sfText.setCharacterSize(40);
        }

        void loadMaps(MenuItem& menu, Game& game) {
            std::fstream file;
            file.open("maps.conf");
            std::string line = "";
            do {
                std::getline(file,line);
                menu.addItem(new StartGameG(line.c_str(), game));
            } while(!file.eof());
        }
    };

    class Settings : public MenuItem {
    public:
        Settings() : MenuItem(0) {

            text = "Settings";
            sfText.setFillColor(sf::Color::White);
            sfText.setString(text);
            sfText.setCharacterSize(40);

        }
    };

    class Exit : public MenuItem {
        Game* game;
    public:
        Exit(Game& game) : MenuItem(0) {
            this->game = &game;

            text = "Exit";
            sfText.setFillColor(sf::Color::White);
            sfText.setString(text);
            sfText.setCharacterSize(40);
        }

        void doSomething() {
            game->window->close();
        }
    };

    class MainMenu : public MenuItem {
    public:
        //sf::Text sfText;
        MainMenu(Game& game) : MenuItem(4) {
            addItem(new Start(game));
            addItem(new Settings);
            addItem(new Exit(game));
        }
    };

}

#endif //DOOMCOPY_GAME_H
