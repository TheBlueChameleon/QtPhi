#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <limits>

#include "base/concepts.h"

namespace Base
{
    namespace Functions
    {
        enum class Signum
        {
            negative = -1,
            zero = 0,
            positive = +1,
            nan = std::numeric_limits<Pixel>::lowest()
        };

        Signum sign(const Real x);
        bool crossesZero(const Real min, const Real max);
    }
}

#endif // FUNCTIONS_H
