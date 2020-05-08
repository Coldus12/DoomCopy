//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_TEXTURE_H
#define DOOMCOPY_TEXTURE_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "Point.h"

namespace DoomCopy {
    class Texture {
        size_t currentSize = 0;
        static const size_t maxSize = 9;
        int w, h;
        sf::Texture text;
    public:
        std::string names[maxSize];
        sf::RenderStates states;

        Texture(int width, int height) {
            w = width;
            h = height;
            text.create(maxSize*width,maxSize*height);
            states.texture = &text;
        }

        void addImg(const char* pathToImg, const char* imgName) {
            if (currentSize < maxSize) {
                names[currentSize] = imgName;

                sf::Texture newText;
                newText.loadFromFile(pathToImg);

                int px = (currentSize % 3);
                int py = int(currentSize/3.0);

                //std::cout << px << " " << py << std::endl;

                text.update(newText,px * w,py * h);

                currentSize++;
            } else {
                //HIBA
            }
        }

        Point sampleFrom(std::string name) {
            for (int i = 0; i < currentSize; i++) {
                if ((names[i].find(name) != std::string::npos) && (names[i].length() == name.length())) {
                    int px = ((i) % 3);
                    int py = int((i)/3.0);
                    return Point(px * w, py * h);
                }
            }
            //HIBA
            return Point(0,0);
        }

        Point getTextureSize() {
            return Point(w,h);
        }
    };
}

#endif //DOOMCOPY_TEXTURE_H
