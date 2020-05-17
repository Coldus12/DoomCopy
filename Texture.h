//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_TEXTURE_H
#define DOOMCOPY_TEXTURE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Point.h"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                  Texture                                                       ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {
    ///Textura
    ///Mivel az sf::VertexArray-nek csupan egy renderstate alapjan van texturaja, igy
    ///minden texturat ami egy VertexArray-hez tartozik erdemes egy nagy texturaba osszegyujteni,
    ///es igy bizonyos tulajdonsagok alapjan (pl textura neve) lehet a VertexArray kulonbozo texturaju reszeihez
    ///kulonbozo texturakat "kivalasztani".
    ///Mindez ugy mukodik, hogy a sajat tipusu textura class-nek van egy max merete (hany x,y meretu texturat bir
    ///eltarolni), egy jelenlegi merete (valojaban hany textura van eddig bele rakva), es termeszetesen egy sf::Texture-je,
    ///aminek szelessege a maximum meret * x (ha x az egyeni texturak szelessege), es magassaga: maximum meret * y.
    ///A texturak neve el van mentve, azzal egyutt hogy a "textura matrixban" hol van a helyuk, igy egy sample fuggvennyel
    ///a nev alapjan visszakaphatjuk, hol a sajat textura class sf::Texture-ben melyik x,y koordinataktol talalhato
    ///a keresett texturank.
    class Texture {
        size_t currentSize = 0;
        static const size_t maxSize = 9;
        int w, h;
        sf::Texture text;
    public:
        std::string names[maxSize];
        sf::RenderStates states;

        ///Konstruktor, beallitja az egysegnyi texturak szelessegeit, es magassagait,
        ///majd ez alapjan letrehozza a textura megfelelo meretu sf::Texture-jet.
        ///Ebbe 9 darab a beallitott szelesseggel es magassaggal rendelkezo texturat/kepet
        ///lehet betolteni.
        ///@param width - egyes texturak/kepek szelessege
        ///@param height - egyes texturak/kepek magassaga
        Texture(int width, int height) {
            w = width;
            h = height;
            text.create(maxSize*width,maxSize*height);
            states.texture = &text;
        }

        ///Betolt egy kepet a "textura matrixba" a kep eleresi utvonala alapjan
        ///@param pathToImg - a kep eleresi utvonala
        ///@param imgName - a kep neve, ami alapjan kesobb meglehet talalni.
        void addImg(const char* pathToImg, const char* imgName) {
            if (currentSize < maxSize) {
                names[currentSize] = imgName;

                sf::Texture newText;
                newText.loadFromFile(pathToImg);

                int px = (currentSize % 3);
                int py = int(currentSize/3.0);

                text.update(newText,px * w,py * h);

                currentSize++;
            } else {
                std::cerr << "Could not add the new image to this texture as it is already full." << std::endl;
            }
        }

        ///Egy textura neve alapjan visszaad egy (x,y) koordinatat.
        ///A keresett texturanak a nagy "textura-matrixban" ez a bal folso pontja, es a textura
        ///ettol tart az (x + texturak szelesseg, y + texturak magassaga) koordinataig.
        ///@param name - keresett texturanak a neve
        ///@return - keresett textura bal felso koordinataja a "textura-matrixban"
        Point sampleFrom(std::string name) {
            for (int i = 0; i < currentSize; i++) {
                if ((names[i].find(name) != std::string::npos) && (names[i].length() == name.length())) {
                    int px = ((i) % 3);
                    int py = int((i)/3.0);
                    return Point(px * w, py * h);
                }
            }

            std::cerr << "This texture does not contain any sf::Texture named " << name << std::endl;
            return Point(0,0);
        }

        ///Visszaadja a kontruktor altal beallitott egysegnyi textura szelesseget, es magassagat.
        ///@return - egysegnyi textura dimenzioi
        Point getTextureSize() {
            return Point(w,h);
        }
    };
}

#endif //DOOMCOPY_TEXTURE_H
