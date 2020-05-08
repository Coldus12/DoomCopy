//
// Created by coldus on 5/8/20.
//
#include "Array2D.h"
#include "Map.h"
#include "Creature.h"
#include "Player.h"

void DoomCopy::Creature::move(double relativeX, double relativY, const DoomCopy::Map& map) {
    int x = int(position.x + relativeX);
    int y = int(position.y + relativY);
    int oX = int(position.x);
    int oY = int(position.y);

    if (!(map.blocks.isTypeSolid(map.data[y][x]) || map.blocks.isTypeSolid(map.data[oY][x]) || map.blocks.isTypeSolid(map.data[y][oX]) || map.blocks.isTypeSolid(map.data[oY][oX]))) {
        position.x += relativeX;
        position.y += relativY;
    }
}

bool DoomCopy::Creature::isPlayerVisble(const Map& map, Point playerPos) {
    double dx = playerPos.x - position.x;
    double dy = playerPos.y - position.y;
    distanceFromPlayer = sqrt(dx * dx + dy * dy);
    double dir = atan2(directionVector.y,directionVector.x);
    double angleToPlayer = atan2(dy,dx);

    return ((dir - FOV / 2.0) <= angleToPlayer <= (dir + FOV / 2.0)) && (distanceFromPlayer <= viewDistance);
}

void DoomCopy::Creature::update(const Map& map, Player& player) {
    sf::Time passed = clock.getElapsedTime();
    if (passed.asSeconds() >= 1/10.0) {
        //std::cout << "here we are mate" << std::endl;

        if (isPlayerVisble(map,Point(player.getPosX(),player.getPosY()))) {
            //std::cout << "oh yeah, nice " << std::endl;
            double dx = player.getPosX() - position.x;
            double dy = player.getPosY() - position.y;

            if (distanceFromPlayer <= 1.5) {
                //std::cout << "being attacked" << std::endl;

                if (currentStatus == attack1)
                    currentStatus = attack2;
                else
                    currentStatus = attack1;

                if (currentStatus == attack2)
                    dmgPlayer(player,5);
            }

            //std::cout << "Before change: " << position.x << " " << position.y << std::endl;
            if ((!map.blocks.isTypeSolid(map.data[int(position.y + speed * dy)][int(position.x + speed * dx)])) && (distanceFromPlayer > 1.5)) {
                position.x += speed/20.0 * dx;
                position.y += speed/20.0 * dy;

                //std::cout << position.x << " " << position.y << std::endl;

                if (currentStatus == run1)
                    currentStatus = run2;
                else
                    currentStatus = run1;
            }
        }

        if (distanceFromPlayer > viewDistance)
            currentStatus = stand;


        clock.restart();
    }
}

void DoomCopy::Creature::dmgPlayer(Player& player, double amount) {
    player.HP -= amount;
}