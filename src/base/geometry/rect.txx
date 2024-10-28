#include <algorithm>
#include <format>
#include <string>

#include "base/errors.h"
#include "rect.h"

namespace Base
{
    template<PixelOrReal T>
    void assertPositiveExtent(const Rect<T>& r)
    {
        if (r.w <= 0 || r.h <= 0)
        {
            const std::string errMsg = std::format("Negative dimensions encountered: w={}, h={}", r.w, r.h);
            throw DimensionError(errMsg);
        }
    }

    template<PixelOrReal T>
    Rect<T>::Rect() :
        x(0), y(0),
        w(1), h(1)
    {}

    template<PixelOrReal T>
    Rect<T>::Rect(const T x, const T y, const T w, const T h) :
        x(x), y(y),
        w(w), h(h)
    {
        assertPositiveExtent(*this);
    }

    template<PixelOrReal T>
    template<CoordinatePair P>
    Rect<T>::Rect(const P& p)
    {
        static_assert(
            std::is_same_v<T, typename P::first_type::baseType>,
            "type mismatch in CTOR Rect from CoordinatePair"
        );

        const auto [x1, x2] = std::minmax(p.first.x, p.second.x);
        const auto [y1, y2] = std::minmax(p.first.y, p.second.y);

        this->x = x1;
        this->y = y1;
        this->w = x2 - x1 + (std::is_integral_v<T>);
        this->h = y2 - y1 + (std::is_integral_v<T>);

        assertPositiveExtent(*this);
    }

    template<PixelOrReal T>
    Coordinate<T> Rect<T>::getMin() const
    {
        return Coordinate<T>(x, y);
    }

    template<PixelOrReal T>
    Coordinate<T> Rect<T>::getMax() const
    {
        return Coordinate<T>(
                   x + w - std::is_integral_v<T>,
                   y + h - std::is_integral_v<T>
               );
    }

    template<PixelOrReal T>
    Coordinate<T> Rect<T>::getSize() const
    {
        return Coordinate<T>(w, h);
    }

    template<PixelOrReal T>
    bool Rect<T>::contains(Coordinate<T> p) const
    {
        bool result = true;
        const auto q = this->getMax();

        result &= (p.x >= this->x);
        result &= (p.y >= this->y);
        result &= (p.x <= q.x);
        result &= (p.y <= q.y);

        return result;
    }

    template<PixelOrReal T>
    std::string Rect<T>::to_string() const
    {
        return std::format("Rect ({}, {}) x ({}, {})", this->x, this->y, this->w, this->h);
    }

    template<PixelOrReal T>
    template<class Q>
    std::enable_if<std::is_integral<Q>::value, const PixelRectIterator>::type
    Rect<T>::begin() const
    {
        return PixelRectIterator(*this);
    }

    template<PixelOrReal T>
    template<class Q>
    std::enable_if<std::is_integral<Q>::value, const PixelRectIterator>::type
    Rect<T>::end() const
    {
        return PixelRectIterator();
    }
}
