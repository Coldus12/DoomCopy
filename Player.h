//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_PLAYER_H
#define DOOMCOPY_PLAYER_H

#include "Point.h"
#include "Map.h"
#include "Weapon.h"

namespace DoomCopy {

    class Player {
        Point position;
    public:
        Weapon weapon;
        double HP = 100;
        double FOV;
        double direction;
        double speed;
        double viewDistance;

        Player(double x, double y) {
            position.x = x;
            position.y = y;
        }

        Player(double x, double y, double FOV, double direction, double speed, double viewDistance) {
            position.x = x;
            position.y = y;
            this->FOV = FOV;
            this->direction = direction;
            this->speed = speed;
            this->viewDistance = viewDistance;
            //weapon.set(&position,&direction);
        }

        void move(double relativeX, double relativY, const DoomCopy::Map& map);
        void setPosX(double nPosX) {position.x = nPosX;}
        void setPosY(double nPosY) {position.y = nPosY;}
        void setPosX(double nPosX, const DoomCopy::Map& map);
        void setPosY(double nPosY, const DoomCopy::Map& map);

        double getPosX() {return position.x;}
        double getPosY() {return position.y;}
    };
}

#endif //DOOMCOPY_PLAYER_H
