//
// Created by coldus on 5/10/20.
//

#include <fstream>
#include "Weapon.h"

bool DoomCopy::Weapon::loadWeapon(const char *pathToConf) {
    std::string line = "";
    std::ifstream file;
    file.open(pathToConf);
    std::getline(file, line);

    while(!file.eof()) {
        if (line.find("ProjectileType") != std::string::npos) {
            type.loadProjectileType(line);
        } else {
            fireRate = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"fireRate=\"","\""));
            range = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"range=\"","\""));

            std::string pathToDefaultTexture = StringManager::get_substring_btwn_first_and_next(line,"pathToIdle=\"","\"");
            texture.addImg(pathToDefaultTexture.c_str(),StringManager::get_substring_btwn_last_occurences(pathToDefaultTexture,"/",".").c_str());

            std::string pathToShootTexture= StringManager::get_substring_btwn_first_and_next(line,"pathToActive=\"","\"");
            texture.addImg(pathToShootTexture.c_str(),StringManager::get_substring_btwn_last_occurences(pathToShootTexture,"/",".").c_str());
        }
        std::getline(file, line);
    }

    if (line.find("ProjectileType") != std::string::npos) {
        type.loadProjectileType(line);
    } else {
        fireRate = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"fireRate=\"","\""));
        range = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"range=\"","\""));

        std::string pathToDefaultTexture = StringManager::get_substring_btwn_first_and_next(line,"pathToIdle=\"","\"");
        texture.addImg(pathToDefaultTexture.c_str(),StringManager::get_substring_btwn_last_occurences(pathToDefaultTexture,"/",".").c_str());

        std::string pathToShootTexture= StringManager::get_substring_btwn_first_and_next(line,"pathToActive=\"","\"");
        texture.addImg(pathToShootTexture.c_str(),StringManager::get_substring_btwn_last_occurences(pathToShootTexture,"/",".").c_str());
    }

    return true;
}

void DoomCopy::Weapon::gShot(Map &map) {
    if (clock.getElapsedTime().asSeconds() >= fireRate) {
        //std::cout << ownerPos->x << " " << ownerPos->y << " " << *ownerDir << std::endl;
        currentState = shoot;
        map.projectiles.addItem(new Projectile(type,*ownerPos,Point(cos(*ownerDir),sin(*ownerDir))));
        clock.restart();
    }
}

