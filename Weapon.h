//
// Created by coldus on 5/10/20.
//

#ifndef DOOMCOPY_WEAPON_H
#define DOOMCOPY_WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include "Map.h"

namespace DoomCopy {

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

        sf::VertexArray vertexArray;

        Weapon() : texture(32,32) {
            vertexArray = sf::VertexArray(sf::Quads,4);
        }

        Weapon(const Point* ownerPos, const double* ownerDirection) : texture(32,32), ownerPos(ownerPos), ownerDir(ownerDirection) {
            clock.restart();
            vertexArray = sf::VertexArray(sf::Quads,4);
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
