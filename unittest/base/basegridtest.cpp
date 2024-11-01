#include <iostream>

#include "basegridtest.h"

#include "base/errors.h"
#include "base/grid/basegrid.h"

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
    for (const auto& c: grid.getPixelDimensions())
    {
        grid[c] = v++;
    }

    auto expected = std::vector<Real>(dimension.w * dimension.h);
    std::iota(expected.begin(), expected.end(), 0);
    QCOMPARE(
        grid.exposeValues(),
        expected
    );
}

void BaseGridTest::interpolation()
{
    /* GRID OVERALL:
     *   0 0 0 1 2
     *   0 0 0 3 4
     *   0 0 0 0 0
     *   4 3 0 0 0
     *   2 1 0 0 0
     *
     * INTERPOLATION SCHEME:
     *  (flipped for negative coordinates)
     *     coordinates       values
     *   (1,2)   (2,2)     1       2
     *     *---U---*       *---u---*
     *     |       |       |       |
     *     |   X   |       |   x   |
     *     *---L---*       *---l---*
     *   (1,1)   (2,1)     3       4
     *
     *   X = (1.5, 1.25)  x = 0.75 * 3.5 + 0.25 * 1.5 = 3.0
     *   U = (1.5, 2.00)  u = 1.5
     *   L = (1.5, 1.00)  l = 3.5
     */

    const auto dimension = PixelRect(-2, -2, 5, 5);
    auto grid = BaseGrid<Real>(dimension, 1.0);

    grid[PixelCoordinate(+1, +2)] = 1;
    grid[PixelCoordinate(+2, +2)] = 2;
    grid[PixelCoordinate(+1, +1)] = 3;
    grid[PixelCoordinate(+2, +1)] = 4;

    grid[PixelCoordinate(-1, -2)] = 1;
    grid[PixelCoordinate(-2, -2)] = 2;
    grid[PixelCoordinate(-1, -1)] = 3;
    grid[PixelCoordinate(-2, -1)] = 4;

    QCOMPARE(grid.get(RealCoordinate(+1.5, +1.25)), 3.0);
    QCOMPARE(grid.get(RealCoordinate(-1.5, -1.25)), 3.0);

    QCOMPARE(grid.get(RealCoordinate(+2.0, +2.0)), 2.0);
    QCOMPARE(grid.get(RealCoordinate(-2.0, -2.0)), 2.0);
}

void BaseGridTest::boundaryInterpolation()
{
    const auto dimension = PixelRect(-2, -2, 5, 5);
    auto grid = BaseGrid<Real>(dimension, 1.0);

    grid[PixelCoordinate(+2, +0)] = 5;
    grid[PixelCoordinate(-2, +0)] = 5;
    grid[PixelCoordinate(+0, +2)] = 5;
    grid[PixelCoordinate(+0, -2)] = 5;
    grid[PixelCoordinate(-2, +2)] = 5;
    grid[PixelCoordinate(+2, -2)] = 5;
    grid[PixelCoordinate(+2, +2)] = 5;
    grid[PixelCoordinate(-2, -2)] = 5;

    const auto north = RealCoordinate(+0.0, +2.0);
    const auto south = RealCoordinate(+0.0, -2.0);
    const auto east  = RealCoordinate(+2.0, +0.0);
    const auto west  = RealCoordinate(-2.0, +0.0);
    const auto diaPP = RealCoordinate(+2.0, +2.0);
    const auto diaPM = RealCoordinate(-2.0, +2.0);
    const auto diaMM = RealCoordinate(-2.0, -2.0);
    const auto diaMP = RealCoordinate(+2.0, -2.0);

    const auto points = {north, south, east, west, diaPP, diaPM, diaMM, diaMP};

    for (const auto& p : points)
    {
        const auto ipd = grid.getInterpolationData(p);

        QVERIFY(grid.getPixelDimensions().contains(ipd.p1));
        QVERIFY(grid.getPixelDimensions().contains(ipd.p2));
        QCOMPARE(grid.get(p), 5.0);
    }
}
