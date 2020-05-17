//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_LIST_H
#define DOOMCOPY_LIST_H

#include <iostream>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                  List                                                          ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {

    ///Listitem - lancolt lista egysegeleme
    ///@param T - adattipus
    template <typename T>
    class ListItem {
    public:
        T item;
        ListItem* next;
        ListItem(T item) {
            this->item = item;
            next = NULL;
        }
    };

    ///Automatikus lancolt lista sablon
    ///hasonlo az std::vector-hoz, csak minden
    ///szempontbol rosszabb.
    ///@param T - adattipus
    template <typename T>
    class List {
        ListItem<T>* head = NULL;
        bool isDestructFucSet = false;
        void (*fnc)(T t);

        ///Fuggvény ami felcsereli ket elem
        ///poziciojat a listaban
        ///@param nr1 - a lancolt lista egyik elemenek indexe
        ///@param nr2 - a lancolt list masik elemenek indexe
        void swap(size_t nr1, size_t nr2) {
            if ((0 < nr1 <= currentSize) && (0 < nr2 <= currentSize)) {
                if (abs(int(nr2) - int(nr1)) > 1) {
                    ListItem<T>* tmpBehind1 = NULL;
                    ListItem<T>* tmpBehind2 = NULL;

                    if (nr1 > 0) {
                        tmpBehind1 = addrAt(nr1 - 1);
                    }

                    if (nr2 > 0) {
                        tmpBehind2 = addrAt(nr2 - 1);
                    }

                    ListItem<T>* nrTmp = addrAt(nr1);
                    ListItem<T>* nr2Tmp = addrAt(nr2);
                    ListItem<T>* nr2TmpNext = nr2Tmp->next;

                    nr2Tmp->next = nrTmp->next;
                    nrTmp->next = nr2TmpNext;


                    if (tmpBehind1 != NULL) {
                        tmpBehind1->next = nr2Tmp;
                    } else {
                        head = nr2Tmp;
                    }

                    if (tmpBehind2 != NULL) {
                        tmpBehind2->next = nrTmp;
                    } else {
                        head = nrTmp;
                    }
                }

                if (abs(int(nr1) - int(nr2)) == 1) {
                    size_t nagy;
                    size_t kicsi;

                    if (nr1 > nr2) {
                        nagy = nr1;
                        kicsi = nr2;
                    } else {
                        nagy = nr2;
                        kicsi = nr1;
                    }

                    ListItem<T>* kisebb = addrAt(kicsi);
                    ListItem<T>* nagyobb = kisebb->next;
                    ListItem<T>* tmp = nagyobb->next;

                    ListItem<T>* tmpBehind = NULL;
                    if (kicsi > 0)
                        tmpBehind = addrAt(kicsi - 1);

                    nagyobb->next = kisebb;
                    kisebb->next = tmp;

                    if (kicsi > 0)
                        tmpBehind->next = nagyobb;
                    else
                        head = nagyobb;

                }
            } else {
                throw std::out_of_range("Swap index(es) seem to be out of range...");
            }
        }

        size_t partition(size_t low, size_t high, bool fnc(T i, T i2)) {
            ListItem<T>* pivot = addrAt(high);
            size_t li = (low -1); // index of smaller element

            for (int j = low; j <= high - 1; j ++) {
                if (fnc(at(j),pivot->item)) {
                    li++;
                    try {
                        swap(li, j);
                    } catch (std::exception& ex) {
                        std::cerr << ex.what() << std::endl;
                    }
                }
            }

            try {
                swap(li + 1, high);
            } catch (std::exception& ex) {
                std::cerr << ex.what() << std::endl;
            }
            return (li + 1);
        }

        ///Quicksort lancolt listara
        ///Forras, ami alapjan implementalva van:
        ///https://www.geeksforgeeks.org/quick-sort/
        ///@param low - a lista elso eleme ahonnan a quicksortot inditjuk
        ///@param high - a lista utolso eleme (ameddig a quicksort tart)
        ///@param fnc - egy osszehasonlito fuggveny ami alapjan a rendezes tortenik
        void quickSort(size_t low, size_t high, bool fnc(T i, T i2)) {
            if (low < high) {
                size_t pi = partition(low, high, fnc);

                if (pi != 0)
                    quickSort(low, pi - 1, fnc);
                quickSort(pi + 1, high, fnc);
            }
        }

    public:
        size_t currentSize = 0;

        List() {}

        List(T first) {
            head = new ListItem<T>(first);
        }

        ///Beallitja a lancolt lista elso elemet
        ///felteve, hogy a lista eddig teljesen ures volt.
        ///@param first - az elem amivel kezdeni szeretnenk
        void setHead(T first) {
            if (head == NULL)
                head = new ListItem<T>(first);
        }

        ///Hozzaad egy uj elemet a lancolt listahoz
        ///@param newItem - az uj elem
        void addItem(T newItem) {
            ListItem<T>* iter = head;
            if (iter == NULL) {
                head = new ListItem<T>(newItem);
            } else {
                while (iter->next != NULL)
                    iter = iter->next;
                iter->next = new ListItem<T>(newItem);
                currentSize++;
            }
        }

        ///Quicksort ami az egesz lista lefut
        ///@param fnc - osszehasonlito fuggveny ami alapjan a rendezes tortenik
        void sort(bool fnc(T i, T i2)) {
            quickSort(0,currentSize,fnc);
        }

        ListItem <T>* getHead() const {return head;}

        ///Visszaadja a lista egy adott indexu elemet
        ///@param idx - index
        ///@return - adott indexu elem
        T at(size_t idx) {
            if ((idx >= 0) && (idx <= currentSize)) {
                size_t i = 0;
                ListItem<T>* iter = head;
                while(iter != NULL) {
                    if (i == idx)
                        return iter->item;
                    i++;
                    iter = iter->next;
                }
            } else {
                std::stringstream err;
                err << "index is out of range: " << idx;
                throw std::out_of_range(err.str());
            }

            return NULL;
        }

        ///Visszaadja a lista egy adott indexen talalhato memoria cimet
        ///@param idx - index
        ///@return - adott indexu elem memoriacime
        ListItem<T>* addrAt(size_t idx) {
            if ((idx >= 0) && (idx <= currentSize)) {
                size_t i = 0;
                ListItem<T>* iter = head;
                while(iter != NULL) {
                    if (i == idx)
                        return iter;
                    i++;
                    iter = iter->next;
                }
            } else {
                std::stringstream err;
                err << "index is out of range: " << idx;
                throw std::out_of_range(err.str());
            }

            return NULL;
        }

        ///Egy fuggveny alapjan keres elemet a listabol.
        ///Az elso olyan elemmel ter vissza ami teljesiti
        ///a kereso fuggveny feltetele(i)t.
        ///@param fnc - fuggveny ami alapjan adott elemet kereseni lehet
        ///@return - az elso elem amire a biztositott fuggveny igazzal tert vissza
        T searchBy(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return iter->item;
                iter = iter->next;
            }

            throw std::domain_error("No item in the list satisfies the search function provided.");
        }

        ///Egy fuggveny alapjan keres elemet a listabol.
        ///Az elso olyan elem memoria cimevel ter vissza
        ///ami teljesiti a kereso fuggveny feltetele(i)t.
        ///@param fnc - fuggveny ami alapjan adott elemet kereseni lehet
        ///@return - az elso elem memoriaja amire a biztositott fuggveny igazzal tert vissza
        ListItem<T>* pSearchBy(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return iter;
                iter = iter->next;
            }
            //Nincs kozte -> NULL
            return NULL;
        }

        ///Egy igaz/hamis fuggveny-t vegig futtat a lista
        ///minden elemen, es amint talal akar egyet is igazzal ter vissza.
        ///@param fnc - fuggveny pointer elem vizsgalasahoz
        ///@return - tartalmaz-e adott tulajdonsagu elemet
        bool doesItContain(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return true;
                iter = iter->next;
            }
            return false;
        }

        ///Kitorli a lista egy adott indexen talalhato elemet
        ///@param idx - kitorlendo elem indexe
        void deleteAt(size_t idx) {
            if ((idx >= 0) && (idx <= currentSize)) {
                try {
                    if (idx == 0) {
                        if (head != NULL) {
                            if (head->next != NULL) {
                                ListItem<T>* next = head->next;
                                delete head;
                                head = next;
                            } else {
                                delete head;
                                head = NULL;
                            }
                        }
                    } else if (addrAt(idx)->next == NULL) {
                        ListItem<T>* del = addrAt(idx);
                        delete del;
                        addrAt(idx-1)->next = NULL;
                    } else {
                        ListItem<T>* del = addrAt(idx);
                        ListItem<T>* tmp = addrAt(idx+1);
                        addrAt(idx-1)->next = tmp;
                        delete del;
                    }

                    if (currentSize > 0)
                        currentSize--;
                } catch  (std::exception& ex) {
                    std::cerr << "Could not delete item at index: " << idx << " reason being: " << ex.what() << std::endl;
                }
            } else {
                throw std::out_of_range("del idx is out of range.");
            }
        }

        ///A lista egy adoot indexu elemen lefuttat
        ///egy fuggveny (pl.: ha a lanc dinamikusan foglalt
        ///elemeket tartalmaz, akkor ez valamilyen delete fgvny)
        ///majd kitorli az elemet a listabol.
        ///@param idx - kitorlendo elem indexe
        ///@param fnc - fuggveny ami a torlendo elemen lefut
        void deleteAt(size_t idx, void fnc(T)) {
            if ((idx >= 0) && (idx <= currentSize)) {
                try {
                    if (idx == 0) {
                        if (head != NULL) {
                            if (head->next != NULL) {
                                ListItem<T>* next = head->next;
                                fnc(head->item);
                                delete head;
                                head = next;
                            } else {
                                fnc(head->item);
                                delete head;
                                head = NULL;
                            }
                        }
                    } else if (addrAt(idx)->next == NULL) {
                        //std::cout << "here we are" << std::endl;
                        ListItem<T>* del = addrAt(idx);
                        ListItem<T>* before = addrAt(idx-1);
                        fnc(del->item);
                        delete del;
                        before->next = NULL;
                    } else {
                        ListItem<T>* del = addrAt(idx);
                        ListItem<T>* tmp = addrAt(idx+1);
                        addrAt(idx-1)->next = tmp;
                        fnc(del->item);
                        delete del;
                    }

                    if (currentSize > 0)
                        currentSize--;
                } catch (std::exception& ex) {
                    std::cerr << "Could not delete item at index: " << idx << " reason being: " << ex.what() << std::endl;
                }
            } else {
                throw std::out_of_range("del idx is out of range.");
            }
        }


        ///Beallit egy fuggvenyt ami majd lefut a lista
        ///minden elemere, amikor a listanak a destruktora fut.
        ///@param fnc - a fuggveny
        void setDestructFunction(void fnc(T)) {
            isDestructFucSet = true;
            this->fnc = fnc;
        }

        ~List() {
            ListItem<T>* iter = head;
            while (iter != NULL) {
                ListItem<T>* nextF = iter->next;
                if (isDestructFucSet)
                    fnc(iter->item);
                delete iter;
                iter = nextF;
            }
        }
    };
}

#endif //DOOMCOPY_LIST_H
