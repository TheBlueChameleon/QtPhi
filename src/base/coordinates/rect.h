#ifndef RECT_H
#define RECT_H

#include "base/concepts.h"
#include "base/coordinates/coordinate.h"

namespace Base
{
    template<PixelOrReal T>
    struct Rect
    {
        T x;
        T y;
        T w;
        T h;

        Rect();
        Rect(const T x, const T y, const T w, const T h);

        template<CoordinatePair P>
        Rect(const P& p);

        Coordinate<T> getMin() const;
        Coordinate<T> getMax() const;

        bool contains(Coordinate<T> p) const;
    };
}
#endif // RECT_H