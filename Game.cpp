//
// Created by coldus on 5/8/20.
//

#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include "Creature.h"
#include "Player.h"
#include "Menu.h"

//                                          Seged fuggvenyke
//----------------------------------------------------------------------------------------------------------------------
//Szornyek torlesehez
void fnc(DoomCopy::Creature* cre) {
    delete cre;
}

//Lovedekek torlesehez
void fnc2(DoomCopy::Projectile* pro) {
    delete pro;
}

//ket "highscore"-t osszehasonlito fuggveny
bool scoreCmpr(int i, int i2) {
    return i > i2;
}

//                                          A JATEK
//----------------------------------------------------------------------------------------------------------------------
DoomCopy::Game::Game(bool cli) {
    try {
        //                                      Grafikus modban inditva
        //--------------------------------------------------------------------------------------------------------------
        if (cli == false) {

            //Font betoltese
            if (!font.loadFromFile("FunSized.ttf")) {
                if (!font.loadFromFile("Roboto-Regular.ttf")) {
                    font.loadFromFile("advanced_pixel-7.ttf");
                }
            }

            //Beallitasok betoltese
            loadSettings();
            window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DoomCopy!",sf::Style::Titlebar | sf::Style::Close);

            //Fomenu
            MainMenu menu("Main",*this);
            Menu* iter = &menu;
            int sel = 0;

            sf::Event event;
            while(window->isOpen()) {

                while(window->pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                        window->close();
                    } else if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::Escape)
                            window->close();

                        if (event.key.code == sf::Keyboard::Up)
                            sel--;

                        if (event.key.code == sf::Keyboard::Down)
                            sel++;

                        if(event.key.code == sf::Keyboard::Enter) {
                            if (sel != iter->nr_of_menus) {
                                if (iter->options[sel]->nr_of_menus != 0)
                                    iter = iter->options[sel];
                                else
                                    iter->options[sel]->doAction();
                            } else {
                                iter = iter->back;
                            }
                        }

                    }
                }

                for (int i = 0; i < iter->nr_of_menus; i++) {
                    iter->options[i]->gText.setString(iter->options[i]->text);
                    iter->options[i]->gText.setFillColor(sf::Color::White);
                    iter->options[i]->gText.setCharacterSize(30);

                    if (iter->back != NULL)
                        iter->options[i]->gText.setPosition(SCREEN_WIDTH/2 - 30,(SCREEN_HEIGHT/2)/(iter->nr_of_menus + 1) * i + SCREEN_HEIGHT/3);
                    else
                        iter->options[i]->gText.setPosition(SCREEN_WIDTH/2 - 30,(SCREEN_HEIGHT/2)/iter->nr_of_menus * i + SCREEN_HEIGHT/3);

                    iter->options[i]->gText.setFont(font);
                }

                if (iter->back != NULL) {
                    iter->back->gText.setString("Back");
                    iter->back->gText.setFillColor(sf::Color::White);
                    iter->back->gText.setCharacterSize(30);
                    iter->back->gText.setFont(font);
                    iter->back->gText.setPosition(SCREEN_WIDTH/2 - 30, (SCREEN_HEIGHT/2)/(iter->nr_of_menus + 1) * iter->nr_of_menus + (SCREEN_HEIGHT/3));

                    if (sel < 0)
                        sel = iter->nr_of_menus;
                    if (sel > iter->nr_of_menus)
                        sel = 0;

                    if (sel != iter->nr_of_menus)
                        iter->options[sel]->gText.setFillColor(sf::Color::Red);
                    else
                        iter->back->gText.setFillColor(sf::Color::Red);

                } else {
                    if (sel < 0)
                        sel = iter->nr_of_menus - 1;
                    if (sel > iter->nr_of_menus - 1)
                        sel = 0;

                    iter->options[sel]->gText.setFillColor(sf::Color::Red);
                }





                window->clear();

                for (int i = 0; i < iter->nr_of_menus; i++)
                    window->draw(iter->options[i]->gText);

                if (iter->back != NULL)
                    window->draw(iter->back->gText);

                window->display();
            }
        } else {
            //                                          CLI-ben inditva
            //----------------------------------------------------------------------------------------------------------
            std::fstream file;
            file.open("maps.conf");
            std::string fileLine;

            std::cout << "Maps to play:" << std::endl;

            do {
                std::getline(file,fileLine);
                if (!fileLine.empty())
                    std::cout << fileLine << std::endl;
                else break;
            } while(!file.eof());

            std::cout << "To start playing just type in the name of a map! (to quit type \"quit\")" << std::endl;
            std::string line = "";
            std::cin >> line;
            if (line.find("quit") != std::string::npos)
                return;
            else
                startCLIGame(line.c_str());
        }
    } catch (std::exception& ex) {
        std::cerr << "Something went wrong: " << ex.what() << std::endl;
    }
}

