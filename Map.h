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

    class Map : public Array2D<int> {
    public:
        Texture text;
        Blocks blocks;
        List<Creature*> enemies;

        Map() : text(32,32) {}
        Map(const char* pathToMap, const char* pathToConf);
        void load(const char* pathtoMap, const char* pathToConf);
        void loadEnemies(const char* pathToEnemyConf);

        ~Map() {
            ListItem<Creature*>* iter = enemies.getHead();
            while (iter != NULL) {
                delete iter->item;
                iter = iter->next;
            }
        }
        //std::ostream& printMap(std::ostream& os);
    };
}

#endif //DOOMCOPY_MAP_H
