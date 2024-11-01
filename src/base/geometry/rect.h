#ifndef RECT_H
#define RECT_H

#include "base/geometry/coordinate.h"
#include "base/geometry/pixelrectiterator.h"

namespace Base
{
    class PixelRectIterator;

    template<PixelOrReal T>
    struct Rect
    {
        T x;
        T y;
        T w;
        T h;

        Rect();
        Rect(const T x, const T y, const T w, const T h);
        Rect(const Coordinate<T>& boundary1, const Coordinate<T>& boundary2);

        Coordinate<T> getMin() const;
        Coordinate<T> getMax() const;
        Coordinate<T> getSize() const;

        bool contains(Coordinate<T> p) const;

        PixelRect toPixelRect(const Real gridConstant) const;
        RealRect  toRealRect(const Real gridConstant) const;

        bool operator==(const Rect<T>& rhs) const = default;

        std::string to_string() const;

        template<class Q = T>
        typename std::enable_if<std::is_integral<Q>::value, const PixelRectIterator>::type
        begin() const;

        template<class Q = T>
        typename std::enable_if<std::is_integral<Q>::value, const PixelRectIterator>::type
        end() const;
    };
}
#endif // RECT_H