//                                        Game - loadSettings
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::loadSettings() {
    std::fstream keyCodes;
    keyCodes.open("controls.conf");
    std::string line = "";

    do {
        std::getline(keyCodes,line);
        if (line.find("moveForward") != std::string::npos)
            bindings[0] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "moveForward=\"", "\"")));
        if (line.find("moveBackward") != std::string::npos)
            bindings[1] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "moveBackward=\"", "\"")));
        if (line.find("turnLeft") != std::string::npos)
            bindings[2] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "turnLeft=\"", "\"")));
        if (line.find("turnRight") != std::string::npos)
            bindings[3] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "turnRight=\"", "\"")));
        if (line.find("shoot") != std::string::npos)
            bindings[4] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "shoot=\"", "\"")));
        if (line.find("openMap") != std::string::npos)
            bindings[5] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "openMap=\"", "\"")));
        if (line.find("toggleFullscreen") != std::string::npos)
            bindings[6] = static_cast<sf::Keyboard::Key>(StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line, "toggleFullscreen=\"", "\"")));
        if (line.find("screenWidth") != std::string::npos)
            SCREEN_WIDTH = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"screenWidth=\"","\""));
        if (line.find("screenHeight") != std::string::npos)
            SCREEN_HEIGHT = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"screenHeight=\"","\""));

        if (line.find("resolution") != std::string::npos) {
            screenWidth = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"resolution=\"","x"));
            screenHeight = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"x","\""));
        }

    } while(!keyCodes.eof());

    bindings[9] = sf::Keyboard::Escape;
}

