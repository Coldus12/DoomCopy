//
// Created by coldus on 5/12/20.
//
#include <iostream>
#include <fstream>
#include <SFML/Graphics/Text.hpp>

#ifndef MENU_MENU_H
#define MENU_MENU_H

namespace DoomCopy {
    template <typename T>
    class Container {
        size_t nrOfItems = 0;
        size_t currentMaxSize;
        T** items;
    public:
        Container(size_t size) : currentMaxSize(size) {
            if (currentMaxSize > 0)
                items = new T*[currentMaxSize];
        }

        void addItem(T* newItem) {
            if (currentMaxSize > 0) {
                if (nrOfItems < currentMaxSize) {
                    items[nrOfItems] = newItem;
                    nrOfItems++;
                } else {
                    currentMaxSize *= 2;
                    T** temp = new T*[currentMaxSize];
                    for (size_t i = 0; i < nrOfItems; i++)
                        temp[i] = items[i];

                    delete[] items;

                    items = new T*[currentMaxSize];
                    for (size_t i = 0; i < nrOfItems; i++) {
                        items[i] = temp[i];
                    }

                    delete[] temp;

                    items[nrOfItems] = newItem;
                    nrOfItems++;
                }
            }
        }

        int itemNr() const {return nrOfItems;}

        int getMaxSize() {return currentMaxSize;}

        T* getItemAt(size_t idx) {
            if ((idx >= 0) && (idx <= currentMaxSize))
                return items[idx];
            else
                throw std::out_of_range("well shit, container index is out of range");
        }

        ~Container() {
            if (currentMaxSize > 0) {
                for (size_t i = 0; i < nrOfItems; i++) {
                    delete items[i];
                }
                delete[] items;
            }
            nrOfItems = 0;
        }

    };

    class MenuItem : public Container<MenuItem> {
    public:
        std::string text;
        sf::Text sfText;

        MenuItem(size_t size) : Container(size) {}

        virtual void doActionAt(size_t idx) {
            getItemAt(idx)->doSomething();
        }

        virtual void doSomething() {}
        virtual ~MenuItem() {}
    };
}


#endif //MENU_MENU_H
