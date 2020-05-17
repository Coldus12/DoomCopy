//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_CREATURE_H
#define DOOMCOPY_CREATURE_H

#include <iostream>
#include <SFML/Graphics/VertexArray.hpp>
#include <cmath>
#include <SFML/System/Clock.hpp>

#include "Point.h"
#include "Texture.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                               Creature                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {
    class Map;
    class Player;

    ///A jatekhoz tartozo szorny osztaly
    ///@param alive - el-e a szorny (eletpontjai 0 folott vannak)
    ///@param speed - mozgasi sebesseg
    ///@param currentHP - jelenlegi eletpontok szama
    ///@param HP - eredeti/maximum eletpontok szama
    ///@param currentStatus - jelenlegi statusza (mozzgas/tamadas/allas/stb)
    ///@param position - szorny pozicioja
    ///@param directionVector - iranyvektor - ebbe az iranyba nez, es mozog
    ///@param visible - latja-e a jatekos
    ///@param distanceFromPlayer - jatekostol valo tavolsag - ez alapjan van a szorny lista rendezve
    ///@param text - textura
    ///@param FOV - szorny latoszoge
    ///@param viewDistance - szorny latotavolsaga
    class Creature {
    private:
        sf::Clock clock;
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

        ///Szorny konstruktora.
        ///Beallitja a kezodhelyzetet, kezdoiranyat, latoszoget,
        ///es ltotavolsagat.
        ///@param pos - kezdo pozicio
        ///@param direction - kezdo irany
        ///@param viewDistance - latotavolsag
        ///@param HP - kezdo/max eletpontok szama
        Creature(Point pos, double HP, Point direction, double FOV, double viewDistance) : position(pos), HP(HP), viewDistance(viewDistance), text(32,32) {
            this->FOV = FOV * M_PI/180.0;
            double alfa = atan2(direction.y,direction.x);
            alfa *= M_PI/180.0;
            this->directionVector = Point(cos(alfa),sin(alfa));
            currentHP = HP;
        }

        ///Barmilyen vizsgalat nelkul csak
        ///atallitja a szorny poziciojat egy masikra.
        ///@param newPos - uj pozicio
        virtual void setPos(Point newPos) {
            position = newPos;
        }

        ///Visszaadja a szorny jelenlegi poziciojat
        ///@return - szorny jelenlegi pozicioja
        virtual Point getPos() {
            return position;
        }

        ///Adott mennyiseget sebez
        ///ha ezzel a szorny eletpontja nulla,
        ///vagy annal kevesebb, akkor a szorny elpusztul
        ///@param amount - sebzes merete
        virtual void damage(double amount) {
            currentHP -= amount;
            if (currentHP <= 0)
                alive = false;
        }

        ///Megsebzi a jatekost
        ///@param player - jatekos
        ///@param amount - sebzes merete
        virtual void dmgPlayer(Player& player, double amount);

        virtual bool isAlive() {return alive;}

        ///Visszatolti a szorny egy adott mennyisegu eletpontjat,
        ///de ha az tobb vagy annyi, mint a max eletpontjainak szama
        ///, akkor szorny a kezdo eletpontjat kapja meg.
        ///@param amount - eletviszzatoltes merteke
        virtual void heal(double amount) {
            if(currentHP+amount < HP)
                currentHP += amount;
            else
                currentHP = HP;
        }

        virtual double getHP() {return currentHP;}

        ///A szorny iranyvektorat elforditja egy radianban megadott szoggel
        ///@param radian - szog radianban
        virtual void turn(double radian) {
            double current = atan2(directionVector.y,directionVector.x);
            current += radian;
            directionVector.x = cos(current);
            directionVector.y = sin(current);
        }

        virtual double getDirection() { return atan2(directionVector.y,directionVector.x);}

        ///A szorny jelenlegipoziciojahoz kepest elmozgatja azt valamilyen
        ///x, y iranyban felteve, hogy kozben nem utkozik semmilyen falba.
        ///@param map - palya (falakba utkozes vizsgalata miatt van ra szukseg)
        ///@param relativeX - pozicio valtozasa x iranyban
        ///@param relativY - pozicio valtozasa y iranyban
        virtual void move(double relativeX, double relativY, const DoomCopy::Map& map);

        virtual void setSpeed(double newSpeed) {
            speed = newSpeed;
        }

        ///Latja-e a szorny a jatekost
        ///@param map - palya
        ///@param playerPos - jatekos pozicioja
        ///@return - lathato-e a jatekos
        bool isPlayerVisble(const Map& map, Point playerPos);

        ///Frissiti a szornyet, mozgatja, "tamadtatja",
        ///valtoztatja annak jelenlegi statuszat.
        ///Valojaban itt ez felel meg leginkabb
        ///a mesterseges intelligencianak, pedig valojabon
        ///csak mesterseges.
        ///@param map - palya
        ///@param player - jatekos
        virtual void update(const Map& map, Player& player);

        virtual ~Creature() {}
    };
}

#endif //DOOMCOPY_CREATURE_H
