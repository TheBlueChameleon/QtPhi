#include "interpolation.h"
#include "base/geometry/coordinate.h"

namespace Base
{
    namespace Interpolation
    {
        Real percentage(const Real at, const Real lowerBoundary, const Real upperBoundary)
        {
            return (at - lowerBoundary) / (upperBoundary - lowerBoundary);
        }

        template<ScalarOrVector T>
        T linear(const Real at, const Real lowerBound, const T& lowerValue, const Real upperBound, const T& upperValue)
        {
            const auto p = percentage(at, lowerBound, upperBound);
            return upperValue * p  + lowerValue * (1-p);
        }

        template<ScalarOrVector T>
        T planar(
            const RealCoordinate& at,
            const RealCoordinate& upperLeft, const RealCoordinate& lowerRight,
            const T& upperLeftValue, const T& upperRightValue,
            const T& lowerLeftValue, const T& lowerRightValue
        )
        {
            const auto upper = linear(at.x,
                                      upperLeft.x,  upperLeftValue,
                                      lowerRight.x, upperRightValue);
            const auto lower = linear(at.x,
                                      upperLeft.x,  lowerLeftValue,
                                      lowerRight.x, lowerRightValue);
            return linear(at.y,
                          upperLeft.y,  upper,
                          lowerRight.y, lower);
        }

        // ================================================================== //
        // instantiations

        template Scalar linear(const Real at, const Real lowerBound, const Scalar& lowerValue, const Real upperBound, const Scalar& upperValue);
        template Vector linear(const Real at, const Real lowerBound, const Vector& lowerValue, const Real upperBound, const Vector& upperValue);

        template Scalar planar(const RealCoordinate& at,
                               const RealCoordinate& upperLeft, const RealCoordinate& lowerRight,
                               const Scalar& upperLeftValue, const Scalar& upperRightValue,
                               const Scalar& lowerLeftValue, const Scalar& lowerRightValue);
        template Vector planar(const RealCoordinate& at,
                               const RealCoordinate& upperLeft, const RealCoordinate& lowerRight,
                               const Vector& upperLeftValue, const Vector& upperRightValue,
                               const Vector& lowerLeftValue, const Vector& lowerRightValue);
    }
}
