//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_PLAYER_H
#define DOOMCOPY_PLAYER_H

#include "Point.h"
#include "Map.h"
#include "Weapon.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                 Player                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {

    ///Jatekos - rendelkezik fegyverrel, eletpontokkal, latoszoggel, latotavolsaggal, pozicioval, irannyal.
    ///A jatekos az amit a felhasznalo iranyitani tud, a jatek veget erhet, ha a jatekos meghal.
    class Player {
        Point position;
    public:
        Weapon weapon;
        double HP = 100;
        double FOV;
        double direction;
        //double speed;
        double viewDistance;

        ///Jatekos konstruktora, ami csak a kezdopoziciojat allitja be/allitja at, barmilyen vizsgalat nelkul.
        ///@param x - jatekos uj x koordinataja
        ///@param y - jatekos uj y koordinataja
        Player(double x, double y) {
            position.x = x;
            position.y = y;
        }

        ///Jatekos konstruktora, ami megnyitja a conf eleresi utvonalu fajlt, majd a fajl tartalma
        ///alapjan betolti a jatekost, annak fegyverevel, poziciojaval, iranyaval, latoszogevel,
        ///latotavolsagaval, eletpontjaival egyutt. Azaz teljesen.
        ///@param conf - a jatekos konfiguracios fajljanak eleresi utvonala
        Player(const char* conf);

        ///Jatekos konstruktora, ami a fontosabb dolgokat beallitja konfiguracios fajl nelkul (de pl fegyvert nem)
        ///@param x - jatekos x koordinataja
        ///@param y - jatekos y koordinataja
        ///@param direction - jatekos iranya radianban (0 radian az x tengelyen valo pozitiv iranyu mozgassal egyenerteku)
        ///@param FOV - latoszog radianban
        ///@param viewDistance - latotavolsag (blokkok szamaban)
        Player(double x, double y, double FOV, double direction, double viewDistance) {
            position.x = x;
            position.y = y;
            this->FOV = FOV;
            this->direction = direction;
            //this->speed = speed;
            this->viewDistance = viewDistance;
            weapon.set(&position, &this->direction);
        }

        ///Mozgas fuggveny, a jatekos a jelenlegi poziciojahoz kepest elmozdul relativeX-el es relativY-al,
        ///felteve, hogy ezzel a mozgassal nem utkozik blokkba (ezert van szukseg a mapre)
        ///@param relativeX - mozgas x iranyban a jelenegi poziciohoz kepest
        ///@param relativY - mozgas y iranyban a jelenegi poziciohoz kepest
        ///@param map - palya
        void move(double relativeX, double relativY, const DoomCopy::Map& map);

        ///Barmilyen vizsgalat nelkul atallitja a jatekos x poziciojat egy ujra.
        ///@param nPosX - uj x koordinataja a jatekosnak
        void setPosX(double nPosX) {position.x = nPosX;}

        ///Barmilyen vizsgalat nelkul atallitja a jatekos y poziciojat egy ujra.
        ///@param nPosY - uj y koordinataja a jatekosnak
        void setPosY(double nPosY) {position.y = nPosY;}

        ///Atallitja a jatekos x koordinatajat egy ujra, felteve,
        ///hogy igy nem utkozik a jatekos, vagy nem kerul blokk belsejebe.
        ///@param nPosX - uj x koordinata
        ///@param map - palya
        void setPosX(double nPosX, const DoomCopy::Map& map);

        ///Atallitja a jatekos y koordinatajat egy ujra, felteve,
        ///hogy igy nem utkozik a jatekos, vagy nem kerul blokk belsejebe.
        ///@param nPosY - uj y koordinata
        ///@param map - palya
        void setPosY(double nPosY, const DoomCopy::Map& map);

        ///Visszaadja a jatekos x koordinatajat
        ///@return - jatekos x koordinataja
        double getPosX() {return position.x;}

        ///Visszaadja a jatekos y koordinatajat
        ///@return - jatekos y koordinataja
        double getPosY() {return position.y;}
    };
}

#endif //DOOMCOPY_PLAYER_H
