//
// Created by coldus on 5/8/20.
//

#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System.hpp>
#include "Array2D.h"
#include "Creature.h"
#include "Player.h"
#include "Ray.h"

void DoomCopy::Game::startGraphicalGame(const char* mapName, Point resolution, Point screenSize) {
    SCREEN_WIDTH = screenSize.x;
    SCREEN_HEIGHT = screenSize.y;

    screenWidth = resolution.x;
    screenHeight = resolution.y;

    if (window != NULL)
        delete window;

    window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "DoomCopy!",sf::Style::Titlebar | sf::Style::Close);

    sf::VertexArray screen;
    screen.setPrimitiveType(sf::Quads);
    screen.resize(screenWidth*3*4);

    //verteces = Array2D<sf::Vertex*>(3,screenWidth);
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


    sf::Clock clock;
    sf::Event event;
    map = new Map("textures/mapV1.png","blockType.conf");
    player = new Player(10,10,45*degree,0,1,108);
    player->weapon.loadWeapon("weapon.conf");
    double fps = 1/30.0;

    while(window->isOpen()) {
        clock.restart();

        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                else if (event.key.code == sf::Keyboard::A)
                    player->direction -= 5*degree;
                else if (event.key.code == sf::Keyboard::D)
                    player->direction += 5*degree;
                else if (event.key.code == sf::Keyboard::W) {
                    player->move(cos(player->direction),sin(player->direction),*map);
                } else if (event.key.code == sf::Keyboard::S) {
                    player->move((-cos(player->direction)), (-sin(player->direction)), *map);
                } else if (event.key.code == sf::Keyboard::Q) {
                    player->weapon.gShot(*map);
                }
            }
        }

        if (player->direction >= M_PI) player->direction -= 2 * M_PI;
        if (player->direction <= -M_PI) player->direction += 2 * M_PI;

        //Updating enemies
        ListItem<Creature*>* iterEnemy = map->enemies.getHead();
        while(iterEnemy != NULL) {
            iterEnemy->item->update(*map,*player);
            iterEnemy = iterEnemy->next;
        }

        //Updating enemies
        ListItem<Projectile*>* iterProjectile = map->projectiles.getHead();
        while(iterProjectile != NULL) {
            iterProjectile->item->update(*map,*player);
            iterProjectile = iterProjectile->next;
        }

        //Deleting stuff from the list
        deleteDeadOrNonExistent();

        renderWalls();
        renderEnemies();
        renderProjectiles();
        renderWeapon();
        map->enemies.sort(cmp);

        window->clear();

        //Drawing walls
        window->draw(screen,map->text.states);

        //Drawing enemies
        iterEnemy = map->enemies.getHead();
        while(iterEnemy != NULL) {
            if (iterEnemy->item->visible) {
                window->draw(iterEnemy->item->vertexArray,iterEnemy->item->text.states);
            }
            iterEnemy = iterEnemy->next;
        }

        //Drawing projectiles
        iterProjectile = map->projectiles.getHead();
        while(iterProjectile != NULL) {
            if (iterProjectile->item->visible)
                window->draw(iterProjectile->item->vertexArray,iterProjectile->item->type.text.states);
            iterProjectile = iterProjectile->next;
        }

        //Drawing weapon
        window->draw(player->weapon.vertexArray,player->weapon.texture.states);

        window->display();

        sf::Time elapsedTime = clock.getElapsedTime();
        double waitTime = ((fps) - elapsedTime.asSeconds());
        sf::Time wait = sf::seconds(waitTime);
        sf::sleep(wait);
    }
}

void DoomCopy::Game::renderWalls() {
    int sqSizeX = (SCREEN_WIDTH/screenWidth);
    int sqSizeY = (SCREEN_HEIGHT/screenHeight);

    for (int i = 0; i < screenWidth; i++) {
        double rayDegree = (player->direction - player->FOV/2) + (((double) i)/(double) screenWidth) * player->FOV;

        double distance = Ray::distanceFromCollision(*map,Point(player->getPosX(),player->getPosY()),Point(cos(rayDegree),sin(rayDegree)),0.1,player->viewDistance);

        int ceiling = ((screenHeight/2.0) - (screenHeight/distance));
        int floor = (screenHeight - ceiling);

        double x = player->getPosX() + distance * cos(rayDegree);
        double y = player->getPosY() + distance * sin(rayDegree);

        //the midpoint of the wall that has been hit
        double midX = int(x) + 0.5;
        double midY = int(y) + 0.5;

        double beta = atan2f((y - midY),(x - midX));

        //Ceiling
        //----------------------------------------------------------------------------------------------------------
        verteces.data[0][i][0].position = sf::Vector2f(i * sqSizeX,0);
        verteces.data[0][i][1].position = sf::Vector2f((i+1) * sqSizeX,0);
        verteces.data[0][i][2].position = sf::Vector2f((i+1) * sqSizeX,ceiling * sqSizeY);
        verteces.data[0][i][3].position = sf::Vector2f(i * sqSizeX, ceiling * sqSizeY);

        verteces.data[0][i][0].color = sf::Color::Black;
        verteces.data[0][i][1].color = sf::Color::Black;
        verteces.data[0][i][2].color = sf::Color::Black;
        verteces.data[0][i][3].color = sf::Color::Black;

        //Wall
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

        //Floor
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

void fnc(DoomCopy::Creature* cre) {
    delete cre;
}

void fnc2(DoomCopy::Projectile* pro) {
    delete pro;
}

void DoomCopy::Game::deleteDeadOrNonExistent() {
    ListItem<Creature*>* iterEnemy = map->enemies.getHead();
    int i = 0;
    while (iterEnemy !=  NULL) {
        //std::cout << i << ".dik szörny hpja: " << iterEnemy->item->getHP() << std::endl;
        if (!iterEnemy->item->isAlive()) {
            ListItem<Creature*>* tmp = iterEnemy->next;
            map->enemies.deleteAt(i,fnc);
            iterEnemy = tmp;
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
            j++;
        } else
            iterProjectile = iterProjectile->next;
    }
}

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

void DoomCopy::Game::renderProjectiles() {
    int sqSizeX = (SCREEN_WIDTH/screenWidth);
    int sqSizeY = (SCREEN_HEIGHT/screenHeight);

    int i = 0;
    ListItem<Projectile*>* iter = map->projectiles.getHead();
    while (iter != NULL) {

        iter->item->visible = false;
        //std::cout << "Projectile pos " << iter->item->currenPosition.x << " " << iter->item->currenPosition.y << std::endl;

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