#include <cmath>

#include "functions.h"
#include "base/errors.h"

namespace Base
{
    namespace Functions
    {
        Signum sign(const Real x)
        {
            // *INDENT-OFF*
            if (x == 0) {return Signum::zero;}
            if (x  > 0) {return Signum::positive;}
            if (x  < 0) {return Signum::negative;}
            // *INDENT-ON*

            return Signum::nan;
        }

        bool crossesZero(const Real min, const Real max)
        {
            return std::abs(static_cast<int>(sign(min)) + static_cast<int>(sign(max))) == 0;
        }

    }
}
