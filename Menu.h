//
// Created by coldus on 5/12/20.
//
#include <iostream>
#include <fstream>

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
        int posX, posY;
        int size;
        int color;

        MenuItem(size_t size) : Container(size) {}

        virtual void doActionAt(size_t idx) {
            getItemAt(idx)->doSomething();
        }

        virtual void doSomething() {}
        virtual ~MenuItem() {}
    };

    class StartGameG : public MenuItem {
    public:
        StartGameG(const char* nameOfTheLevel) : MenuItem(0) {
            text = nameOfTheLevel;
        }

        void doSomething() {
            //std::cout << text << std::endl;
        }
    };

    class Start : public MenuItem {
    public:
        Start() : MenuItem(10) {
            loadMaps(*this);
        }

        void loadMaps(MenuItem& menu) {
            std::fstream file;
            file.open("maps.conf");
            std::string line = "";
            do {
                std::getline(file,line);
                menu.addItem(new StartGameG(line.c_str()));
            } while(!file.eof());
        }
    };

    class Settings : public MenuItem {
    public:
        Settings() : MenuItem(0) {}
    };

    class Exit : public MenuItem {
    public:
        Exit() : MenuItem(0) {}
    };
}


#endif //MENU_MENU_H
