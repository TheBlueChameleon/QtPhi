#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include "base/concepts.h"

namespace Base
{
    namespace Interpolation
    {
        Real percentage(const Real at, const Real lowerBoundary, const Real upperBoundary);

        template<ScalarOrVector T>
        T linear(const Real at, const Real lowerBound, const T& lowerValue, const Real upperBound, const T& upperValue);

        template<ScalarOrVector T>
        T planar(const RealCoordinate& at,
                 const RealCoordinate& upperLeft, const RealCoordinate& lowerRight,
                 const T& upperLeftValue, const T& upperRightValue,
                 const T& lowerLeftValue, const T& lowerRightValue
                );
    }
}

#endif // INTERPOLATION_H
