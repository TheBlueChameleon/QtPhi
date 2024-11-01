#include <iostream>

#include "interpolationtest.h"

#include "base/geometry/coordinate.h"
#include "base/interpolation/interpolation.h"

using namespace Base;

void InterpolationTest::percentage()
{
    QCOMPARE(Interpolation::percentage(0.1, 0., 1.), 0.1);
    QCOMPARE(Interpolation::percentage(1.1, 1., 2.), 0.1);
    QCOMPARE(Interpolation::percentage(1.1, 2., 1.), 0.9);  // reverse order of lower and upper boundary
}

void InterpolationTest::linear()
{
    /*          lower  at     upper
     *              |---*-----|
     * coordinate: +1  1.4   +2
     * value:      -1 -0.2   +1
     */

    QCOMPARE(
        Interpolation::linear(1.4,
                              1., -1.,
                              2., +1.),
        -0.2
    );

    QCOMPARE(
        Interpolation::linear(1.4,
                              1., RealCoordinate(-1, -1),
                              2., RealCoordinate(+1, +1)
                             ).x,       // QTEST has fuzzyCompare but does not detect float nested in struct.
        -0.2
    );
    QCOMPARE(
        Interpolation::linear(1.4,
                              1., RealCoordinate(-1, -1),
                              2., RealCoordinate(+1, +1)
                             ).y,
        -0.2
    );

    /* "Reverse boundaries interpolation"
     *         lower  at   upper
     *             |--*----|
     * coordinate: 2 1.1   1
     * value:      1 1.9   2
     */

    QCOMPARE(
        Interpolation::linear(1.1,
                              2., 1.,
                              1., 2.),
        1.9
    );
}

void InterpolationTest::planar()
{
    /*    coordinates       values
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
     *
     */
    QCOMPARE(
        Interpolation::planar(RealCoordinate(1.5, 1.25),
                              RealCoordinate(1, 2), RealCoordinate(2, 1),
                              1., 2.,
                              3., 4.),
        3.0
    );


    /* "compatible with screen coordinates"
     *   coordinates         values
     *   (1,1)   (2,1)     1       2
     *     *---U---*       *---u---*
     *     |   X   |       |   X   |
     *     |       |       |       |
     *     *---L---*       *---l---*
     *   (1,2)   (2,2)     3       4
     *
     *   X = (1.5, 1.25)  x = 0.25 * 3.5 + 0.75 * 1.5 = 2.0
     *   U = (1.5, 2.00)  u = 1.5
     *   L = (1.5, 1.00)  l = 3.5
     *
     */
    QCOMPARE(
        Interpolation::planar(RealCoordinate(1.5, 1.25),
                              RealCoordinate(1, 1), RealCoordinate(2, 2),
                              1., 2.,
                              3., 4.),
        2.0
    );
}
