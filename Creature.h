//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_CREATURE_H
#define DOOMCOPY_CREATURE_H

#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <SFML/System/Clock.hpp>
#include "Map.h"
#include "Point.h"
#include "Texture.h"
#include "Player.h"

namespace DoomCopy {
    class Map;
    class Player;

    class Creature {
    private:
        sf::Clock clock;
        sf::Clock movement;
        bool alive = true;
        double speed = 1;
        double currentHP;
        enum Status {
            run1,
            run2,
            attack1,
            attack2,
            stand,
            back
        };
    protected:
        double HP;
        Point position;
        Point directionVector;
    public:
        Status currentStatus = stand;

        bool visible = false;
        Texture text;
        sf::VertexArray vertexArray;
        double viewDistance;
        double FOV;
        double distanceFromPlayer;

        Creature(Point pos, double HP, Point direction, double FOV, double viewDistance) : position(pos), HP(HP), directionVector(direction), FOV(FOV), viewDistance(viewDistance), text(32,32) {}
        virtual void setPos(Point newPos) {
            position = newPos;
        }

        virtual Point getPos() {
            return position;
        }

        virtual void damage(double amount) {
            currentHP -= amount;
            if (currentHP <= 0)
                alive = false;
        }

        virtual void dmgPlayer(Player& player, double amount);

        virtual bool isAlive() {return alive;}

        virtual void heal(double amount) {
            if(currentHP+amount < HP)
                currentHP += amount;
            else
                currentHP = HP;
        }

        virtual double getHP() {return currentHP;}

        virtual void turn(double radian) {
            double current = atan2(directionVector.y,directionVector.x);
            current += radian;
            directionVector.x = cos(current);
            directionVector.y = sin(current);
        }

        virtual double getDirection() { return atan2(directionVector.y,directionVector.x);}

        virtual void move(double relativeX, double relativY, const DoomCopy::Map& map);

        virtual void setSpeed(double newSpeed) {
            speed = newSpeed;
        }

        bool isPlayerVisble(const Map& map, Point playerPos);
        virtual void update(const Map& map, Player& player);

        virtual ~Creature() {}
    };
}

#endif //DOOMCOPY_CREATURE_H
