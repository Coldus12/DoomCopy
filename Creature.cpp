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

    while (dir < -M_PI)
        dir += 2 * M_PI;
    while (dir > M_PI)
        dir -= 2 * M_PI;

    directionVector.x = cos(dir);
    directionVector.y = sin(dir);

    double cosAngle = cos(angleToPlayer);
    double sinAngle = sin(angleToPlayer);

    double d1 = 0;
    while(d1 <= distanceFromPlayer) {
        d1 += 0.1;
        if ((position.x + d1 * cosAngle <= 0) || (position.y + d1 * sinAngle <= 0))
            break;
        if ((position.x + d1 * cosAngle >= map.columns) || (position.y + d1 * sinAngle >= map.rows))
            break;

        if (map.blocks.isTypeSolid(map.data[int(position.x + d1 * cosAngle)][int(position.y + d1 * sinAngle)]))
            break;
    }
    //std::cout << d1 << " distance " << distanceFromPlayer << " playerPos " << playerPos.x << " " << playerPos.y << " M pos x " << position.x << " " << position.y << " dx " << cosAngle << " dy " << sinAngle << std::endl;

    if (d1 >= distanceFromPlayer)
        return (((dir - FOV / 2.0) <= angleToPlayer) && (angleToPlayer <= (dir + FOV / 2.0))) && (distanceFromPlayer <= viewDistance);
    else
        return false;
}

void DoomCopy::Creature::update(const Map& map, Player& player) {
    sf::Time passed = clock.getElapsedTime();
    if (passed.asSeconds() >= 1/10.0) {

        double dx = player.getPosX() - position.x;
        double dy = player.getPosY() - position.y;

        if (isPlayerVisble(map,Point(player.getPosX(),player.getPosY()))) {
            if (distanceFromPlayer <= 1.5) {

                if (currentStatus == attack1)
                    currentStatus = attack2;
                else
                    currentStatus = attack1;

                if (currentStatus == attack2)
                    dmgPlayer(player,5);
            }

            if ((!map.blocks.isTypeSolid(map.data[int(position.y + speed * dy)][int(position.x + speed * dx)])) && (distanceFromPlayer > 1.5)) {
                position.x += speed/20.0 * dx;
                position.y += speed/20.0 * dy;

                if (currentStatus == run1)
                    currentStatus = run2;
                else
                    currentStatus = run1;
            }
        } else {
            //Not visible
            double dir = atan2(directionVector.y,directionVector.x);

            if ((dir - M_PI/2.0) <= player.direction <= (dir + M_PI/2.0))
                currentStatus = stand;
            else
                currentStatus = back;

            std::srand((unsigned) time(NULL));
            int random = std::rand()%4;

            if (random) {
                turn(20 * M_PI/180.0);
            } else {
                double mx = cos(directionVector.x);
                double my = sin(directionVector.y);

                if (!map.blocks.isTypeSolid(map.data[int(position.y + my)][int(position.x + mx)])) {
                    position.x += mx;
                    position.y += my;
                }
            }

        }

        clock.restart();
    }
}

void DoomCopy::Creature::dmgPlayer(Player& player, double amount) {
    player.HP -= amount;
}