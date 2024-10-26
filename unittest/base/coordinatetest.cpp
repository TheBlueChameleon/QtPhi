#include <iostream>

#include "coordinatetest.h"
#include "base/coordinates/coordinate.h"

using namespace Base;

void CoordinateTest::add_sub_neg()
{
    PixelCoordinates p {1,2}, q {3,4};

    PixelCoordinates add = p + q;
    QVERIFY(add == PixelCoordinates(4, 6));

    PixelCoordinates sub = p - q;
    QVERIFY(sub == PixelCoordinates(-2, -2));

    PixelCoordinates neg = -p;
    QVERIFY(neg == PixelCoordinates(-1, -2));
}

void CoordinateTest::mul_div()
{
    RealCoordinates p {1.5, 2.5};

    RealCoordinates mul = p * 2;
    RealCoordinates div = p / 0.5;

    QVERIFY(mul == RealCoordinates(3, 5));
    QVERIFY(mul == div);
}


