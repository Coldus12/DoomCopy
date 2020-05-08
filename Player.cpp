//
// Created by coldus on 5/8/20.
//
#include "Player.h"
void DoomCopy::Player::move(double relativeX, double relativY, const DoomCopy::Map& map) {
    int x = (posX + relativeX);
    int y = (posY + relativY);
    int oX = posX;
    int oY = posY;

    if (!(map.blocks.isTypeSolid(map.data[y][x]) || map.blocks.isTypeSolid(map.data[oY][x]) || map.blocks.isTypeSolid(map.data[y][oX]) || map.blocks.isTypeSolid(map.data[oY][oX]))) {
        posX += relativeX;
        posY += relativY;
    }
}

void DoomCopy::Player::setPosX(double nPosX, const DoomCopy::Map& map) {
    int x = nPosX;
    int y = posY;
    if (!map.blocks.isTypeSolid(map.data[y][x])) setPosX(nPosX);
}
void DoomCopy::Player::setPosY(double nPosY, const DoomCopy::Map& map) {
    int x = posX;
    int y = nPosY;
    if (!map.blocks.isTypeSolid(map.data[y][x])) setPosY(nPosY);
}