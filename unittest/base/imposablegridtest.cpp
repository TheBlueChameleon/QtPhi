#include <iostream>

#include "imposablegridtest.h"

#include "base/grid/imposablegrid.h"

using namespace Base;

void ImposableGridTest::clipping()
{
    const Real gridConstant = 2.0;
    const auto imposerDimensions = PixelRect(-1, -1, 3, 3);
    const auto imposer = ImposableGrid<Real>(imposerDimensions, gridConstant);

    const auto targetDimensions = PixelRect(-2, -2, 5, 5);
    const auto target = GridImpl<Real>(targetDimensions, gridConstant);

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
        imposer.getSrcRect(target, at_hiClip),
        PixelRect(-1, -1, 2, 2)
    );
}

void ImposableGridTest::impose()
{
    const Real gridConstant = 2.0;
    const auto imposerDimensions = PixelRect(-1, -1, 3, 3);
    auto imposerScalar = ImposableGrid<Scalar>(imposerDimensions, gridConstant);
    auto imposerVector = ImposableGrid<Vector>(imposerDimensions, gridConstant);

    const auto targetDimensions = PixelRect(-2, -2, 5, 5);
    auto targetScalar = GridImpl<Scalar>(targetDimensions, gridConstant);
    auto targetVector = GridImpl<Vector>(targetDimensions, gridConstant);

    const auto at = PixelCoordinate(+0, +0);
    const auto v0 = RealCoordinate(0, 0);
    const auto v1 = RealCoordinate(1, 1);
    const auto v2 = RealCoordinate(2, 2);

    for (const auto c: imposerDimensions)
    {
        imposerScalar[c] = 1.0;
        imposerVector[c] = v1;
    }

    imposerScalar.impose(targetScalar, at);
    const auto expectedScalarValues = std::vector<Scalar>(
    {
        0, 0, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 1, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 0
    });
    QCOMPARE(targetScalar.exposeValues(), expectedScalarValues);

    imposerScalar.impose(targetScalar, PixelCoordinate(-2, -2));
    imposerScalar.impose(targetScalar, PixelCoordinate(+2, +2));
    const auto expectedScalarValues2 = std::vector<Scalar>(
    {
        1, 1, 0, 0, 0,
        1, 2, 1, 1, 0,
        0, 1, 1, 1, 0,
        0, 1, 1, 2, 1,
        0, 0, 0, 1, 1
    });
    QCOMPARE(targetScalar.exposeValues(), expectedScalarValues2);

    imposerVector.impose(targetVector, at);
    const auto expectedVectorValues = std::vector<Vector>(
    {
        v0, v0, v0, v0, v0,
        v0, v1, v1, v1, v0,
        v0, v1, v1, v1, v0,
        v0, v1, v1, v1, v0,
        v0, v0, v0, v0, v0
    });
    QCOMPARE(targetVector.exposeValues(), expectedVectorValues);

}
