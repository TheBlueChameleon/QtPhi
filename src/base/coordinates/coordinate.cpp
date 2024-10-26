#include "coordinate.txx"

namespace Base
{
    template struct Coordinate<Pixel>;
    template struct Coordinate<Real>;

    template PixelCoordinate min(const PixelCoordinate& a, const PixelCoordinate& b);
    template PixelCoordinate max(const PixelCoordinate& a, const PixelCoordinate& b);

    template RealCoordinate min(const RealCoordinate& a, const RealCoordinate& b);
    template RealCoordinate max(const RealCoordinate& a, const RealCoordinate& b);

    template std::array<Pixel, 4> getBoundariesSorted(const PixelCoordinate& boundary1, const PixelCoordinate& boundary2);
    template std::array<Real,  4> getBoundariesSorted(const  RealCoordinate& boundary1, const  RealCoordinate& boundary2);

    template bool isWithin<Pixel>(const PixelCoordinate& point, const PixelCoordinate& boundary1, const PixelCoordinate& boundary2);
    template bool isWithin<Real>(const Coordinate<Real>& point, const Coordinate<Real>& boundary1, const Coordinate<Real>& boundary2);

    PixelCoordinate toPixelCoordinates(const RealCoordinate& c, Real gridConstant)
    {
        return PixelCoordinate {Pixel(c.x / gridConstant), Pixel(c.y / gridConstant)};
    }

    RealCoordinate toRealCoordinates(const PixelCoordinate& c, Real gridConstant)
    {
        return RealCoordinate {c.x * gridConstant, c.y * gridConstant};
    }
}
