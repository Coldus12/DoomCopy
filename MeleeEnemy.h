//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_MELEEENEMY_H
#define DOOMCOPY_MELEEENEMY_H

#include "Creature.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                              MeleeEnemy                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {
    class MeleeEnemy : public Creature {
    public:
        double damage;
        double attackSpeed;

        ///Letrehoz egy adott texturaju, pozicioju, iranyu, eletpontu, sebzesu MeleeEnemy-t.
        ///@param HP - max/kezdo eletpontok szama
        ///@param position - kezdo pozicio
        ///@param direction - kezdo irany
        ///@param FOV - latoszog
        ///@param viewDistance - latotavolsag
        ///@param pathToText - textura eleresi utvonala
        ///@param textname - textura neve
        MeleeEnemy(Point position, Point direction, double HP, double dmg, double attackSpeed, const std::string& pathToText, const char* textname, double FOV, double viewDistance) : Creature(position,HP,direction, FOV, viewDistance) {
            text.addImg((pathToText + textname + "_run1.png").c_str(),"run1");
            text.addImg((pathToText + textname + "_run2.png").c_str(),"run2");
            text.addImg((pathToText + textname + "_attack1.png").c_str(),"attack1");
            text.addImg((pathToText + textname + "_attack2.png").c_str(),"attack2");
            text.addImg((pathToText + textname + "_standing.png").c_str(),"standing");
            text.addImg((pathToText + textname + "_behind.png").c_str(),"behind");

            vertexArray = sf::VertexArray(sf::Quads,4);

            damage = dmg;
            this->attackSpeed = attackSpeed;
        }

    };
}

#endif //DOOMCOPY_MELEEENEMY_H
