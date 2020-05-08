//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_BLOCKTYPE_H
#define DOOMCOPY_BLOCKTYPE_H

#include "Texture.h"
#include "List.h"

namespace DoomCopy {
    class BlockType {
    public:
        int x;
        bool isSolid;
        std::string textureName;
        BlockType() {}
        BlockType(int x, bool isSolid, const char* textName) : x(x), isSolid(isSolid), textureName(textName) {}
    };

    class Blocks {
    public:
        List<BlockType> blockType;
        Blocks() {}
        Blocks(const char*, Texture& text);
        void load(const char*, Texture&);
        ~Blocks() {}

        bool isTypeSolid(int) const;
        std::string getTextureName(int);
        void printTypes();
    };

}

#endif //DOOMCOPY_BLOCKTYPE_H
