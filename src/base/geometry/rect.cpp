#include <algorithm>
#include <format>

#include "base/errors.h"
#include "rectiterator.h"
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
        w(1), h(1),
        gridConstant(1)
    {}

    template<PixelOrReal T>
    Rect<T>::Rect(const T x, const T y, const T w, const T h, Real gridConstant) :
        x(x), y(y),
        w(w), h(h),
        gridConstant(gridConstant)
    {
        assertPositiveExtent(*this);
    }

    template<PixelOrReal T>
    Rect<T>::Rect(const Coordinate<T>& boundary1, const Coordinate<T>& boundary2, Real gridConstant) :
        gridConstant(gridConstant)
    {
        const auto [x1, x2] = std::minmax(boundary1.x, boundary2.x);
        const auto [y1, y2] = std::minmax(boundary1.y, boundary2.y);

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

    // ...................................................................... //
    // template specializations

    template<>
    PixelRect Rect<Pixel>::toPixelRect([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    template<>
    PixelRect Rect<Real>::toPixelRect(const Real gridConstant) const
    {
        const auto origin = this->getMin().toPixelCoordinate(gridConstant);
        const auto size   = this->getSize().toPixelCoordinate(gridConstant);
        return PixelRect(origin.x, origin.y, size.x, size.y, gridConstant);
    }

    template<>
    RealRect Rect<Pixel>::toRealRect(const Real gridConstant) const
    {
        const auto origin = this->getMin().toRealCoordinate(gridConstant);
        const auto size   = this->getSize().toRealCoordinate(gridConstant);
        return RealRect(origin.x, origin.y, size.x, size.y, gridConstant);
    }

    template<>
    RealRect Rect<Real>::toRealRect([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    // ...................................................................... //

    template<PixelOrReal T>
    std::string Rect<T>::to_string() const
    {
        return std::format("Rect ({}, {}) x ({}, {})", this->x, this->y, this->w, this->h);
    }

    template<PixelOrReal T>
    template<class Q>
    std::enable_if<std::is_integral<Q>::value, const RectIterator>::type
    Rect<T>::begin() const
    {
        return RectIterator(*this);
    }

    template<PixelOrReal T>
    template<class Q>
    std::enable_if<std::is_integral<Q>::value, const RectIterator>::type
    Rect<T>::end() const
    {
        return RectIterator();
    }

    // ====================================================================== //
    // instantiations

    template struct Rect<Pixel>;
    template struct Rect<Real>;

    template typename std::enable_if<std::is_integral<Pixel>::value, const RectIterator>::type Rect<Pixel>::begin<Pixel>() const;
    template typename std::enable_if<std::is_integral<Pixel>::value, const RectIterator>::type Rect<Pixel>::end<Pixel>() const;
}
