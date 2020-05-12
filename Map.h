//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_MAP_H
#define DOOMCOPY_MAP_H

#include "Array2D.h"
#include "List.h"
#include "BlockType.h"
#include "Creature.h"
#include "Projectile.h"

namespace DoomCopy {
    class Map : public Array2D<int> {
    public:
        Texture text;
        Blocks blocks;
        List<Creature*> enemies;
        List<Projectile*> projectiles;

        Map() : text(32,32) {}
        Map(std::string pathToMap);
        void load(std::string pathToMap);
        void loadEnemies(std::string pathToMap);

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
        }
    };

    class Ray {
    public:
        static double distanceFromCollision(const Map& map, Point source, Point direction, double stepSize, double maxDistance);
    };

    double inline Ray::distanceFromCollision(const Map &map, Point source, Point direction, double stepSize, double maxDistance) {
        double raySize = 0;

        while(raySize < maxDistance) {
            raySize += stepSize;

            int x = source.x + (raySize*direction.x);
            int y = source.y + (raySize*direction.y);

            if (map.blocks.isTypeSolid(map.data[y][x])) {
                //double distance = raySize * sqrt(dx*dx + dy*dy);
                //ami valójában raysize * 1, szal raysize...
                return raySize;
            }

        }

        if (raySize >= maxDistance)
            return maxDistance;
        return maxDistance;
    }
}

#endif //DOOMCOPY_MAP_H