//                                        Game - startGraphicalGame
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::startGraphicalGame(const char* mapName, Point resolution, Point screenSize) {
    bool isPlayerAlive = true;
    bool fullscreen = false;

    int OSW = SCREEN_WIDTH;
    int OSH = SCREEN_HEIGHT;

    //Cel ahova el kell jutni
    int wherex;
    int wherey;
    winCondition(mapName,wherex,wherey);

    SCREEN_WIDTH = screenSize.x;
    SCREEN_HEIGHT = screenSize.y;

    screenWidth = resolution.x;
    screenHeight = resolution.y;

    //ShowMap
    bool mapShown = false;
    std::string displayMapPath = mapName;
    displayMapPath += "/textures/display_map.png";
    sf::Texture displayMap;
    sf::Texture displayMapConst;

    displayMap.loadFromFile(displayMapPath);
    displayMapConst.loadFromFile(displayMapPath);

    sf::RenderStates mapStates;
    mapStates.texture = &displayMap;
    sf::VertexArray showMap;
    showMap.setPrimitiveType(sf::Quads);
    showMap.resize(4);

    showMap[0].texCoords = sf::Vector2f(0,0);
    showMap[1].texCoords = sf::Vector2f(displayMap.getSize().x,0);
    showMap[2].texCoords = sf::Vector2f(displayMap.getSize().x,displayMap.getSize().y);
    showMap[3].texCoords = sf::Vector2f(0,displayMap.getSize().y);

    showMap[0].position = sf::Vector2f(0,0);
    showMap[1].position = sf::Vector2f(SCREEN_WIDTH,0);
    showMap[2].position = sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT);
    showMap[3].position = sf::Vector2f(0,SCREEN_HEIGHT);

    if (window == NULL)
        window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DoomCopy!",sf::Style::Titlebar | sf::Style::Close);
    else {
        window->setSize(sf::Vector2u(SCREEN_WIDTH,SCREEN_HEIGHT));
    }

    sf::VertexArray screen;
    screen.setPrimitiveType(sf::Quads);
    screen.resize(screenWidth*3*4);

    verteces.rows = 3;
    verteces.columns = screenWidth;
    verteces.data = new sf::Vertex**[verteces.rows];
    for (int i = 0; i < verteces.rows; i++) {
        verteces.data[i] = new sf::Vertex*[verteces.columns];
    }

    for (int i = 0; i < screenWidth; i++) {
        for (int j = 0; j < 3; j++) {
            verteces.data[j][i] = &screen[(i + j * screenWidth) * 4];
        }
    }

    std::string mapN = mapName;

    sf::Clock clock;
    sf::Event event;
    map = new Map(mapN);
    map->enemies.setDestructFunction(fnc);
    int nrOfEnemiesAtStart = map->enemies.currentSize+1;
    map->projectiles.setDestructFunction(fnc2);
    player = new Player((mapN + "/player.conf").c_str());
    player->weapon.loadWeapon(mapN);
    double fps = 1/30.0;

    sf::Text currentHP;
    currentHP.setString(std::to_string(int(player->HP)));
    currentHP.setFillColor(sf::Color::Red);
    currentHP.setPosition(0,0);
    currentHP.setFont(font);
    currentHP.setCharacterSize(30);

    //Az ora inditasa
    sf::Clock gameTime;
    bool mapDone = false;

    while(window->isOpen()) {
        clock.restart();

        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == bindings[9])
                    window->close();
                if (event.key.code == bindings[0])
                    player->move(cos(player->direction), sin(player->direction), *map);
                if (event.key.code == bindings[1])
                    player->move((-cos(player->direction)), (-sin(player->direction)), *map);
                if (event.key.code == bindings[2])
                    player->direction -= 5 * degree;
                if (event.key.code == bindings[3])
                    player->direction += 5 * degree;
                if (event.key.code == bindings[4])
                    player->weapon.gShot(*map);
                if (event.key.code == bindings[5]) {
                    mapShown = !mapShown;
                }
                if (event.key.code == bindings[6]) {
                    fullscreen = !fullscreen;
                    if (fullscreen) {
                        window->create(sf::VideoMode::getFullscreenModes()[0], "DoomCopy!", sf::Style::Fullscreen);
                        SCREEN_WIDTH = window->getSize().x;
                        SCREEN_HEIGHT = window->getSize().y;
                    } else {
                        SCREEN_WIDTH = OSW;
                        SCREEN_HEIGHT = OSH;
                        window->create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DoomCopy!",sf::Style::Titlebar | sf::Style::Close);
                    }
                }
            }
        }

        if (player->direction >= M_PI) player->direction -= 2 * M_PI;
        if (player->direction <= -M_PI) player->direction += 2 * M_PI;

        if ((int(player->getPosX()) == wherex) && (int(player->getPosY()) == wherey)) {
            mapDone = true;
            break;
        }

        //Szornyek frissitese
        ListItem<Creature*>* iterEnemy = map->enemies.getHead();
        while(iterEnemy != NULL) {
            iterEnemy->item->update(*map,*player);
            iterEnemy = iterEnemy->next;
        }

        //Lovedekek frissitese
        ListItem<Projectile*>* iterProjectile = map->projectiles.getHead();
        while(iterProjectile != NULL) {
            iterProjectile->item->update(*map,*player);
            iterProjectile = iterProjectile->next;
        }

        //Nem letezo entitasok torlese
        deleteDeadOrNonExistent();

        renderWalls();
        renderEnemies();
        renderProjectiles();
        renderWeapon();
        map->enemies.sort(cmp);

        if (player->HP <= 0) {
            isPlayerAlive = false;
            break;
        }

        currentHP.setString(std::to_string(int(player->HP)));

        window->clear();

        if (!mapShown) {
            //Falak kirajzolasa
            window->draw(screen,map->text.states);

            //Szornyek kirajzolasa
            iterEnemy = map->enemies.getHead();
            while(iterEnemy != NULL) {
                if (iterEnemy->item->visible) {
                    window->draw(iterEnemy->item->vertexArray,iterEnemy->item->text.states);
                }
                iterEnemy = iterEnemy->next;
            }

            //Lovedekek kirajzolasa
            iterProjectile = map->projectiles.getHead();
            while(iterProjectile != NULL) {
                if (iterProjectile->item->visible)
                    window->draw(iterProjectile->item->vertexArray,iterProjectile->item->type.text.states);
                iterProjectile = iterProjectile->next;
            }

            //Fegyver kirajzolasa
            window->draw(player->weapon.vertexArray,player->weapon.texture.states);
            window->draw(currentHP);
        } else {
            sf::Uint8 playerColor(0);
            sf::Uint8 whereToGo(255);
            displayMap.update(&playerColor,1,1,int(player->getPosX()),int(player->getPosY()));
            displayMap.update(&whereToGo,1,1,wherex,wherey);
            window->draw(showMap,mapStates);
            displayMap.update(displayMapConst);
        }

        window->display();

        sf::Time elapsedTime = clock.getElapsedTime();
        double waitTime = ((fps) - elapsedTime.asSeconds());
        sf::Time wait = sf::seconds(waitTime);
        sf::sleep(wait);
    }

    //Ha a celba ert a jatekos
    //Score szamitasa
    //Fajlba irasa
    if (mapDone) {
        DoomCopy::List<int> list;
        int score = 1500;

        score -= int(gameTime.getElapsedTime().asSeconds());
        score += int((nrOfEnemiesAtStart - map->enemies.currentSize) * 100);

        std::fstream file;
        std::string line = "";
        file.open(mapN + "/scores.txt");
        int lineNr = 0;

        do {
            std::getline(file,line);
            if (!line.empty()) {
                list.addItem(int(DoomCopy::StringManager::string_to_double(line)));
                lineNr++;
            } else
                break;
        } while(!file.eof() && (lineNr < 10));

        list.addItem(score);
        list.sort(scoreCmpr);

        std::ofstream output;
        output.open(mapN + "/scores.txt");

        if (lineNr != 0) {
            if (list.currentSize < 10) {
                for (int i = 0; i < list.currentSize + 1; i++)
                    output << list.at(i) << "\n";
            } else {
                for (int i = 0; i < 10; i++)
                    output << list.at(i) << "\n";
            }
        } else {
            output << list.at(0);
        }

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(30);
        text.setPosition(SCREEN_WIDTH/2.0,SCREEN_HEIGHT/2.0);

        std::string string = "Your score this game ";
        string += std::to_string(score);

        text.setString(string);

        sf::Event event;
        bool exit = false;
        while(window->isOpen()) {
            while(window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                if (event.type == sf::Event::KeyPressed) {
                    exit = true;
                }
            }

            if (exit)
                break;

            window->clear();
            window->draw(text);
            window->display();
        }

        delete map;
        delete player;
        map = NULL;
        player = NULL;
    }

    //Ha meghalt a jatekos
    if (!isPlayerAlive) {
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setPosition(SCREEN_WIDTH/2.0,SCREEN_HEIGHT/2.0);
        text.setString("You are dead");
        text.setFillColor(sf::Color::Red);

        delete map;
        delete player;
        map = NULL;
        player = NULL;

        sf::Event event;
        bool exit = false;
        while(window->isOpen()) {
            while(window->pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window->close();

                if (event.type == sf::Event::KeyPressed) {
                    exit = true;
                }
            }

            if (exit)
                break;

            window->clear();
            window->draw(text);
            window->display();
        }
    }
}

