#include "coordinate.txx"

namespace Base
{
    template struct Coordinate<Pixel>;
    template struct Coordinate<Real>;

    template<>
    PixelCoordinate Coordinate<Pixel>::toPixelCoordinate([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    template<>
    PixelCoordinate Coordinate<Real>::toPixelCoordinate(const Real gridConstant) const
    {
        return PixelCoordinate {Pixel(this->x / gridConstant), Pixel(this->y / gridConstant)};
    }

    template<>
    RealCoordinate Coordinate<Pixel>::toRealCoordinate(const Real gridConstant) const
    {
        return RealCoordinate {this->x * gridConstant, this->y * gridConstant};
    }

    template<>
    RealCoordinate Coordinate<Real>::toRealCoordinate([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }
}
