//
// Created by coldus on 5/10/20.
//

#include <fstream>
#include "Projectile.h"
#include "Player.h"

//                                     projectiletype - loadProjectileType
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::ProjectileType::loadProjectileType(std::string path,std::string line) {
    try {
        dmg = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"damage=\"","\""));
        speed = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"speed=\"","\""));
        //size = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"size=\"","\""));
        range = StringManager::string_to_double(StringManager::get_substring_btwn_first_and_next(line,"range=\"","\""));

        path += "/" + StringManager::get_substring_btwn_first_and_next(line,"pathToTexture=\"","\"");

        text.addImg(path.c_str(),StringManager::get_substring_btwn_last_occurences(path,"/",".png").c_str());
    } catch (std::exception& ex) {
        std::cerr << "Something went wrong: " << ex.what() << std::endl;
    }
}

//                                              cmpr - nearby
//----------------------------------------------------------------------------------------------------------------------
bool DoomCopy::cmpr::nearby(DoomCopy::Creature* t) {
    return (((t->getPos().x - 0.75) <= p.x) && ((t->getPos().x + 0.75) >= p.x) && ((t->getPos().y - 0.75) <= p.y) && ((t->getPos().y + 0.75) >= p.y));
}

//                                          projectile - update
//----------------------------------------------------------------------------------------------------------------------
void DoomCopy::Projectile::update(Map &map, Player& player) {
    if (clock.getElapsedTime().asSeconds() >= 1/20.0) {
        if (stillExists) {
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
}

DoomCopy::Point DoomCopy::cmpr::p = Point(0,0);