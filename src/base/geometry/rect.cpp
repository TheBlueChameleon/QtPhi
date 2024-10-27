#include "rect.txx"

namespace Base
{
    // ====================================================================== //
    // Rect instantiations

    template struct Rect<Pixel>;
    template struct Rect<Real>;

    // ====================================================================== //
    // Rect template specializations

    template Rect<Pixel>::Rect(const PixelCoordinatePair&);
    template Rect<Real>::Rect(const RealCoordinatePair&);

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
        return PixelRect(PixelCoordinatePair(origin, size));
    }

    template<>
    RealRect Rect<Pixel>::toRealRect(const Real gridConstant) const
    {
        const auto origin = this->getMin().toRealCoordinate(gridConstant);
        const auto size   = this->getSize().toRealCoordinate(gridConstant);
        return RealRect(RealCoordinatePair(origin, size));
    }

    template<>
    RealRect Rect<Real>::toRealRect([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    template<>
    const PixelRectIterator Rect<Pixel>::begin() const
    {
        return PixelRectIterator(*this);
    }

    template<>
    const PixelRectIterator Rect<Real>::begin() const
    {
        throw IllegalStateError("Iterating over a non-discrete rect");
    }

    template<>
    const PixelRectIterator Rect<Pixel>::end() const
    {
        return PixelRectIterator();
    }

    template<>
    const PixelRectIterator Rect<Real>::end() const
    {
        throw IllegalStateError("Iterating over a non-discrete rect");
    }

    // ====================================================================== //
    // iterator

    PixelRectIterator::PixelRectIterator(const PixelRect& rect) :
        x(rect.x), y(rect.y), w(rect.w), h(rect.h),
        currentCoordinate(rect.getMin())
    {}

    // prefix operator
    PixelRectIterator& PixelRectIterator::operator++()
    {
        ++currentCoordinate.x;
        if (currentCoordinate.x >= x + w)
        {
            currentCoordinate.x = x;
            ++currentCoordinate.y;
        }

        if (currentCoordinate.y >= y + h)
        {
            *this = PixelRectIterator();
        }

        return *this;
    }

    // postfix operator
    PixelRectIterator PixelRectIterator::operator++(int)
    {
        const auto temp = *this;
        ++(*this);
        return temp;
    }

    PixelRectIterator::reference PixelRectIterator::operator*() const
    {
        return currentCoordinate;
    }

    PixelRectIterator::pointer PixelRectIterator::operator->() const
    {
        return &currentCoordinate;
    }
}
