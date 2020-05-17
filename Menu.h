//
// Created by coldus on 5/12/20.
//
#include <iostream>
#include <fstream>
#include <SFML/Graphics/Text.hpp>

#ifndef MENU_MENU_H
#define MENU_MENU_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                  Menu                                                          ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace DoomCopy {

    ///A Menu osztaly a kovetkezo modon mukodik: rendelkezik egy doAction fuggvennyel, mely egy adott menupont
    ///kivalasztasa utan lefut, felteve, hogy a kivalasztott menupont nem rendelkezik almenukkel. A Menu osztaly
    ///rendelkezhet egy ebbol az abstract osztalybol szarmazo heterogen kollekcioval. Ez a heterogen kollekcio valojaban
    ///az almenuk pointereibol allo dinamikus tomb. Ezenkivul minden menu rendelkezik meg egy menu pointerrel, ami vagy
    /// NULL (ez esetben a menu nem submenu), vagy pedig arra a menure mutat, amiben ez a menu egy submenu.
    ///Mas szavakkal: a Menu osztaly valojaban egy funktor, es minden menu/menupont ennek a leszarmazottja, es minden
    ///szarmaztataskor a menu viselkedeset a doAction fuggveny atirasaval lehet megvaltoztatni. Es azert, hogy barmilyen
    ///menu tartalmazhasson barmilyen menupontot/almenut, ezert minden menu rendelkezik egy menukbol allo heterogen kollekcioval.
    class Menu {
    public:
        Menu* back;
        Menu** options;
        size_t nr_of_menus = 0;
        size_t arraySize;
        std::string text;
        sf::Text gText;

        ///Letrehoz egy menut/menupontot egy adott merettel (ha 0, akkor nincs almenuje -> ilyenkore menupont),
        ///adott nevvel, es egy back pointerrrel, ami az elozo menure mutat ami ezt tartalmazza, ha van ilyen.
        ///@param arraySize - menu meret, ha 0, akkor nem lehet hozza menupontokat adni
        ///@param name - a menu neve
        ///@param back - pointer az elozo menure, ha van olyan
        Menu(size_t arraySize, std::string name, Menu* back = NULL) : arraySize(arraySize), back(back), text(name) {
            if (arraySize > 0)
                options = new Menu*[arraySize];
        }

        ///Az a fuggveny ami a menupont kivalasztasanal lefut. Ezt kell minden uj menunek felulirnia.
        virtual void doAction() {}

        ///Hozzad egy almenut/menupontot a menuhoz
        ///@param newItem - menupont/almenu pointer
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
            } else {
                delete newItem;
                std::cerr << "You cannot add submenus to something which cannot contain submenus!" << std::endl;
            }
        }

        ///Visszaadja egy adott indexu almenu memoriacimet
        ///@param idx - almenu/menupont indexe
        ///@return - almenu/menupont memoriacime
        virtual Menu* getItemAt(size_t idx) {
            if (arraySize > 0) {
                if ((idx >= 0) && (idx <= nr_of_menus))
                    return options[idx];
                else
                    throw std::out_of_range("Index is out of range");
            } else {
                std::cerr << "This menu does not have any submenus!" << std::endl;
                return NULL;
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
