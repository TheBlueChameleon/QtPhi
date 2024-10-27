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

    const auto at_within = PixelCoordinate(+0, +0);
    const auto at_loClip = PixelCoordinate(-2, -2);
    const auto at_hiClip = PixelCoordinate(+2, +2);

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
        imposer.getDstStart(target, at_within),
        PixelCoordinate(-1, -1)
    );
    QCOMPARE(
        imposer.getSrcRect(target, at_within),
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
        imposer.getDstStart(target, at_loClip),
        PixelCoordinate(-2, -2)
    );
    QCOMPARE(
        imposer.getSrcRect(target, at_loClip),
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
        imposer.getDstStart(target, at_hiClip),
        PixelCoordinate(1, 1)
    );
    QCOMPARE(
        imposer.getSrcRect(target, at_hiClip),
        PixelRect(-1, -1, 2, 2)
    );

    // TEST OPTIMIZED VERSION BEHAVES THE SAME
    QCOMPARE(
        imposer.getImposeInfo(target, at_within),
        std::make_pair(imposer.getSrcRect(target, at_within),
                       imposer.getDstStart(target, at_within)
                      )
    );
    QCOMPARE(
        imposer.getImposeInfo(target, at_loClip),
        std::make_pair(imposer.getSrcRect(target, at_loClip),
                       imposer.getDstStart(target, at_loClip)
                      )
    );
    QCOMPARE(
        imposer.getImposeInfo(target, at_hiClip),
        std::make_pair(imposer.getSrcRect(target, at_hiClip),
                       imposer.getDstStart(target, at_hiClip)
                      )
    );
}

void ImposableGridTest::impose()
{
    const Real gridConstant = 2.0;
    const auto imposerDimensions = PixelRect(-1, -1, 3, 3);
    auto imposerReal   = ImposableGrid<Real>(imposerDimensions, gridConstant);
    auto imposerVector = ImposableGrid<Vector>(imposerDimensions, gridConstant);

    const auto targetDimensions = PixelRect(-2, -2, 5, 5);
    auto targetReal   = BaseGrid<Real>(targetDimensions, gridConstant);
    auto targetVector = BaseGrid<Vector>(targetDimensions, gridConstant);

    for (Pixel y = -1; y < 2; ++y)
    {
        for (Pixel x = -1; x < 2; ++x)
        {
            const auto c = PixelCoordinate(x, y);
            imposerReal[c] = 1.0;
            imposerVector[c] = RealCoordinate(1, 1);
        }
    }

    const auto at = PixelCoordinate(+0, +0);

    imposerReal.impose(targetReal, at);
    imposerVector.impose(targetVector, at);
}
