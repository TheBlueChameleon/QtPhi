#include "base/coordinates/rect.h"

using namespace Base;

void noRectWithMismatchingCoordinatePair()
{
    Base::PixelCoordinatePair pp(PixelCoordinate(0, 0), PixelCoordinate(1,1));
    Base::RealCoordinatePair rp(RealCoordinate(0, 0), RealCoordinate(1,1));

    Rect<Real> rr(pp);
}

int main()
{
    noRectWithMismatchingCoordinatePair();
}

