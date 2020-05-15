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
        void winCondition(std::string mapName, int& x, int& y);

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

        bool isCLI() {return cli;}

        ~Game() {
            if (player != NULL)
                delete player;
            if (map != NULL)
                delete map;
            if (window != NULL)
                delete window;
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

    class SetScreenWidth : public Menu {
    public:
        Game* game;
        SetScreenWidth(Game& game, Menu* back) : Menu(0,"Set new screen width",back) {
            this->game = &game;
        }

        void doAction() {
            bool done = false;
            sf::Event event;
            List<int> int_list;
            int listnr = 0;

            sf::Font font;
            if (!font.loadFromFile("FunSized.ttf")) {
                font.loadFromFile("Roboto-Regular.ttf");
            }

            while (game->window->isOpen()) {
                while (game->window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        game->window->close();

                    if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Escape)
                            game->window->close();

                        if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
                            int_list.addItem(0);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            int_list.addItem(1);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            int_list.addItem(2);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            int_list.addItem(3);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                            int_list.addItem(4);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                            int_list.addItem(5);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
                            int_list.addItem(6);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
                            int_list.addItem(7);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
                            int_list.addItem(8);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
                            int_list.addItem(9);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (listnr > 0) {
                                int_list.deleteAt(listnr - 1);
                                listnr--;
                            }
                        }

                        if (event.key.code == sf::Keyboard::Enter) {
                            int screenWidth = 0;
                            for (int i = 0; i < listnr; i++) {
                                screenWidth += int_list.at(i);
                                if (i != listnr - 1)
                                    screenWidth *= 10;
                            }
                            game->setScreenWidth(screenWidth);
                            done = true;
                        }
                    }
                }

                sf::Text text;
                std::string string = "New width ";
                for (int i = 0; i < listnr; i++)
                    string += std::to_string(int_list.at(i));

                text.setString(string);
                text.setPosition(100,100);
                text.setCharacterSize(75);
                text.setFont(font);
                text.setFillColor(sf::Color::White);

                game->window->clear();
                game->window->draw(text);
                game->window->display();

                if (done)
                    break;

            }
        }
    };

    class SetScreenHeight : public Menu {
    public:
        Game* game;
        SetScreenHeight(Game& game, Menu* back) : Menu(0,"Set new screen height",back) {
            this->game = &game;
        }

        void doAction() {
            bool done = false;
            sf::Event event;
            List<int> int_list;
            int listnr = 0;

            sf::Font font;
            if (!font.loadFromFile("FunSized.ttf")) {
                font.loadFromFile("Roboto-Regular.ttf");
            }

            while (game->window->isOpen()) {
                while (game->window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        game->window->close();

                    if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Escape)
                            game->window->close();

                        if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
                            int_list.addItem(0);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            int_list.addItem(1);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            int_list.addItem(2);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            int_list.addItem(3);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                            int_list.addItem(4);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                            int_list.addItem(5);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
                            int_list.addItem(6);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
                            int_list.addItem(7);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
                            int_list.addItem(8);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
                            int_list.addItem(9);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (listnr > 0) {
                                int_list.deleteAt(listnr - 1);
                                listnr--;
                            }
                        }

                        if (event.key.code == sf::Keyboard::Enter) {
                            int screenHeight = 0;
                            for (int i = 0; i < listnr; i++) {
                                screenHeight += int_list.at(i);
                                if (i != listnr - 1)
                                    screenHeight *= 10;
                            }
                            game->setScreenHeight(screenHeight);
                            done = true;
                        }
                    }
                }

                sf::Text text;
                std::string string = "New height ";
                for (int i = 0; i < listnr; i++)
                    string += std::to_string(int_list.at(i));

                text.setString(string);
                text.setPosition(100,100);
                text.setCharacterSize(75);
                text.setFont(font);
                text.setFillColor(sf::Color::White);

                game->window->clear();
                game->window->draw(text);
                game->window->display();

                if (done)
                    break;

            }
        }
    };

    class SetResWidth : public Menu {
    public:
        Game* game;
        SetResWidth(Game& game, Menu* back) : Menu(0,"Set new resolution width",back) {
            this->game = &game;
        }

        void doAction() {
            bool done = false;
            sf::Event event;
            List<int> int_list;
            int listnr = 0;

            sf::Font font;
            if (!font.loadFromFile("FunSized.ttf")) {
                font.loadFromFile("Roboto-Regular.ttf");
            }

            while (game->window->isOpen()) {
                while (game->window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        game->window->close();

                    if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Escape)
                            game->window->close();

                        if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
                            int_list.addItem(0);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            int_list.addItem(1);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            int_list.addItem(2);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            int_list.addItem(3);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                            int_list.addItem(4);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                            int_list.addItem(5);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
                            int_list.addItem(6);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
                            int_list.addItem(7);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
                            int_list.addItem(8);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
                            int_list.addItem(9);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (listnr > 0) {
                                int_list.deleteAt(listnr - 1);
                                listnr--;
                            }
                        }

                        if (event.key.code == sf::Keyboard::Enter) {
                            int resWidth = 0;
                            for (int i = 0; i < listnr; i++) {
                                resWidth += int_list.at(i);
                                if (i != listnr - 1)
                                    resWidth *= 10;
                            }
                            game->setResWidth(resWidth);
                            done = true;
                        }
                    }
                }

                sf::Text text;
                std::string string = "New width ";
                for (int i = 0; i < listnr; i++)
                    string += std::to_string(int_list.at(i));

                text.setString(string);
                text.setPosition(100,100);
                text.setCharacterSize(75);
                text.setFont(font);
                text.setFillColor(sf::Color::White);

                game->window->clear();
                game->window->draw(text);
                game->window->display();

                if (done)
                    break;

            }
        }
    };

    class SetResHeight : public Menu {
    public:
        Game* game;
        SetResHeight(Game& game, Menu* back) : Menu(0,"Set new resolution height",back) {
            this->game = &game;
        }

        void doAction() {
            bool done = false;
            sf::Event event;
            List<int> int_list;
            int listnr = 0;

            sf::Font font;
            if (!font.loadFromFile("FunSized.ttf")) {
                font.loadFromFile("Roboto-Regular.ttf");
            }

            while (game->window->isOpen()) {
                while (game->window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        game->window->close();

                    if (event.type == sf::Event::KeyPressed) {

                        if (event.key.code == sf::Keyboard::Escape)
                            game->window->close();

                        if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0) {
                            int_list.addItem(0);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1) {
                            int_list.addItem(1);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2) {
                            int_list.addItem(2);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3) {
                            int_list.addItem(3);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4) {
                            int_list.addItem(4);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5) {
                            int_list.addItem(5);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6) {
                            int_list.addItem(6);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7) {
                            int_list.addItem(7);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8) {
                            int_list.addItem(8);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9) {
                            int_list.addItem(9);
                            listnr++;
                        }

                        if (event.key.code == sf::Keyboard::BackSpace) {
                            if (listnr > 0) {
                                int_list.deleteAt(listnr - 1);
                                listnr--;
                            }
                        }

                        if (event.key.code == sf::Keyboard::Enter) {
                            int resHeight = 0;
                            for (int i = 0; i < listnr; i++) {
                                resHeight += int_list.at(i);
                                if (i != listnr - 1)
                                    resHeight *= 10;
                            }
                            game->setResHeight(resHeight);
                            done = true;
                        }
                    }
                }

                sf::Text text;
                std::string string = "New height ";
                for (int i = 0; i < listnr; i++)
                    string += std::to_string(int_list.at(i));

                text.setString(string);
                text.setPosition(100,100);
                text.setCharacterSize(75);
                text.setFont(font);
                text.setFillColor(sf::Color::White);

                game->window->clear();
                game->window->draw(text);
                game->window->display();

                if (done)
                    break;

            }
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

    class MainMenu : public Menu {
    public:
        Game* game;
        MainMenu(std::string name, Game& game) : Menu(2, name) {
            this->game = &game;
            this->addItem(new Start(game,4,"Start",this));
            this->addItem(new Settings(game, 2,"Settings",this));
            this->addItem(new Exit(game,this));
        }
    };

}

#endif //DOOMCOPY_GAME_H