//                                        Game - renderWalls
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::renderWalls() {
    int sqSizeX = (SCREEN_WIDTH/screenWidth);
    int sqSizeY = (SCREEN_HEIGHT/screenHeight);

    for (int i = 0; i < screenWidth; i++) {
        double rayDegree = (player->direction - player->FOV/2) + (((double) i)/(double) screenWidth) * player->FOV;

        //Sugar kilovese
        double distance = Ray::distanceFromCollision(*map,Point(player->getPosX(),player->getPosY()),Point(cos(rayDegree),sin(rayDegree)),0.1,player->viewDistance);

        int ceiling = ((screenHeight/2.0) - (screenHeight/distance));
        int floor = (screenHeight - ceiling);

        double x = player->getPosX() + distance * cos(rayDegree);
        double y = player->getPosY() + distance * sin(rayDegree);

        //Annak a blokknak a kozepe, amit eltalalt a sugar
        double midX = int(x) + 0.5;
        double midY = int(y) + 0.5;

        double beta = atan2f((y - midY),(x - midX));

        //"Teto"
        //----------------------------------------------------------------------------------------------------------
        verteces.data[0][i][0].position = sf::Vector2f(i * sqSizeX,0);
        verteces.data[0][i][1].position = sf::Vector2f((i+1) * sqSizeX,0);
        verteces.data[0][i][2].position = sf::Vector2f((i+1) * sqSizeX,ceiling * sqSizeY);
        verteces.data[0][i][3].position = sf::Vector2f(i * sqSizeX, ceiling * sqSizeY);

        verteces.data[0][i][0].color = sf::Color::Black;
        verteces.data[0][i][1].color = sf::Color::Black;
        verteces.data[0][i][2].color = sf::Color::Black;
        verteces.data[0][i][3].color = sf::Color::Black;

        //Fal
        //----------------------------------------------------------------------------------------------------------
        verteces.data[1][i][0].position = sf::Vector2f(i * sqSizeX, ceiling * sqSizeY);
        verteces.data[1][i][1].position = sf::Vector2f((i+1) * sqSizeX,ceiling * sqSizeY);
        verteces.data[1][i][2].position = sf::Vector2f((i+1) * sqSizeX,floor * sqSizeY);
        verteces.data[1][i][3].position = sf::Vector2f(i * sqSizeX, floor * sqSizeY);

        Point size = map->text.getTextureSize();
        double pixelX = 0;

        beta /= degree;

        if (beta >= -45 && beta < 45) {
            pixelX = (y - int(y)) * size.x;
        }
        if (beta >= 45 && beta < 135) {
            pixelX = (x - int(x)) * size.x;
        }
        if (beta < -45 && beta >= -135) {
            pixelX = (x - int(x)) * size.x;
        }
        if (beta >= 135 || beta < -135) {
            pixelX = (y - int(y)) * size.x;
        }

        std::string textureName = map->blocks.getTextureName(map->data[int(y)][int(x)]);
        Point extra = map->text.sampleFrom(textureName);

        verteces.data[1][i][0].texCoords = sf::Vector2f(pixelX + int(extra.x), 0 + int(extra.y));
        verteces.data[1][i][1].texCoords = sf::Vector2f(pixelX + int(extra.x), 0 + int(extra.y));
        verteces.data[1][i][2].texCoords = sf::Vector2f(pixelX + int(extra.x), int(extra.y) + size.y);
        verteces.data[1][i][3].texCoords = sf::Vector2f(pixelX + int(extra.x), int(extra.y) + size.y);

        //Talaj/padlo
        //----------------------------------------------------------------------------------------------------------
        verteces.data[2][i][0].position = sf::Vector2f(i * sqSizeX,floor * sqSizeY);
        verteces.data[2][i][1].position = sf::Vector2f((i+1) * sqSizeX,floor * sqSizeY);
        verteces.data[2][i][2].position = sf::Vector2f((i+1) * sqSizeX,(screenHeight - 1) * sqSizeY);
        verteces.data[2][i][3].position = sf::Vector2f(i * sqSizeX, (screenHeight - 1) * sqSizeY);

        verteces.data[2][i][0].color = sf::Color::Black;
        verteces.data[2][i][1].color = sf::Color::Black;
        verteces.data[2][i][2].color = sf::Color::Black;
        verteces.data[2][i][3].color = sf::Color::Black;
    }
}

