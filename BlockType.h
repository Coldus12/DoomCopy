//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_BLOCKTYPE_H
#define DOOMCOPY_BLOCKTYPE_H

#include "List.h"
#include "Texture.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                              BlockType                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {

    ///Blokktipus - eltarolja egy adott blokk nevet,
    ///szamat, texturajat, ha van, es azt, hogy az
    ///adott blokk szilard-e vagy sem.
    class BlockType {
    public:
        int x;
        bool isSolid;
        std::string textureName;
        BlockType() {}
        BlockType(int x, bool isSolid, const char* textName) : x(x), isSolid(isSolid), textureName(textName) {}
    };

    ///Blokktipusbol allo lancolt lista, es a hozza
    ///tartozo muveletek es fuggvenyek.
    class Blocks {
    public:
        List<BlockType> blockType;
        Blocks() {}
        Blocks(std::string path, Texture& text);

        ///Betolti egy adott palyahoz a Blokktipusokat
        ///@param path - relativ path, azaz csak a palya neve, amiben a blockTypes.conf van.
        void load(std::string path, Texture&);

        ~Blocks() {}

        ///Egy (blokk) szamrol megmondja, hogy szilard-e az a blokk, vagy sem.
        ///@param type - blokktipus szama
        ///@return - szilard-e az adott tipusu blokk
        bool isTypeSolid(int type) const;

        ///Egy (blokk) szamhoz megadja a hozzatartozo textura nevet (felteve, hogy van)
        ///@param type - blokktipus szama
        ///@return - textura neve
        std::string getTextureName(int type);

        ///Szabvanyos kimenetre kiirja a blokkszamokat kulon sorokba.
        void printTypes();
    };

}

#endif //DOOMCOPY_BLOCKTYPE_H
