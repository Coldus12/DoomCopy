//
// Created by coldus on 5/8/20.
//
#include <fstream>
#include "Player.h"

//                                           Player - move
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Player::move(double relativeX, double relativY, const DoomCopy::Map& map) {
    try {
        int x = (position.x + relativeX);
        int y = (position.y + relativY);
        int oX = position.x;
        int oY = position.y;

        if (!(map.blocks.isTypeSolid(map.data[y][x]) || map.blocks.isTypeSolid(map.data[oY][x]) || map.blocks.isTypeSolid(map.data[y][oX]) || map.blocks.isTypeSolid(map.data[oY][oX]))) {
            position.x += relativeX;
            position.y += relativY;
        }
    } catch (std::exception& ex) {
        std::cerr << "An error occured while the player was trying to move. The error message: " << ex.what() << std::endl;
    }
}

//                                          Player - setPosX
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Player::setPosX(double nPosX, const DoomCopy::Map& map) {
    int x = nPosX;
    int y = position.y;
    try {
        if (!map.blocks.isTypeSolid(map.data[y][x])) setPosX(nPosX);
    } catch (std::exception& ex) {
        std::cerr << "An error occured while changing the player's x coordinate: " << ex.what() << std::endl;
    }
}

//                                          Player - setPosY
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Player::setPosY(double nPosY, const DoomCopy::Map& map) {
    int x = position.x;
    int y = nPosY;
    try {
        if (!map.blocks.isTypeSolid(map.data[y][x])) setPosY(nPosY);
    } catch (std::exception& ex) {
        std::cerr << "An error occured while changing the player's y coordinate: " << ex.what() << std::endl;
    }
}

//                             Player - konfiguracios fajl fele konstruktor
//----------------------------------------------------------------------------------------------------------------------
DoomCopy::Player::Player(const char *conf) {
    try {
        std::fstream file;
        file.open(conf);
        std::string line = "";
        std::getline(file,line);

        position.x = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"posX=\"","\""));
        position.y = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"posY=\"","\""));
        FOV = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"FOV=\"","\""));
        //speed = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"speed=\"","\""));
        viewDistance = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"viewDistance=\"","\""));
        direction = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"direction=\"","\""));

        weapon.set(&position, &direction);
    } catch (std::exception& ex) {
        std::cerr << "An error occured while loading the player from its configuration file: " << ex.what() << std::endl;

        position.x = 0;
        position.y = 0;
        FOV = 45 * M_PI/180.0;
        viewDistance = 108;
        direction = 0;
        weapon.set(&position, &direction);
    }
}