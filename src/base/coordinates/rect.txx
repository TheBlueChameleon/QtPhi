#include <format>
#include <string>

#include "base/errors.h"
#include "rect.h"

namespace Base
{
    template<PixelOrReal T>
    Rect<T>::Rect() :
        x(0), y(0),
        w(0), h(0)
    {}

    template<PixelOrReal T>
    Rect<T>::Rect(const T x, const T y, const T w, const T h) :
        x(x), y(y),
        w(w), h(h)
    {
        if (w < 0 || h < 0)
        {
            const std::string errMsg = std::format("Negative dimensions encountered: w={}, h={}", w, h);
            throw DimensionError(errMsg);
        }
    }

    template<PixelOrReal T>
    template<CoordinatePair P>
    Rect<T>::Rect(const P &p):
        x(p.first.x), y(p.first.y),
        w(p.second.x), h(p.second.y)
    {
        static_assert(
            std::is_same_v<T, typename P::first_type::baseType>,
            "type mismatch in CTOR Rect from CoordinatePair"
        );
    }

    template<PixelOrReal T>
    Coordinate<T> Rect<T>::getMin() const
    {
        return Coordinate<T>(x, y);
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
}
