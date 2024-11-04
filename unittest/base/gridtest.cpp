#include <iostream>

#include "gridtest.h"

#include "base/errors.h"
#include "base/grid/gridimpl.h"

using namespace Base;

void GridTest::ctor()
{
    const auto r = PixelRect();

    QVERIFY_THROWS_EXCEPTION(
        DimensionError,
        GridImpl<Real>(r, 0)
    );
}

void GridTest::getDimensionData()
{
    const Real gridConstant = 2.0;
    const auto r = PixelRect(-1, -2, 3, 4, 1.0);
    const auto g = GridImpl<Real>(r, gridConstant);

    QCOMPARE(g.getGridConstant(), gridConstant);
    QCOMPARE(g.getPixelSize(),   PixelCoordinate(3, 4));
    QCOMPARE(g.getPixelOrigin(), PixelCoordinate(1, 2));

    QCOMPARE(g.getRealSize(),   RealCoordinate(6, 8));
    QCOMPARE(g.getRealOrigin(), RealCoordinate(2, 4));
}

void GridTest::dataAccess()
{
    const auto dimension = PixelRect(-1, -2, 3, 4, 1.0);
    auto grid = GridImpl<Real>(dimension, 1.0);

    for (const auto& c: grid.getPixelDimensions())
    {
        grid[c] = grid.getIndexFromPixelCoordinate(c);
    }

    auto expected = std::vector<Real>(dimension.w * dimension.h);
    std::iota(expected.begin(), expected.end(), 0);
    QCOMPARE(
        grid.exposeValues(),
        expected
    );
}

void GridTest::interpolation()
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

    const auto dimension = PixelRect(-2, -2, 5, 5, 1.0);
    auto grid = GridImpl<Real>(dimension, 1.0);

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

void GridTest::boundaryInterpolation()
{
    const auto dimension = PixelRect(-2, -2, 5, 5, 1.0);
    auto grid = GridImpl<Real>(dimension, 1.0);

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

void GridTest::minMax()
{
    const auto dimension = PixelRect(-2, -2, 5, 5, 1.0);
    auto grid = GridImpl<Real>(dimension, 1.0);

    grid[PixelCoordinate(+1, +2)] = +1;
    grid[PixelCoordinate(+2, +2)] = +2;
    grid[PixelCoordinate(+1, +1)] = +3;
    grid[PixelCoordinate(+2, +1)] = +4;

    grid[PixelCoordinate(-1, -2)] = -1;
    grid[PixelCoordinate(-2, -2)] = -2;
    grid[PixelCoordinate(-1, -1)] = -3;
    grid[PixelCoordinate(-2, -1)] = -4;

    const auto range = grid.getValuesRange();

    QCOMPARE(range.min, -4.0);
    QCOMPARE(range.max, +4.0);
}
