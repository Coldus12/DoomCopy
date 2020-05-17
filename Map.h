//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_MAP_H
#define DOOMCOPY_MAP_H

#include "Array2D.h"
#include "List.h"
#include "BlockType.h"
#include "Creature.h"
#include "Projectile.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                    Map                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {

    ///A palya, egy ketdimenzios szam tomb, ahol minden szam egy blokkot jelent.
    ///Rendelkezik egy texturaval, amibe 9 blokktextura fer bele.
    ///Ezen kivul a palya rendelkezik egy szorny listval, es egy lovedeklistval.
    class Map : public Array2D<int> {
    public:
        Texture text;
        Blocks blocks;
        List<Creature*> enemies;
        List<Projectile*> projectiles;
        Array2D<char> CLIMap;

        Map() : text(32,32) {}

        ///Betolti a palyat, es minden mast ami a palyahoz tartozik, pl a szornyeket a szorny listaba
        ///@param pathToMap - a palya mappa eleresi utvonala
        Map(std::string pathToMap);

        ///Betolti a palyat, es minden mast ami a palyahoz tartozik, pl a szornyeket a szorny listaba
        ///@param pathToMap - a palya mappa eleresi utvonala
        void load(std::string pathToMap);

        ///Betolti a palyahoz tartozo szornyek a palya mappajanak eleresi utvonala alapjan.
        ///@param pathToMap - a palyat tartalmazo mappa eleresi utvonala
        void loadEnemies(std::string pathToMap);

    };

    ///A sugar, egy egyszeru funktor, ami ugy mukodik, hogy egy kezdopoziciobol egy adott iranyba "kilovunk"
    ///egy sugarat, es megnezzuk, hogy blokkba utkozik-e, es visszaadjuk azt a tavolsagot amit ez a sugar megtett
    ///mig blokkba nem utkozott, vagy ha nem utkozott blokkba, akkor azt a maximalis tavolsagot, amit a sugar engedelyezetten
    ///meg tudott tenni.
    class Ray {
    public:
        static double distanceFromCollision(const Map& map, Point source, Point direction, double stepSize, double maxDistance);
    };

    ///A sugar fuggvenye
    ///@param source - a pozicio ahonnan a sugar indul
    ///@param direction - az irany amibe a sugar megy
    ///@param maxDistance - a maximum tavolsag amit a sugar megbir tenni
    ///@param stepSize - lepesemeret (mennyivel no a sugar azelott hogy megint megvizsgalnank, hogy blokkba utkozott-e)
    ///@param map - palya
    ///@return - a tavolsag amit a sugar utkozes elott megtett.
    double inline Ray::distanceFromCollision(const Map &map, Point source, Point direction, double stepSize, double maxDistance) {
        double raySize = 0;

        while(raySize < maxDistance) {
            raySize += stepSize;

            int x = source.x + (raySize*direction.x);
            int y = source.y + (raySize*direction.y);

            if (map.blocks.isTypeSolid(map.data[y][x])) {
                //double distance = raySize * sqrt(dx*dx + dy*dy);
                //ami valójában raysize * 1, szal raysize...
                return raySize;
            }

        }

        if (raySize >= maxDistance)
            return maxDistance;
        return maxDistance;
    }
}

#endif //DOOMCOPY_MAP_H
