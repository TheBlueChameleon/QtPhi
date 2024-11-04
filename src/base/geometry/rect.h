#ifndef RECT_H
#define RECT_H

#include "base/geometry/coordinate.h"
#include "base/geometry/rectiterator.h"

namespace Base
{
    template<PixelOrReal T>
    struct Rect
    {
        T x;
        T y;
        T w;
        T h;
        Real gridConstant;

        Rect();
        Rect(const T x, const T y, const T w, const T h, Real gridConstant = 1.0);
        Rect(const Coordinate<T>& boundary1, const Coordinate<T>& boundary2, Real gridConstant = 1.0);

        Coordinate<T> getMin() const;
        Coordinate<T> getMax() const;
        Coordinate<T> getSize() const;

        bool contains(Coordinate<T> p) const;

        PixelRect toPixelRect(const Real gridConstant) const;
        RealRect  toRealRect(const Real gridConstant) const;

        bool operator==(const Rect<T>& rhs) const = default;

        std::string to_string() const;

        RectIterator<T> begin() const;

        RectIterator<T> end() const;

    };
}
#endif // RECT_H
