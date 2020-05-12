//
// Created by coldus on 5/10/20.
//

#ifndef DOOMCOPY_PROJECTILE_H
#define DOOMCOPY_PROJECTILE_H

#include <SFML/System/Clock.hpp>
#include "List.h"
#include "Creature.h"
#include "StringManager.h"

namespace DoomCopy {
    class Map;
    class Player;

    class ProjectileType {
    public:
        double dmg;
        double speed;
        double size;
        double range;
        Texture text;
        ProjectileType() : text(32,32) {}
        void loadProjectileType(std::string path, std::string line);
    };

    class cmpr {
    public:
        static Point p;

        cmpr(Point a) {
            cmpr::p = Point(a.x,a.y);
        }
        bool static nearby(Creature* t);
    };


    class Projectile {
        bool stillExists = true;
        Point src;
    public:
        bool visible = false;
        sf::Clock clock;
        ProjectileType type;
        Point direction;
        Point currenPosition;
        sf::VertexArray vertexArray;

        Projectile(ProjectileType type, Point srcPosition, Point dir) : type(type), direction(dir), src(srcPosition) {
            currenPosition.x = srcPosition.x + dir.x * type.speed/20.0;
            currenPosition.y = srcPosition.y + dir.y * type.speed/20.0;

            vertexArray = sf::VertexArray(sf::Quads,4);
            clock.restart();
        }

        bool getStillExists() {return stillExists;}

        void update(Map& map, Player& player);
    };
}

#endif //DOOMCOPY_PROJECTILE_H
