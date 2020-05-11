//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_LIST_H
#define DOOMCOPY_LIST_H
#include <iostream>

//#include "DoomCopy.h"

namespace DoomCopy {

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

    template <typename T>
    class List {
        ListItem<T>* head = NULL;

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


                    //nagy = kisebb->next
                    //kisebb->next->next = kisebb
                    //tmp = kisebb->next->next;
                    //kisebb->next = tmp;
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
                    swap(li,j);
                }
            }

            swap(li + 1, high);
            return (li + 1);
        }

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

        void setHead(T first) {
            head = new ListItem<T>(first);
        }

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

        void printData() {
            ListItem<T>* iter = head;
            int i = 0;
            while (iter->next != NULL) {
                std::cout << iter->item << std::endl;
                i++;
                iter = iter->next;
            }
            std::cout << iter->item << std::endl;
        }

        void sort(bool fnc(T i, T i2)) {
            quickSort(0,currentSize,fnc);
        }

        ListItem <T>* getHead() const {return head;}

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
                throw std::out_of_range("idx is out of range.");
            }
        }

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
                throw std::out_of_range("idx is out of range.");
            }
            //return head;
        }

        T searchBy(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return iter->item;
                iter = iter->next;
            }

            throw "well shit.... Nincs közte...";
        }

        ListItem<T>* pSearchBy(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return iter;
                iter = iter->next;
            }

            throw "well shit.... Nincs közte...";
        }

        bool doesItContain(bool fnc(T)) {
            ListItem<T>* iter = head;
            while(iter != NULL) {
                if (fnc(iter->item))
                    return true;
                iter = iter->next;
            }
            return false;
        }

        ~List() {
            ListItem<T>* iter = head;
            while (iter != NULL) {
                ListItem<T>* nextF = iter->next;
                delete iter;
                iter = nextF;
            }
        }
    };
}

#endif //DOOMCOPY_LIST_H
