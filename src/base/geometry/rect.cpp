#include "rect.txx"

namespace Base
{
    template Rect<Pixel>::Rect(const PixelCoordinatePair&);
    template Rect<Real>::Rect(const RealCoordinatePair&);

    template struct Rect<Pixel>;
    template struct Rect<Real>;

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
}