//                                        Game - deleteDeadOrNonExistent
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::deleteDeadOrNonExistent() {
    ListItem<Creature*>* iterEnemy = map->enemies.getHead();
    int i = 0;
    while (iterEnemy !=  NULL) {
        if (!iterEnemy->item->isAlive()) {
            ListItem<Creature*>* tmp = iterEnemy->next;
            map->enemies.deleteAt(i,fnc);
            iterEnemy = tmp;
            i--;
        } else
            iterEnemy = iterEnemy->next;
        i++;
    }

    ListItem<Projectile*>* iterProjectile = map->projectiles.getHead();
    int j = 0;
    while (iterProjectile !=  NULL) {
        if (!iterProjectile->item->getStillExists()) {
            ListItem<Projectile*>* tmpP = iterProjectile->next;
            map->projectiles.deleteAt(j,fnc2);
            iterProjectile = tmpP;
            j--;
        } else
            iterProjectile = iterProjectile->next;
        j++;
    }
}

//                                        Game - renderEnemies
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::renderEnemies() {
    int sqSizeX = (SCREEN_WIDTH/screenWidth);
    int sqSizeY = (SCREEN_HEIGHT/screenHeight);

    int i = 0;
    ListItem<Creature*>* iter = map->enemies.getHead();
    while (iter != NULL) {
        double dx = iter->item->getPos().x - player->getPosX();
        double dy = iter->item->getPos().y - player->getPosY();

        double monster_degree = atan2(dy,dx);

        iter->item->visible = false;

        double distanceFromMonster = sqrt(dx * dx + dy * dy);

        iter->item->distanceFromPlayer = distanceFromMonster;

        if (((player->direction - player->FOV/2.0) <= monster_degree) && ((player->direction + player->FOV/2.0) >= monster_degree)) {
            double distanceFromBlock = Ray::distanceFromCollision(*map,Point(player->getPosX(),player->getPosY()),Point(cos(monster_degree),sin(monster_degree)),0.1,player->viewDistance);

            if ((distanceFromMonster < distanceFromBlock) && (distanceFromMonster < 32)) {
                iter->item->visible = true;

                int posW = int(((monster_degree - player->direction + player->FOV/2.0) / player->FOV) * screenWidth);

                int up = int(screenHeight/2.0 - screenHeight/distanceFromMonster);

                int blockSize = screenHeight - 2 * up;
                blockSize *= sqSizeY;

                iter->item->vertexArray[0].position = sf::Vector2f(posW * sqSizeX - blockSize/2.0,SCREEN_HEIGHT/2.0 - blockSize/2.0);
                iter->item->vertexArray[1].position = sf::Vector2f(posW * sqSizeX + blockSize/2.0,SCREEN_HEIGHT/2.0 - blockSize/2.0);
                iter->item->vertexArray[2].position = sf::Vector2f(posW * sqSizeX + blockSize/2.0,SCREEN_HEIGHT/2.0 + blockSize/2.0);
                iter->item->vertexArray[3].position = sf::Vector2f(posW * sqSizeX - blockSize/2.0,SCREEN_HEIGHT/2.0 + blockSize/2.0);

                int status = iter->item->currentStatus;

                int px = (status % 3);
                int py = int(status/3.0);

                iter->item->vertexArray[0].texCoords = sf::Vector2f(px * 32,py * 32);
                iter->item->vertexArray[1].texCoords = sf::Vector2f((px + 1) * 32,py * 32);
                iter->item->vertexArray[2].texCoords = sf::Vector2f((px + 1) * 32,(py + 1) * 32);
                iter->item->vertexArray[3].texCoords = sf::Vector2f(px * 32,(py + 1) * 32);
            }
        }

        iter = iter->next;
    }
}

