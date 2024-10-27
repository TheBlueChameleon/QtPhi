#include "basegridtest.h"

#include "base/errors.h"
#include "base/grid/basegrid.h"
#include <iostream>

using namespace Base;

void BaseGridTest::ctor()
{
    const auto r = PixelRect();

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        BaseGrid<Real>(r, 0)
    );
}

void BaseGridTest::getDimensionData()
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

void BaseGridTest::dataAccess()
{
    const auto dimension = PixelRect(-1, -2, 3, 4);
    auto grid = BaseGrid<Real>(dimension, 1.0);

    Real v = 0;
    for (Pixel y = dimension.getMin().y; y <= dimension.getMax().y; ++y)
    {
        for (Pixel x = dimension.getMin().x; x <= dimension.getMax().x; ++x)
        {
            const auto c = PixelCoordinate(x, y);
            grid[c] = v++;
        }
    }

    auto expected = std::vector<Real>(dimension.w * dimension.h);
    std::iota(expected.begin(), expected.end(), 0);
    QCOMPARE(
        grid.exposeValues(),
        expected
    );
}
