//
// Created by coldus on 5/10/20.
//

#ifndef DOOMCOPY_PROJECTILE_H
#define DOOMCOPY_PROJECTILE_H

#include <SFML/System/Clock.hpp>
#include "List.h"
#include "Creature.h"
#include "StringManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                              Projectile                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {
    class Map;
    class Player;

    ///Lovedektipus - a lovedekek gyakorlatilag ennek a peldanyai pozicioval,
    ///es kulonbozo muveletekkel/tulajdonsagokkal.
    ///A lovedektipusok rendelkeznek texturaval, tavolsaggal (ameddig maximum elbirnak jutni),
    ///es sebesseggel.
    class ProjectileType {
    public:
        double dmg;
        double speed;
        double range;
        Texture text;
        ProjectileType() : text(32,32) {}

        ///Egy sorban talalhato adatok alapjan (line) betolti a lovedektipust
        ///es annak a texturajat az eleresi utvonal alapjan.
        ///@param line - string, amiben a lovedektipus adatai/tulajdonsagai szerepelnek
        ///@param path - a tipushoz tartozo textura eleresi utvonala
        void loadProjectileType(std::string path, std::string line);
    };

    ///Egy funktor arra, hogy meg lehessen vizsgalni, hogy egy lovedek egy
    ///szornyhoz eleg kozel van-e ahhoz, hogy "eltalalja" azt.
    class cmpr {
    public:
        static Point p;

        ///Beallitja a vizsgalando lovedek jelenlegi poziciojat.
        ///@param a - lovedek pozicioja
        cmpr(Point a) {
            cmpr::p = Point(a.x,a.y);
        }

        ///Megvizsgalja adott szornyre, hogy eltalalta-e azt a lovedek
        ///@param t - szorny
        ///@return - talalt-e a lovedek
        bool static nearby(Creature* t);
    };


    ///Lovedek osztaly, rendelkezik lovedek tipussal, kezdopozicioval, iranyvektorral, es jelenlegi pozicioval.
    class Projectile {
        bool stillExists = true;
        Point src;
    public:
        bool visible = false;
        sf::Clock clock;
        ProjectileType type;
        Point direction;
        Point currenPosition;
        sf::VertexArray vertexArray;

        ///Lovedek konstruktora - beallitja a lovedek tipusat, kezdo poziciojat, es iranyat.
        ///@param srcPosition - kezdo pozicio
        ///@param dir - iranyvektor
        ///@param type - lovedektipus
        Projectile(const ProjectileType& type, Point srcPosition, Point dir) : type(type), direction(dir), src(srcPosition) {
            currenPosition.x = srcPosition.x + dir.x * type.speed/20.0;
            currenPosition.y = srcPosition.y + dir.y * type.speed/20.0;

            vertexArray = sf::VertexArray(sf::Quads,4);
            clock.restart();
        }

        ///Azt vizsgalja, hogy a lovedek letezik-e.
        ///@return - lovedek letezese
        bool getStillExists() {return stillExists;}

        ///Frissiti a lovedeket, azaz annak a poziciojat, es azt, hogy letezik-e a lovedek.
        ///Azert van szukseg a map-re es a jatekosra, hogy megvizsgalja, hogy eltalalt-e barmit
        ///a lovedek, legyen az szorny, jatekos, vagy akar csak a palya egy fala.
        ///@param map - palya
        ///@param player - jatekos
        void update(Map& map, Player& player);
    };
}

#endif //DOOMCOPY_PROJECTILE_H