//                                        Game - renderProjectiles
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::renderProjectiles() {
    int sqSizeX = (SCREEN_WIDTH/screenWidth);
    int sqSizeY = (SCREEN_HEIGHT/screenHeight);

    int i = 0;
    ListItem<Projectile*>* iter = map->projectiles.getHead();
    while (iter != NULL) {

        iter->item->visible = false;

        double dx = iter->item->currenPosition.x - player->getPosX();
        double dy = iter->item->currenPosition.y - player->getPosY();

        double projectile_degree = atan2(dy,dx);

        if (((player->direction - player->FOV/2.0) <= projectile_degree) && ((player->direction + player->FOV/2.0) >= projectile_degree)) {
            double distanceFromBlock = Ray::distanceFromCollision(*map,Point(player->getPosX(),player->getPosY()),Point(cos(projectile_degree),sin(projectile_degree)),0.1,player->viewDistance);
            double distanceFromProjectile = sqrt(dx*dx + dy*dy);

            //Ha ez igaz, akkor rajzolunk ki projectilet
            if (distanceFromBlock > distanceFromProjectile) {
                iter->item->visible = true;

                double dir = atan2(iter->item->direction.y,iter->item->direction.x);

                int posW = int(((projectile_degree - player->direction + player->FOV/2.0) / player->FOV) * screenWidth);

                int up = int(screenHeight/2.0 - screenHeight/distanceFromProjectile);

                int blockSize = screenHeight - 2 * up;
                blockSize *= sqSizeY;

                iter->item->vertexArray[0].position = sf::Vector2f(posW * sqSizeX - blockSize/2.0,SCREEN_HEIGHT/2.0 - blockSize/2.0);
                iter->item->vertexArray[1].position = sf::Vector2f(posW * sqSizeX + blockSize/2.0,SCREEN_HEIGHT/2.0 - blockSize/2.0);
                iter->item->vertexArray[2].position = sf::Vector2f(posW * sqSizeX + blockSize/2.0,SCREEN_HEIGHT/2.0 + blockSize/2.0);
                iter->item->vertexArray[3].position = sf::Vector2f(posW * sqSizeX - blockSize/2.0,SCREEN_HEIGHT/2.0 + blockSize/2.0);

                iter->item->vertexArray[0].texCoords = sf::Vector2f(0,0);
                iter->item->vertexArray[1].texCoords = sf::Vector2f(32,0);
                iter->item->vertexArray[2].texCoords = sf::Vector2f(32,32);
                iter->item->vertexArray[3].texCoords = sf::Vector2f(0,32);
            }
        }

        iter = iter->next;
    }
}

