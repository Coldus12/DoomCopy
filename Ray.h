//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_RAY_H
#define DOOMCOPY_RAY_H

#include "Array2D.h"
#include "Map.h"

namespace DoomCopy {
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

#endif //DOOMCOPY_RAY_H
