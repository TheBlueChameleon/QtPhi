#include "recttest.h"

#include "base/coordinates/rect.h"
#include "base/errors.h"

using namespace Base;

void RectTest::ctor()
{
    const auto p = Rect<Pixel>();
    QCOMPARE(p.x, 0);
    QCOMPARE(p.y, 0);
    QCOMPARE(p.w, 0);
    QCOMPARE(p.h, 0);

    const auto q = Rect(1,2,3,4);
    QCOMPARE(q.x, 1);
    QCOMPARE(q.y, 2);
    QCOMPARE(q.w, 3);
    QCOMPARE(q.h, 4);

    const auto r = Rect<Real>();
    QCOMPARE(r.x, 0.0);
    QCOMPARE(r.y, 0.0);
    QCOMPARE(r.w, 0.0);
    QCOMPARE(r.h, 0.0);

    const auto s = Rect(1.,2.,3.,4.);
    QCOMPARE(s.x, 1.0);
    QCOMPARE(s.y, 2.0);
    QCOMPARE(s.w, 3.0);
    QCOMPARE(s.h, 4.0);

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        Rect(0, 0, -1, 0)
    );

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        Rect(0, 0, 0, -1)
    );

    Base::PixelCoordinatePair pp(PixelCoordinate(0, 0), PixelCoordinate(1,1));
    Base::RealCoordinatePair rp(RealCoordinate(0, 0), RealCoordinate(1,1));

    Rect<Pixel> pr(pp);
    Rect<Real>  rr(rp);
}

void RectTest::getMinMax()
{
    const auto p = Rect(0, 0, 1, 2);
    QCOMPARE(p.getMin(), PixelCoordinate(0, 0));
    QCOMPARE(p.getMax(), PixelCoordinate(0, 1));


    const auto r = Rect(0.0, 0.0, 1.0, 2.0);
    QCOMPARE(r.getMin(), RealCoordinate(0, 0));
    QCOMPARE(r.getMax(), RealCoordinate(1, 2));
}

void RectTest::contains()
{
    const auto p = Rect(0, 0, 1, 2);
    QVERIFY(p.contains(PixelCoordinate(0,0)));
    QVERIFY(p.contains(PixelCoordinate(0,1)));
    QVERIFY(!p.contains(PixelCoordinate(1,0)));
    QVERIFY(!p.contains(PixelCoordinate(0,2)));
    QVERIFY(!p.contains(PixelCoordinate(-1,-1)));

    const auto r = Rect(0.0, 0.0, 1.0, 2.0);
    QVERIFY(r.contains(RealCoordinate(0,0)));
    QVERIFY(r.contains(RealCoordinate(0,1)));
    QVERIFY(r.contains(RealCoordinate(1,0)));
    QVERIFY(r.contains(RealCoordinate(0,2)));
    QVERIFY(r.contains(RealCoordinate(1,2)));
    QVERIFY(!r.contains(RealCoordinate(-1,-1)));
}
