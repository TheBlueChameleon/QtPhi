#include "imposablegridtest.h"

#include "base/geometry/imposablegrid.h"
#include <iostream>

using namespace Base;

void ImposableGridTest::clipping()
{
    const Real gridConstant = 2.0;
    const auto imposerDimensions = PixelRect(-1, -1, 3, 3);
    const auto imposer = ImposableGrid<Real>(imposerDimensions, gridConstant);

    const auto targetDimensions = PixelRect(-2, -2, 5, 5);
    const auto target = BaseGrid<Real>(targetDimensions, gridConstant);

    /* LEGEND
     * # target
     * x imposer
     * . clipped
     */

    /* SCENARIO 1: ALL WITHIN BOUNDARIES
     * # # # # #
     * # x x x #
     * # x x x #
     * # x x x #
     * # # # # #
     */
    QCOMPARE(
        imposer.getDstStart(target, PixelCoordinate(0, 0)),
        PixelCoordinate(-1, -1)
    );
    QCOMPARE(
        imposer.getSrcRect(target, PixelCoordinate(0, 0)),
        PixelRect(-1, -1, 3, 3)
    );

    /* SCENARIO 2: CLIP OUT LOW COORDINATES
     *
     * . . .
     * . x x # # #
     * . x x # # #
     *   # # # # #
     *   # # # # #
     *   # # # # #
     */
    QCOMPARE(
        imposer.getDstStart(target, PixelCoordinate(-2, -2)),
        PixelCoordinate(-2, -2)
    );
    QCOMPARE(
        imposer.getSrcRect(target, PixelCoordinate(-2, -2)),
        PixelRect(0, 0, 2, 2)
    );

    /* SCENARIO 2: CLIP OUT HIGH COORDINATES
     *
     * # # # # #
     * # # # # #
     * # # # # #
     * # # # x x .
     * # # # x x .
     *       . . .
     */
    QCOMPARE(
        imposer.getDstStart(target, PixelCoordinate(2, 2)),
        PixelCoordinate(1, 1)
    );
    QCOMPARE(
        imposer.getSrcRect(target, PixelCoordinate(2, 2)),
        PixelRect(-1, -1, 2, 2)
    );
}
