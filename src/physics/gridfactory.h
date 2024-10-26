#ifndef GRIDFACTORY_H
#define GRIDFACTORY_H

#include "base/coordinates/coordinate.h"
#include "potential/potentialgrid.h"

namespace Physics
{
    class GridFactory
    {
        private:
            static const Base::PixelCoordinates USE_DEFAULT;

            Base::PixelCoordinates size;
            Base::Real gridConstant;

        public:
            GridFactory(Base::PixelCoordinates size, Base::Real gridConstant);

            PotentialGrid makeWorld() const;
            PotentialGrid makeOverlayAtConstantLevel(Base::Real level, Base::PixelCoordinates size = USE_DEFAULT) const;
            PotentialGrid makeOverlayFromCharge(Base::Real charge, Base::Real cutoff = 0.1) const;
    };
}

#endif // GRIDFACTORY_H
