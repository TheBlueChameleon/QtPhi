#include "rect.txx"

namespace Base
{
    template Rect<Pixel>::Rect(const PixelCoordinatePair&);
    template Rect<Real>::Rect(const RealCoordinatePair&);

    template struct Rect<Pixel>;
    template struct Rect<Real>;
}
