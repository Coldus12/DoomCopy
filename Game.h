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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                 Game                                                           ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


///Szornyek tavolsagat osszehasonlito fuggveny, a palya
///szornylistajanak rendezese miatt van erre szukseg.
///@param i - egyik szorny pointere
///@param j - masik szorny pointere
///@return - i tavolabb van-e a jatekostol mint j
inline bool cmp(DoomCopy::Creature* i, DoomCopy::Creature* j) {
    return (i->distanceFromPlayer > j->distanceFromPlayer);
}

namespace DoomCopy {

    ///Maga a jatek, ez kezel mindent, es ebben tortenik minden.
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

        ///Elinditja a jatekot vagy grafikusan vagy CLI-ben futva.
        ///@param cli - cli-ben induljon-e a jatek
        Game(bool cli);

        ///Elinditja a jatekot grafikusan egy palyan, adott ablakmerettel, es felbontassal.
        ///@param mapName - palya neve
        ///@param resolution - felbontas
        ///@param screenSize - ablak merete
        void startGraphicalGame(const char* mapName, Point resolution, Point screenSize);

        ///Kiszamolja, hogy mit lat a jatekos: milyen blokknak, melyik reszet, melyik texturat.
        void renderWalls();

        ///Vegig fut a palya szorny listajan, es megfelelo helyre, a szorny allapotanak
        ///megfelelo texturaju szornyet rajzol ki, ha az a jatekos latoszogben benne van,
        ///nem takarja ki blokk, es nincs tavolabb, mint a jatekos latotavolsaga.
        void renderEnemies();

        ///Vegig fut a palya lovedek listajan, es a megfelelo helyekre kirajzolja a lovedekeket,
        ///ha azok a jatekos latoszogebe esnek, nincsenek tavolabb, mint a jatekos latotavolsaga,
        ///es nem takarja el oket egy (vagy tobb) blokk.
        void renderProjectiles();

        ///Beallitja a jatekos fegyverenek allapota alapjan, hogy a fegyver melyik texturajat rajzolja majd ki.
        void renderWeapon();

        ///Kitorli a lovedek listabol azokat a lovedekeket, amik mar nem leteznek (bele utkoztek valamibe, vagy
        ///tul mentek a range-ukon). Es kitorli azokat a szornyeket a szorny listabol, melyek mar meghaltak.
        void deleteDeadOrNonExistent();

        ///Betolti a controls.conf konfiguracios fajlbol a kezdo beallitasokat,
        ///mint az iranyitast, felbontast, es kepenyo meretet
        void loadSettings();

        ///Betolti egy palya mappajaban levo whereto.conf konfiguracios fajlt, ami tartalmazza
        ///azt a poziciot, ahova a jatekosnak el kell jutnia azert, hogy a palyan vegig jusson.
        ///@param x - ide tolti be az elerendo cel x koordinatajat
        ///@param y - ide tolti be az elerendo cel y koordinatajat
        ///@param mapName - a palya neve, aminek a mappajaban a whereto.conf talalhato
        void winCondition(std::string mapName, int& x, int& y);

        ///Elinditja a jatekot a mapName nevu palyaval CLI-s modban.
        ///@param mapName - palya neve
        void startCLIGame(const char* mapName);

        ///Ertelmezi a kovetkezo parancsokat: quit, shoot, aim, move, printmap, listmonsters, hp
        ///Akcio tipusu parancsok: shoot, move
        ///Nem akcio tipusu parancsok: aim, quit, printmap, hp, listmonsters
        ///@param cmd - parancs
        ///@param aim - a becolazando szorny indexe
        ///@param exit - kilepjen-e a jatekbol
        ///@return - akcio tipusu parancs lett-e beirva
        bool command(const std::string& cmd, bool& exit, int& aim);

        ///Beallit grafikus futasban az ablaknak egy uj szelesseget, felteve, hogy az nagyobb, mint 100
        ///@param newWidth - az ablak uj szelessege
        void setScreenWidth(int newWidth) {
            if (newWidth > 100) {
                SCREEN_WIDTH = newWidth;
                if (window != NULL)
                    window->setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
            }
        }

        ///Beallit grafikus futasban az ablaknak egy uj magassagot, felteve, hogy az nagyobb, mint 100
        ///@param newHeight - az ablak uj magassaga
        void setScreenHeight(int newHeight) {
            if (newHeight > 100) {
                SCREEN_HEIGHT = newHeight;
                if (window != NULL)
                    window->setSize(sf::Vector2u(SCREEN_WIDTH, SCREEN_HEIGHT));
            }
        }

        ///Beallit a felbontasnak egy uj szelesseget (felteve hogy az nagyobb mint 100)
        ///@param newRWidth - felbontas uj szelessege
        void setResWidth(int newRWidth) {
            if (newRWidth > 100)
                screenWidth = newRWidth;
        }

        ///Beallit a felbontasnak egy uj magassagot (felteve hogy az nagyobb mint 100)
        ///@param newRHeight - felbontas uj magassaga
        void setResHeight(int newRHeight) {
            if (newRHeight > 100)
                screenHeight = newRHeight;
        }

        ///Visszaadja az ablak szelesseget
        ///@return - ablak szelessege
        int getScreenWidth() {
            return SCREEN_WIDTH;
        }

        ///Visszaadja az ablak magassagat
        ///@return - ablak magassaga
        int getScreenHeight() {
            return SCREEN_HEIGHT;
        }

        ///Visszaadja a felbontas szelesseget
        ///@return - felbontas szelessege
        int getResWidth() {
            return screenWidth;
        }

        ///Visszaadja a felbontas magassagat
        ///@return - felbontas magassaga
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

    ///4 menu is ezt a fuggvenyt hasznalja. Gyakorlatilag egy numpad, mint ahogy azt a neve
    ///is sugallja. Egy ablakon erzekeli a szamok beuteset, egy tetszoleges szoveg utan kiirja
    ///azokat, es ha entert nyomnak, akkor az uj szamot (amit beutottek) be irja egy a fuggvenynek
    ///atadott valtozoba.
    ///@param window - ablak amibe a numpad uzemel
    ///@param textToWriteOut - a szoveg amiket a szamok ele kiir
    ///@param variableToSaveInto - a valtozo amibe az uj erteket elmenti.
    void numpad(sf::RenderWindow* window, int* variableToSaveInto, std::string textToWriteOut);

    ///Egy palya elinditasara szolgalo menupont.
    ///Elinditja a menuponttal azonos nevu palya grafikusan.
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

    ///Start menu, kivalasztasa utan felsorolja az osszes map.conf-ban levo palyat.
    ///GStartGame-ekre mutat.
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

    ///A menupont amelyik atallitja az ablak szelesseget
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

    ///A menupont amelyik atallitja az ablak magassagat
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

    ///Menupont ami atallitja a felbontas szelesseget
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

    ///Menupont ami atallitja a felbontas magassagat
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

    ///Kepernyo beallitasait tartalmazo almenu
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

    ///Beallitasokat tartalmazo menu
    class Settings : public Menu {
    public:
        Game* game;
        Settings(Game& game, size_t arraySize, std::string name, Menu* back) : Menu(arraySize, name, back) {
            this->game = &game;
            this->addItem(new ScreenSettings(game,this));
        }
    };

    ///Kilepesi menu
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

    ///Egy palyahoz tartozo high score-okat tolti be, majd kivalasztasa utan irja ki.
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

    ///MapHighScore menupontokat tartalmazo menu
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

    ///Fomenu, ha a jatek grafikus modban indul, akkor az ablakban ezt a menut lathatjuk eloszor
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
