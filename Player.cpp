//
// Created by coldus on 5/8/20.
//
#include "Player.h"
void DoomCopy::Player::move(double relativeX, double relativY, const DoomCopy::Map& map) {
    int x = (position.x + relativeX);
    int y = (position.y + relativY);
    int oX = position.x;
    int oY = position.y;

    if (!(map.blocks.isTypeSolid(map.data[y][x]) || map.blocks.isTypeSolid(map.data[oY][x]) || map.blocks.isTypeSolid(map.data[y][oX]) || map.blocks.isTypeSolid(map.data[oY][oX]))) {
        position.x += relativeX;
        position.y += relativY;
    }
}

void DoomCopy::Player::setPosX(double nPosX, const DoomCopy::Map& map) {
    int x = nPosX;
    int y = position.y;
    if (!map.blocks.isTypeSolid(map.data[y][x])) setPosX(nPosX);
}

void DoomCopy::Player::setPosY(double nPosY, const DoomCopy::Map& map) {
    int x = position.x;
    int y = nPosY;
    if (!map.blocks.isTypeSolid(map.data[y][x])) setPosY(nPosY);
}