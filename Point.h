//
// Created by coldus on 5/8/20.
//

#ifndef DOOMCOPY_POINT_H
#define DOOMCOPY_POINT_H


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                  Point                                                         ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace DoomCopy {
    class Point {
    public:
        double x;
        double y;
        Point() {}
        Point(double x, double y) : x(x), y(y) {}
    };
}

#endif //DOOMCOPY_POINT_H
