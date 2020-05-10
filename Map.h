//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_MAP_H
#define DOOMCOPY_MAP_H

#include "Texture.h"
#include "BlockType.h"
#include "List.h"
#include "Creature.h"

namespace DoomCopy {
    class Creature;
    class Projectile;
    class ProjectileType;

    class Map : public Array2D<int> {
    public:
        Texture text;
        Blocks blocks;
        List<Creature*> enemies;
        //List<ProjectileType*> projectileTypes;
        List<Projectile*> projectiles;

        Map() : text(32,32) {}
        Map(const char* pathToMap, const char* pathToConf);
        void load(const char* pathtoMap, const char* pathToConf);
        void loadEnemies(const char* pathToEnemyConf);
        //void loadProjectileTypes(const char* pathToProjectileConf);

        ~Map() {
            ListItem<Creature*>* iter = enemies.getHead();
            while (iter != NULL) {
                delete iter->item;
                iter = iter->next;
            }

            ListItem<Projectile*>* iter2 = projectiles.getHead();
            while (iter2 != NULL) {
                delete iter2->item;
                iter2 = iter2->next;
            }

            /*ListItem<ProjectileType*>* iter3 = projectileTypes.getHead();
            while (iter3 != NULL) {
                delete iter3->item;
                iter3 = iter3->next;
            }*/
        }
        //std::ostream& printMap(std::ostream& os);
    };
}

#endif //DOOMCOPY_MAP_H
