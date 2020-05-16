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
#include "List.h"
#include "Map.h"
#include "Player.h"

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

        //bool cli = true;
        sf::Keyboard::Key bindings[10];

    public:
        sf::RenderWindow* window = NULL;
        sf::Font font;

        Game(bool cli);
        void startGraphicalGame(const char* mapName, Point resolution, Point screenSize);

        void renderWalls();
        void renderEnemies();
        void renderProjectiles();
        void renderWeapon();
        void deleteDeadOrNonExistent();
        void loadSettings();
        void winCondition(std::string mapName, int& x, int& y);

        void startCLIGame(const char* mapName);
        bool command(const std::string& cmd, bool& exit, int& aim);

        void setScreenWidth(int newWidth) {
            SCREEN_WIDTH = newWidth;
            if (window != NULL)
                window->setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        void setScreenHeight(int newHeight) {
            SCREEN_HEIGHT = newHeight;
            if (window != NULL)
                window->setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
        }

        void setResWidth(int newRWidth) {
            screenWidth = newRWidth;
        }

        void setResHeight(int newRHeight) {
            screenHeight = newRHeight;
        }

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

        ~Game() {
            if (player != NULL)
                delete player;
            if (map != NULL)
                delete map;
            if (window != NULL)
                delete window;
        }
    };

    void numpad(sf::RenderWindow* window, int* variableToSaveInto, std::string textToWriteOut);

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

    class SetScreenWidth : public Menu {
    public:
        Game* game;
        SetScreenWidth(Game& game, Menu* back) : Menu(0,"Set new screen width",back) {
            this->game = &game;
        }

        void doAction() {
            std::string string = "New width ";
            int newScreenWidth = 0;
            numpad(game->window, &newScreenWidth, string);
            game->setScreenWidth(newScreenWidth);
        }
    };

    class SetScreenHeight : public Menu {
    public:
        Game* game;
        SetScreenHeight(Game& game, Menu* back) : Menu(0,"Set new screen height",back) {
            this->game = &game;
        }

        void doAction() {
            std::string string = "New height ";
            int newScreenHeight = 0;
            numpad(game->window, &newScreenHeight, string);
            game->setScreenHeight(newScreenHeight);
        }
    };

    class SetResWidth : public Menu {
    public:
        Game* game;
        SetResWidth(Game& game, Menu* back) : Menu(0,"Set new resolution width",back) {
            this->game = &game;
        }

        void doAction() {
            std::string string = "New width ";
            int newResWidth = 0;
            numpad(game->window,&newResWidth,string);
            game->setResWidth(newResWidth);
        }
    };

    class SetResHeight : public Menu {
    public:
        Game* game;
        SetResHeight(Game& game, Menu* back) : Menu(0,"Set new resolution height",back) {
            this->game = &game;
        }

        void doAction() {
            std::string string = "New Height ";
            int newResHeight = 0;
            numpad(game->window,&newResHeight,string);
            game->setResHeight(newResHeight);
        }
    };

    class ScreenSettings : public Menu {
    public:
        Game* game;
        ScreenSettings(Game& game, Menu* back) : Menu(5,"Display Settings",back) {
            this->game = &game;
            addItem(new SetScreenWidth(game,this));
            addItem(new SetScreenHeight(game,this));
            addItem(new SetResWidth(game, this));
            addItem(new SetResHeight(game,this));
        }
    };

    class Settings : public Menu {
    public:
        Game* game;
        Settings(Game& game, size_t arraySize, std::string name, Menu* back) : Menu(arraySize, name, back) {
            this->game = &game;
            this->addItem(new ScreenSettings(game,this));
        }
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

    class MapHighScore : public Menu {
    public:
        Game* game;
        sf::Text scores[10];
        int lineNr = 0;
        std::string mName;
        MapHighScore(Menu* back, std::string mapName, Game& game) : Menu(0,mapName,back) {
            mName = mapName;
            this->game = &game;
            mapName += "/scores.txt";
            std::fstream file;
            file.open(mapName);
            std::string line = "";

            do {
                std::getline(file,line);
                if (!line.empty()) {
                    scores[lineNr].setString(line);
                    lineNr++;
                } else
                    break;
            } while (!file.eof());

            for (int i = 0; i < lineNr; i++) {
                scores[i].setPosition(this->game->getScreenWidth()/2,this->game->getScreenHeight()/lineNr * i);
                scores[i].setCharacterSize(50);
                scores[i].setFillColor(sf::Color::White);
            }
        }

        void doAction() {
            sf::Event event;
            bool exit = false;

            sf::Font font;
            if (!font.loadFromFile("FunSized.ttf")) {
                if (!font.loadFromFile("Roboto-Regular.ttf")) {
                    font.loadFromFile("advanced_pixel-7.ttf");
                }
            }

            while (game->window->isOpen()) {
                while(game->window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        game->window->close();
                    if (event.type == sf::Event::KeyPressed) {
                        exit = true;
                    }
                }

                for (int i = 0; i < lineNr; i++)
                    scores[i].setFont(font);

                game->window->clear();
                for (int i = 0; i < lineNr; i++)
                    game->window->draw(scores[i]);
                game->window->display();

                if (exit) break;
            }
        }
    };

    class HighScore : public Menu {
    public:
        Game* game;
        HighScore(Menu* back, Game& game) : Menu(4,"High scores",back) {
            this->game = &game;
            std::fstream file;
            std::string line = "";
            file.open("maps.conf");

            do {
                std::getline(file,line);
                if (!line.empty()) {
                    this->addItem(new MapHighScore(this,line,*this->game));
                }
            } while(!file.eof());
        }

    };

    class MainMenu : public Menu {
    public:
        Game* game;
        MainMenu(std::string name, Game& game) : Menu(2, name) {
            this->game = &game;
            this->addItem(new Start(game,4,"Start",this));
            this->addItem(new Settings(game, 2,"Settings",this));
            this->addItem(new HighScore(this,*this->game));
            this->addItem(new Exit(game,this));
        }
    };
}

#endif //DOOMCOPY_GAME_H
