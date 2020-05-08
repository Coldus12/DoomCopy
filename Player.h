//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_PLAYER_H
#define DOOMCOPY_PLAYER_H

#include "Array2D.h"
#include "Map.h"

namespace DoomCopy {
    class Map;

    class Player {
        double posY;
        double posX;
    public:
        double HP = 100;
        double FOV;
        double direction;
        double speed;
        double viewDistance;
        Player(double x, double y) {
            posX = x;
            posY = y;
        }

        Player(double x, double y, double FOV, double direction, double speed, double viewDistance) {
            posX = x;
            posY = y;
            this->FOV = FOV;
            this->direction = direction;
            this->speed = speed;
            this->viewDistance = viewDistance;
        }

        void move(double relativeX, double relativY, const DoomCopy::Map& map);
        void setPosX(double nPosX) {posX = nPosX;}
        void setPosY(double nPosY) {posY = nPosY;}
        void setPosX(double nPosX, const DoomCopy::Map& map);
        void setPosY(double nPosY, const DoomCopy::Map& map);

        double getPosX() {return posX;}
        double getPosY() {return posY;}
    };
}

#endif //DOOMCOPY_PLAYER_H
