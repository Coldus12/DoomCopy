//
// Created by coldus on 5/10/20.
//

#ifndef DOOMCOPY_WEAPON_H
#define DOOMCOPY_WEAPON_H

#include "Texture.h"
#include "Projectile.h"
#include "Map.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                 Weapon                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {

    ///Fegyver osztaly - rendelkezeik texturaval, ket allapottal: normal, lott;
    ///a "tulajdonosa" poziciojaval es iranyvektoraval. Erre azert van szukseg,
    ///mert lovedeket loni a fegyver tud, nem a jatekos, igy a loveskor a fegyvernek
    ///"ismernie" kell a jatekos poziciojat es iranyat, hogy a lovedeket abba az iranyba
    ///inditsa el.
    class Weapon {
        sf::Clock clock;
    public:
        enum state {
            default_state,
            shoot
        };
        state currentState = default_state;

        ProjectileType type;
        Texture texture;
        double fireRate;
        double range; //cli
        const Point* ownerPos;
        const double* ownerDir;

        sf::VertexArray vertexArray;

        ///Letrehozza a fegyvert, de meg valojaban ez egy "ures" fegyver,
        ///minden tulajdonsage "ures".
        Weapon() : texture(32,32) {
            vertexArray = sf::VertexArray(sf::Quads,4);
        }

        ///Letrehoz egy fegyvert, aminek mar be van allitva a "pozicioja" es "iranya"
        ///@param ownerPos - a fegyver tulajdonosanak poziciojara pointer, hogy mindig meg legyen a jelenlegi pozicio
        ///@param ownerDirection - iranyvektorra pointer, hogy folyamatosan friss legyen az is.
        Weapon(const Point* ownerPos, const double* ownerDirection) : texture(32,32), ownerPos(ownerPos), ownerDir(ownerDirection) {
            clock.restart();
            vertexArray = sf::VertexArray(sf::Quads,4);
        }

        ///Beallitja egy fegyver iranyat es poziciojat
        ///@param ownerPos - tulajdonos poziciojara pointer
        ///@param ownerDirection - tulajdonos iranyara pointer
        void set(const Point* ownerPos, const double* ownerDirection) {
            this->ownerPos = ownerPos;
            this->ownerDir = ownerDirection;
            clock.restart();
        }

        ///Betolti a fegyvert egy konfiguracios fajl alapjan ami weapon.conf neven talalhato
        ///az eleresi utvonalon. Ez a fajl minden informaciot tartalmaz a fegyverrol, mint
        ///lovedekenek tipusa, tuzelesi sebesseg, textura eleresi utvonala, stb
        ///@param path - eleresi utvonal a weapon.conf-hoz
        ///@return - betoltes sikeressege
        bool loadWeapon(std::string path);

        ///"Kilo" egy lovedeket.
        ///Azaz a palya lovedeklistajahoz hozzaad egy lovedeket, aminek kezdopozicioja
        ///a fegyver "pozicioja" es iranya a fegyver "iranya".
        ///@param map - palya
        void gShot(Map& map);

        ///Frissiti a fegyver allapotat, a gShot fuggveny a fegyver allapotat
        ///shoot-ra allitja, es ez a fuggveny ezt frissiti.
        void updateState() {
            if (currentState == shoot)
                currentState = default_state;
        }
    };
}


#endif //DOOMCOPY_WEAPON_H
