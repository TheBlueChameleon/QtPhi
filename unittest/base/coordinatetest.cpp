#include "coordinatetest.h"
#include "base/geometry/coordinate.h"

using namespace Base;

void CoordinateTest::add_sub_neg()
{
    PixelCoordinate p {1,2}, q {3,4};

    PixelCoordinate add = p + q;
    QVERIFY(add == PixelCoordinate(4, 6));

    PixelCoordinate sub = p - q;
    QVERIFY(sub == PixelCoordinate(-2, -2));

    PixelCoordinate neg = -p;
    QVERIFY(neg == PixelCoordinate(-1, -2));
}

void CoordinateTest::mul_div()
{
    RealCoordinate p {1.5, 2.5};

    RealCoordinate mul = p * 2;
    RealCoordinate div = p / 0.5;

    QVERIFY(mul == RealCoordinate(3, 5));
    QVERIFY(mul == div);
}

void CoordinateTest::gridConstant()
{
    PixelCoordinate p {1, 2};
    RealCoordinate  q {2.0, 4.0};

    // real transformation
    QCOMPARE(p.toRealCoordinate(2.0), q);
    QCOMPARE(q.toPixelCoordinate(2.0), p);

    // identity transformation
    QCOMPARE(p.toPixelCoordinate(2.0), p);
    QCOMPARE(q.toRealCoordinate(2.0), q);
}


