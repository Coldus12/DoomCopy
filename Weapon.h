//
// Created by coldus on 5/10/20.
//

#ifndef DOOMCOPY_WEAPON_H
#define DOOMCOPY_WEAPON_H

#include "Texture.h"
#include "Projectile.h"

namespace DoomCopy {
    class Map;
    class Creature;
    class Player;

    /*class ProjectileType {
    public:
        double dmg;
        double speed;
        double size;
        double range;
        Texture text;
        ProjectileType() : text(32,32) {}
        void loadProjectileType(std::string line);
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
        sf::Clock clock;
        ProjectileType type;
        Point direction;
        Point currenPosition;

        Projectile(ProjectileType type, Point srcPosition, Point dir) : type(type), direction(direction), src(srcPosition) {
            currenPosition.x = srcPosition.x + dir.x * type.speed/20.0;
            currenPosition.y = srcPosition.y + dir.y * type.speed/20.0;
            clock.restart();
        }

        void update(Map& map, Player& player);
    };*/

    class Weapon {
        sf::Clock clock;
    public:
        enum state {
            default_state,
            shoot
        };
        state currentState = default_state;

        ProjectileType type;
        Texture texture;
        double fireRate;
        double range; //cli
        const Point* ownerPos;
        const double* ownerDir;

        Weapon() : texture(32,32) {}

        Weapon(const Point* ownerPos, const double* ownerDirection) : texture(32,32), ownerPos(ownerPos), ownerDir(ownerDirection) {
            clock.restart();
        }

        void set(const Point* ownerPos, const double* ownerDirection) {
            this->ownerPos = ownerPos;
            this->ownerDir = ownerDirection;
            clock.restart();
        }

        bool loadWeapon(const char* pathToConf);
        void gShot(Map& map);

        void updateState() {
            if (currentState == shoot)
                currentState = default_state;
        }
    };
}


#endif //DOOMCOPY_WEAPON_H
