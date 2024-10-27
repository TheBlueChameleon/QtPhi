#ifndef RECT_H
#define RECT_H

#include "base/concepts.h"
#include "base/geometry/coordinate.h"

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
        template<CoordinatePair P> Rect(const P& p);

        Coordinate<T> getMin() const;
        Coordinate<T> getMax() const;
        Coordinate<T> getSize() const;

        bool contains(Coordinate<T> p) const;

        PixelRect toPixelRect(const Real gridConstant) const;
        RealRect  toRealRect(const Real gridConstant) const;

        bool operator==(const Rect<T>& rhs) const = default;

        std::string to_string() const;
    };
}
#endif // RECT_H
