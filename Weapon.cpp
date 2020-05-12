//
// Created by coldus on 5/10/20.
//

#include <fstream>
#include "Weapon.h"

bool DoomCopy::Weapon::loadWeapon(std::string path) {
    std::string line = "";
    std::ifstream file;
    file.open(path + "/weapon.conf");
    do {
        std::getline(file,line);

        if (line.find("ProjectileType") != std::string::npos) {
            //std::cout << "loading projectiles for sure" << std::endl;
            type.loadProjectileType(path,line);
        } else {
            fireRate = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"fireRate=\"","\""));
            range = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"range=\"","\""));

            std::string pathToDefaultTexture = StringManager::get_substring_btwn_first_and_next(line,"pathToIdle=\"","\"");
            texture.addImg((path + "/" + pathToDefaultTexture).c_str(),StringManager::get_substring_btwn_last_occurences(pathToDefaultTexture,"/",".").c_str());

            std::string pathToShootTexture= StringManager::get_substring_btwn_first_and_next(line,"pathToActive=\"","\"");
            texture.addImg((path + "/" + pathToShootTexture).c_str(),StringManager::get_substring_btwn_last_occurences(pathToShootTexture,"/",".").c_str());
        }
    } while(!file.eof());

    return true;
}

void DoomCopy::Weapon::gShot(Map &map) {
    if (clock.getElapsedTime().asSeconds() >= fireRate) {
        currentState = shoot;
        map.projectiles.addItem(new Projectile(type,*ownerPos,Point(cos(*ownerDir),sin(*ownerDir))));
        clock.restart();
    }
}