//                                        Game - renderWeapon
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::renderWeapon() {
    player->weapon.vertexArray[0].position = sf::Vector2f(0,0);
    player->weapon.vertexArray[1].position = sf::Vector2f(SCREEN_WIDTH,0);
    player->weapon.vertexArray[2].position = sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT);
    player->weapon.vertexArray[3].position = sf::Vector2f(0,SCREEN_HEIGHT);

    int px = int(player->weapon.currentState % 3);
    int py = int(player->weapon.currentState / 3.0);

    player->weapon.vertexArray[0].texCoords = sf::Vector2f(px * 32, py * 32);
    player->weapon.vertexArray[1].texCoords = sf::Vector2f((px + 1) * 32, py * 32);
    player->weapon.vertexArray[2].texCoords = sf::Vector2f((px + 1) * 32, (py + 1) * 32);
    player->weapon.vertexArray[3].texCoords = sf::Vector2f(px * 32, (py + 1) * 32);

    player->weapon.updateState();
}

//                                        Game - winCondition
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::winCondition(std::string mapName, int& x, int& y) {
    std::fstream file;
    file.open(mapName +  "/whereto.conf");
    std::string line = "";
    std::getline(file,line);

    x = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"posX=\"","\""));
    y = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"posY=\"","\""));
}

//                                          NUMPAD
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::numpad(sf::RenderWindow *window, int *variableToSaveInto, std::string textToWriteOut) {
    bool done = false;
    sf::Event event;
    List<int> int_list;
    int listnr = 0;

    sf::Font font;
    if (!font.loadFromFile("FunSized.ttf")) {
        if (!font.loadFromFile("Roboto-Regular.ttf")) {
            font.loadFromFile("advanced_pixel-7.ttf");
        }
    }

    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::KeyPressed) {

                if (event.key.code == sf::Keyboard::Escape)
                    window->close();

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
                    *variableToSaveInto = screenWidth;
                    done = true;
                }
            }
        }

        sf::Text text;
        std::string string = textToWriteOut;
        for (int i = 0; i < listnr; i++)
            string += std::to_string(int_list.at(i));

        text.setString(string);
        text.setPosition(100,100);
        text.setCharacterSize(75);
        text.setFont(font);
        text.setFillColor(sf::Color::White);

        window->clear();
        window->draw(text);
        window->display();

        if (done)
            break;

    }
}

//                                        Game - startCLIGame
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Game::startCLIGame(const char *mapName) {
    bool isPlayerAlive = true;

    //Cel ahova el kell jutni
    int wherex;
    int wherey;
    winCondition(mapName,wherex,wherey);

    std::string mapN = mapName;
    map = new Map(mapN);
    map->enemies.setDestructFunction(fnc);
    int nrOfEnemiesAtStart = map->enemies.currentSize+1;
    map->projectiles.setDestructFunction(fnc2);
    player = new Player((mapN + "/player.conf").c_str());
    player->weapon.loadWeapon(mapN);
    bool mapDone = false;

    map->CLIMap.data[wherey][wherex] = 'F';

    ListItem<Creature*>* iterEnemy = map->enemies.getHead();
    while(iterEnemy != NULL) {
        iterEnemy->item->setSpeed(10);
        iterEnemy = iterEnemy->next;
    }

    int aim = 0;

    while(!mapDone && isPlayerAlive) {
        char line[100];
        std::cin.getline(line, sizeof(line));

        if (command(line, mapDone, aim)) {
            //Szornyek frissitese
            ListItem<Creature*>* iterEnemy = map->enemies.getHead();
            while(iterEnemy != NULL) {
                iterEnemy->item->update(*map,*player);
                if(iterEnemy->item->distanceFromPlayer <= 1) {
                    player->HP -= 5;
                    std::cout << "You've taken " << 5 << " damage from a nearby monster" << std::endl;
                }
                iterEnemy = iterEnemy->next;
            }

            map->enemies.sort(cmp);
        } else {

        }

        if (player->direction >= M_PI) player->direction -= 2 * M_PI;
        if (player->direction <= -M_PI) player->direction += 2 * M_PI;

        if ((int(player->getPosX()) == wherex) && (int(player->getPosY()) == wherey)) {
            mapDone = true;
            break;
        }

        //Nem letezo/halott dolgok torlese
        deleteDeadOrNonExistent();

        if (player->HP <= 0) {
            std::cout << "You are dead!" << std::endl;
            isPlayerAlive = false;
            break;
        }
    }
}

