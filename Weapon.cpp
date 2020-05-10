//
// Created by coldus on 5/10/20.
//

#include <fstream>
#include "Weapon.h"
#include "StringManager.h"
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
        currentState = shoot;
        map.projectiles.addItem(new Projectile(type,*ownerPos,Point(cos(*ownerDir),sin(*ownerDir))));
        clock.restart();
    }
}

/*void DoomCopy::ProjectileType::loadProjectileType(std::string line) {
    dmg = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"damage=\"","\""));
    speed = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"speed=\"","\""));
    size = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"size=\"","\""));
    range = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"range=\"","\""));

    std::string path = StringManager::get_substring_btwn_first_and_next(line,"pathToTexture=\"","\"");

    text.addImg(path.c_str(),StringManager::get_substring_btwn_last_occurences(path,"/",".png").c_str());
}

bool DoomCopy::cmpr::nearby(DoomCopy::Creature* t) {
    return (((t->getPos().x - 0.25) <= p.x) && ((t->getPos().x + 0.25) >= p.x) && ((t->getPos().y - 0.25) <= p.y) && ((t->getPos().y + 0.25) >= p.y));
}

void DoomCopy::Projectile::update(Map &map, Player& player) {
    if (clock.getElapsedTime().asSeconds() >= 1/20.0) {
        currenPosition.x += direction.x * type.speed/20.0;
        currenPosition.y += direction.y * type.speed/20.0;

        if (map.blocks.isTypeSolid(map.data[int(currenPosition.y)][int(currenPosition.x)]))
            stillExists = false;

        cmpr cm(currenPosition);
        if (map.enemies.doesItContain(cmpr::nearby)) {
            ListItem<Creature*>* enemy =  map.enemies.pSearchBy(cmpr::nearby);
            enemy->item->damage(type.dmg);
            stillExists = false;
        }

        if (((player.getPosX() - 0.25) <= currenPosition.x) && ((player.getPosX() + 0.25) >= currenPosition.x) && ((player.getPosY() - 0.25) <= currenPosition.y) && ((player.getPosY() + 0.25) >= currenPosition.y)) {
            player.HP -= type.dmg;
            stillExists = false;
        }

        double x = currenPosition.x - src.x;
        double y = currenPosition.y - src.y;
        double d = sqrt(x*x + y*y);

        if (d >= type.range)
            stillExists = false;

        clock.restart();
    }
}

DoomCopy::Point DoomCopy::cmpr::p = Point(0,0);*/
