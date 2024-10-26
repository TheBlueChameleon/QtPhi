#ifndef GRIDFACTORY_H
#define GRIDFACTORY_H

#include "base/coordinates/coordinate.h"
#include "potential/potentialgrid.h"

namespace Physics
{
    class GridFactory
    {
        private:
            static const Base::PixelCoordinate USE_DEFAULT;

            Base::PixelCoordinate size;
            Base::Real gridConstant;

        public:
            GridFactory(Base::PixelCoordinate size, Base::Real gridConstant);

            PotentialGrid makeWorld() const;
            PotentialGrid makeOverlayAtConstantLevel(Base::Real level, Base::PixelCoordinate size = USE_DEFAULT) const;
            PotentialGrid makeOverlayFromCharge(Base::Real charge, Base::Real cutoff = 0.1) const;
    };
}

#endif // GRIDFACTORY_H