//                                        Game - command
//----------------------------------------------------------------------------------------------------------------------
bool DoomCopy::Game::command(const std::string& cmd, bool& exit, int& aim) {
    //move command
    if (cmd.find("move") != std::string::npos) {

        if (cmd.find("up") != std::string::npos) {
            player->move(0,-1,*map);
        } else if (cmd.find("down") != std::string::npos) {
            player->move(0,1,*map);
        } else if (cmd.find("left") != std::string::npos) {
            player->move(-1,0,*map);
        } else if (cmd.find("right") != std::string::npos) {
            player->move(1,0,*map);
        }

        std::cout << player->getPosX() << " " << player->getPosY() << std::endl;

        return true;

    //shoot command
    } else if (cmd.find("shoot") != std::string::npos) {
        if (map->enemies.getHead() != NULL) {
            if ((aim <= map->enemies.currentSize) && (aim >= 0))
                if (map->enemies.at(aim)->distanceFromPlayer < player->weapon.range) {
                    map->enemies.at(aim)->damage(player->weapon.type.dmg);
                    std::cout << aim << ". Monster took " << player->weapon.type.dmg << std::endl;
                    std::cout << aim << "\'s hp: " << map->enemies.at(aim)->getHP() << std::endl;
                } else
                    std::cout << aim << ". seems to be out of range." << std::endl;
        }

        return true;

    //listmonsters command
    } else if ((cmd.find("listmonsters") != std::string::npos) || (cmd.find("Listmonsters") != std::string::npos)) {
        std::cout << "Monsters:" << std::endl;
        if (map->enemies.getHead() != NULL) {
            for (int i = 0; i < map->enemies.currentSize + 1; i++)
                std::cout << i << ". " << map->enemies.at(i)->getPos().x << " " << map->enemies.at(i)->getPos().y << std::endl;
        } else
            std::cout << "None alive" << std::endl;

        return false;

    //printmap command
    } else if ((cmd.find("printmap") != std::string::npos) || (cmd.find("Printmap") != std::string::npos)) {
        char* tmp;
        if (map->enemies.getHead() != NULL) {
            tmp = new char[map->enemies.currentSize+1];
            for (int i = 0; i < map->enemies.currentSize+1; i++) {
                tmp[i] = map->CLIMap.data[int(map->enemies.at(i)->getPos().y)][int(map->enemies.at(i)->getPos().x)];
                map->CLIMap.data[int(map->enemies.at(i)->getPos().y)][int(map->enemies.at(i)->getPos().x)] = std::to_string(i).c_str()[0];
            }
        }

        for (int i = 0; i < map->rows; i++) {
            for (int j = 0; j < map->columns; j++) {
                if ((i == int(player->getPosY())) && (j == int(player->getPosX())))
                    std::cout << "@";
                else
                    std::cout << map->CLIMap.data[i][j];
            }
            std::cout << std::endl;
        }

        if (map->enemies.getHead() != NULL) {
            for (int i = 0; i < map->enemies.currentSize+1; i++) {
                map->CLIMap.data[int(map->enemies.at(i)->getPos().y)][int(map->enemies.at(i)->getPos().x)] = tmp[i];
            }
            delete[] tmp;
        }

        return false;

    //quit command
    } else if ((cmd.find("quit") != std::string::npos) || (cmd.find("Quit") != std::string::npos)) {
        exit = true;
        return false;

    //aim command
    } else if (cmd.find("aim") != std::string::npos) {
        std::string c = cmd;
        c += "\"";
        aim = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(c,"aim ","\""));
        return false;

    //hp command
    } else if (cmd.find("hp") != std::string::npos) {
        std::cout << player->HP << std::endl;
    }

    return false;
}