#include "coordinate.txx"

namespace Base
{
    template struct Coordinate<Pixel>;
    template struct Coordinate<Real>;

    PixelCoordinate toPixelCoordinate(const RealCoordinate& c, Real gridConstant)
    {
        return PixelCoordinate {Pixel(c.x / gridConstant), Pixel(c.y / gridConstant)};
    }

    RealCoordinate toRealCoordinate(const PixelCoordinate& c, Real gridConstant)
    {
        return RealCoordinate {c.x * gridConstant, c.y * gridConstant};
    }
}
