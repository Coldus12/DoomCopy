//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_ARRAY2D_H
#define DOOMCOPY_ARRAY2D_H

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                Array2D                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///Generikus ketdimenzios tomb
///@param T - adattipus
namespace DoomCopy {
    template <class T>
    class Array2D {
        bool destroyed = true;
    public:
        T** data;
        int rows;
        int columns;

        ///A ketdimenzios tomb konstruktore
        ///@param rows - a ketdimenzios tombben levo sorok szama
        ///@param columns - a ketdimenzios tombben levo oszlopok szama
        Array2D(int rows = 0, int columns = 0) {
            destroyed = false;
            this->rows = rows;
            this->columns = columns;
            data = new T*[this->rows];
            for (int i = 0; i < this->rows; i++) {
                data[i] = new T[this->columns];
            }
        }

        void inline free() {
            if (rows != 0) {
                for (int j = 0; j < rows; j++) {
                    delete[] data[j];
                }
            }
            delete[] data;
        }

        ///Virtualis destruktor
        ///Felszabaditja a dinamikusan lefoglalt memoriateruleteket
        virtual ~Array2D() {
            if (!destroyed) {
                if (rows != 0) {
                    for (int j = 0; j < rows; j++) {
                        delete[] data[j];
                    }
                }
                delete[] data;
                destroyed = true;
            }
        }

    };

    template class Array2D<double>;
    template class Array2D<int>;
    template class Array2D<short>;
    template class Array2D<long>;
    template class Array2D<float>;
}



#endif //DOOMCOPY_ARRAY2D_H
