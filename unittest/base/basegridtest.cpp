#include "basegridtest.h"

#include "base/errors.h"
#include "base/geometry/basegrid.h"

using namespace Base;

void BaseGridTest::ctor()
{
    const auto r = PixelRect();

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        BaseGrid<Real>(r, 0)
    );
}

void BaseGridTest::getters()
{
    const Real gridConstant = 2.0;
    const auto r = PixelRect(-1, -2, 3, 4);
    const auto g = BaseGrid<Real>(r, gridConstant);

    QCOMPARE(g.getGridConstant(), gridConstant);
    QCOMPARE(g.getPixelSize(),   PixelCoordinate(3, 4));
    QCOMPARE(g.getPixelOrigin(), PixelCoordinate(1, 2));

    QCOMPARE(g.getRealSize(),   RealCoordinate(6, 8));
    QCOMPARE(g.getRealOrigin(), RealCoordinate(2, 4));
}
