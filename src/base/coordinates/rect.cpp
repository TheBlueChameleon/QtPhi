#include "rect.txx"

namespace Base
{
    template<>
    Coordinate<Pixel> Rect<Pixel>::getMax() const
    {
        return Coordinate<Pixel>(x + w - 1, y + h - 1);
    }

    template<>
    Coordinate<Real> Rect<Real>::getMax() const
    {
        return Coordinate<Real>(x + w, y + h);
    }

    template Rect<Pixel>::Rect(const PixelCoordinatePair&);
    template Rect<Real>::Rect(const RealCoordinatePair&);

    template struct Rect<Pixel>;
    template struct Rect<Real>;
}
