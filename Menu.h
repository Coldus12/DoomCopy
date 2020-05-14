//
// Created by coldus on 5/12/20.
//
#include <iostream>
#include <fstream>
#include <SFML/Graphics/Text.hpp>

#ifndef MENU_MENU_H
#define MENU_MENU_H

namespace DoomCopy {
    class Menu {
    public:
        Menu* back;
        Menu** options;
        size_t nr_of_menus = 0;
        size_t arraySize;
        std::string text;
        sf::Text gText;

        Menu(size_t arraySize, std::string name, Menu* back = NULL) : arraySize(arraySize), back(back), text(name) {
            if (arraySize > 0)
                options = new Menu*[arraySize];
        }

        virtual void doAction() {}

        virtual void addItem(Menu* newItem) {
            if (arraySize > 0) {
                if (nr_of_menus < arraySize) {
                    options[nr_of_menus] = newItem;
                    nr_of_menus++;
                } else {
                    arraySize *= 2;
                    Menu** temp = new Menu*[arraySize];
                    for (size_t i = 0; i < nr_of_menus; i++)
                        temp[i] = options[i];

                    delete[] options;

                    options = new Menu*[arraySize];
                    for (size_t i = 0; i < nr_of_menus; i++) {
                        options[i] = temp[i];
                    }

                    delete[] temp;

                    options[nr_of_menus] = newItem;
                    nr_of_menus++;
                }
            }
        }

        virtual Menu* getItemAt(size_t idx) {
            if ((idx >= 0) && (idx <= nr_of_menus))
                return options[idx];
            else
                throw std::out_of_range("well shit, container index is out of range");
        }

        virtual void printOptions() {
            for (int i = 0; i < nr_of_menus; i++) {
                std::cout << i <<". " << getItemAt(i)->text << std::endl;
            }
        }

        virtual ~Menu() {
            if (arraySize > 0) {
                for (size_t i = 0; i < nr_of_menus; i++) {
                    delete options[i];
                }
                delete[] options;
            }
            nr_of_menus = 0;
            arraySize = 0;
        }
    };
}

#endif //MENU_MENU_H
