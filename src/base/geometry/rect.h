#ifndef RECT_H
#define RECT_H

#include "base/concepts.h"
#include "base/geometry/coordinate.h"

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
        template<CoordinatePair P> Rect(const P& p);

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

    class PixelRectIterator
    {
        public:
            using iterator_category = std::input_iterator_tag;
            using iterator_concept  = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = PixelCoordinate;
            using pointer           = const PixelCoordinate*;
            using reference         = const PixelCoordinate&;

        private:
            Pixel x;
            Pixel y;
            Pixel w;
            Pixel h;
            value_type currentCoordinate;

        public:
            PixelRectIterator() = default;
            PixelRectIterator(const PixelRectIterator& other) = default;
            PixelRectIterator(PixelRectIterator&& other) = default;
            PixelRectIterator(const PixelRect& rect);

            PixelRectIterator& operator++();        // prefix operator
            PixelRectIterator  operator++(int);     // postfix operator

            reference operator*() const;
            pointer   operator->() const;

            bool operator==(const PixelRectIterator& it) const = default;
            bool operator!=(const PixelRectIterator& it) const = default;

            PixelRectIterator& operator=(const PixelRectIterator& other) = default;
            PixelRectIterator& operator=(PixelRectIterator&& other) = default;
    };
}
#endif // RECT_H
