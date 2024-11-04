#include "recttest.h"

#include "base/geometry/rect.h"
#include "base/errors.h"

using namespace Base;

void RectTest::ctor()
{
    const auto p = Rect<Pixel>();
    QCOMPARE(p.x, 0);
    QCOMPARE(p.y, 0);
    QCOMPARE(p.w, 1);
    QCOMPARE(p.h, 1);

    const auto q = Rect(1,2,3,4, 1.0);
    QCOMPARE(q.x, 1);
    QCOMPARE(q.y, 2);
    QCOMPARE(q.w, 3);
    QCOMPARE(q.h, 4);

    const auto r = Rect<Real>();
    QCOMPARE(r.x, 0.0);
    QCOMPARE(r.y, 0.0);
    QCOMPARE(r.w, 1.0);
    QCOMPARE(r.h, 1.0);

    const auto s = Rect(1.,2.,3.,4., 1.0);
    QCOMPARE(s.x, 1.0);
    QCOMPARE(s.y, 2.0);
    QCOMPARE(s.w, 3.0);
    QCOMPARE(s.h, 4.0);

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        Rect(0, 0, 0, 0, 1.0)
    );

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        Rect(0, 0, -1, 1, 1.0)
    );

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        Rect(0, 0, 1, -1, 1.0)
    );

    Rect<Pixel> pr1(PixelCoordinate(0, 0), PixelCoordinate(1, 1), 1.0);
    Rect<Pixel> pr2(PixelCoordinate(0, 1), PixelCoordinate(1, 0), 1.0);

    QCOMPARE(pr1.getMin(), PixelCoordinate(0, 0));
    QCOMPARE(pr1.w, 2);
    QCOMPARE(pr1.h, 2);
    QCOMPARE(pr1, pr2);

    Rect<Real>  rr1(RealCoordinate(0.0, 0.0), RealCoordinate(1.0, 1.0), 1.0);
    Rect<Real>  rr2(RealCoordinate(0.0, 1.0), RealCoordinate(1.0, 0.0), 1.0);

    QCOMPARE(rr1.getMin(), RealCoordinate(0.0, 0.0));
    QCOMPARE(rr1.w, 1.0);
    QCOMPARE(rr1.h, 1.0);
    QCOMPARE(rr1, rr2);
}

void RectTest::getMinMaxSize()
{
    const auto p = Rect(0, 0, 1, 2, 1.0);
    QCOMPARE(p.getMin(),  PixelCoordinate(0, 0));
    QCOMPARE(p.getMax(),  PixelCoordinate(0, 1));
    QCOMPARE(p.getSize(), PixelCoordinate(1, 2));

    const auto r = Rect(0.0, 0.0, 1.0, 2.0, 1.0);
    QCOMPARE(r.getMin(),  RealCoordinate(0, 0));
    QCOMPARE(r.getMax(),  RealCoordinate(1, 2));
    QCOMPARE(r.getSize(), RealCoordinate(1, 2));
}

void RectTest::contains()
{
    const auto p = Rect<Pixel>(0, 0, 1, 2, 1.0);
    QVERIFY(+p.contains(PixelCoordinate(+0, +0)));
    QVERIFY(+p.contains(PixelCoordinate(+0, +1)));
    QVERIFY(!p.contains(PixelCoordinate(+1, +0)));
    QVERIFY(!p.contains(PixelCoordinate(+0, +2)));
    QVERIFY(!p.contains(PixelCoordinate(-1, -1)));

    const auto r = Rect<Real>(0.0, 0.0, 1.0, 2.0, 1.0);
    QVERIFY(+r.contains(RealCoordinate(+0, +0)));
    QVERIFY(+r.contains(RealCoordinate(+0, +1)));
    QVERIFY(+r.contains(RealCoordinate(+1, +0)));
    QVERIFY(+r.contains(RealCoordinate(+0, +2)));
    QVERIFY(+r.contains(RealCoordinate(+1, +2)));
    QVERIFY(!r.contains(RealCoordinate(-1, -1)));
}

void RectTest::iterator()
{
    const auto p = Rect<Pixel>(-1, -2, 3, 4, 2.0);
    const auto r = Rect<Real>(-1, -2, 3, 4, 2.0);

    int pCount = 0;
    for (const auto& c: p)
    {
        ++pCount;
        QVERIFY(p.contains(c));
    }
    QCOMPARE(pCount, p.w * p.h);

    /* grid size is 3.0 x 4.0, so coordinates range from
     * (-1, -2) (inclusive) to (+2, +2) (inclusive)
     * # grid points
     * * integer coordinates
     *
     *  (-1,-2)     (+1,-2)  (+2,-2)
     *     #·····+·····#·····+
     *     :           :     :
     *     #·····+·····#·····+ y=+0
     *     :           :     :
     *     #·····+·····#·····+ y=+2
     */
    int rCount = 0;
    for (const auto& c: r)
    {
        ++rCount;
        QVERIFY(r.contains(c));
    }
    QCOMPARE(rCount, 6);
}
