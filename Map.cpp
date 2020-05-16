//
// Created by coldus on 5/8/20.
//

#include <fstream>
#include "Array2D.h"
#include "Map.h"
#include "StringManager.h"
#include "MeleeEnemy.h"
#include "Projectile.h"

DoomCopy::Map::Map(std::string pathToMap) : Array2D<int>(2,2), text(32,32) {
    load(pathToMap);
}

void DoomCopy::Map::load(std::string pathToMap) {
    sf::Image img;
    img.loadFromFile(pathToMap + "/textures/map.png");

    this->free();

    this->rows = img.getSize().y;
    this->columns = img.getSize().x;

    this->data = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->data[i] = new int[this->columns];
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->data[i][j] = img.getPixel(j,i).toInteger();
        }
    }

    blocks.load(pathToMap, text);
    Map::loadEnemies(pathToMap);

    //CLIMap létrehozása
    CLIMap.rows = this->rows;
    CLIMap.columns = this->columns;

    CLIMap.data = new char*[CLIMap.rows];
    for (int i = 0; i < CLIMap.rows; i++) {
        CLIMap.data[i] = new char[CLIMap.columns];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (blocks.isTypeSolid(data[i][j]))
                CLIMap.data[i][j] = 'X';
            else
                CLIMap.data[i][j] = ' ';
        }
    }
}

void DoomCopy::Map::loadEnemies(std::string pathToMap) {

    std::string line = "";
    std::ifstream file;
    file.open((pathToMap + "/monsters.conf"));

    do {
        std::getline(file,line);

        if (line.find("MeleeMonster") != std::string::npos) {

            double posX = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"positionX=\"","\""));
            double posY = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"positionY=\"","\""));

            double direction = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"direction=\"","\""));
            direction *= M_PI/180.0;
            double dirX = cos(direction);
            double dirY = sin(direction);

            double dmg = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"defaultDamage=\"","\""));
            double hp = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"defaultHealth=\"","\""));
            double fov = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"fov=\"","\""));

            double viewDistance = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"viewDistance=\"","\""));
            double attackSpeed = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"attackSpeed=\"","\""));

            std::string textName = StringManager::get_substring_btwn_first_and_next(line,"textureName=\"","\"");

            enemies.addItem(new MeleeEnemy(Point(posX,posY),Point(dirX,dirY),hp,dmg,attackSpeed,(pathToMap + "/textures/"),textName.c_str(),fov,viewDistance));
        } else if (line.find("RangedMonster") != std::string::npos) {

        }

    }
    while (!file.eof());
}
