#ifndef POTENTIALGRID_H
#define POTENTIALGRID_H

#include "base/geometry/basegrid.h"

namespace Physics
{
    class PotentialGrid : public Base::BaseGrid<Base::Scalar>
    {
        public:
            PotentialGrid();
            PotentialGrid(const Base::PixelRect& dimensions, Base::Real gridConstant, Base::Real level = 0);

            Base::PixelCoordinate getMinimumImposeIndices(const PotentialGrid& targetPotential, const Base::PixelCoordinate at) const;
            Base::PixelCoordinate getMaximumImposeIndices(const PotentialGrid& targetPotential, const Base::PixelCoordinate at) const;

            void imposeAt(const PotentialGrid& targetPotential, const Base::RealCoordinate  at);
            void imposeAt(const PotentialGrid& targetPotential, const Base::PixelCoordinate at);

            std::string to_string() const;

        private:
#ifdef ENABLE_AVX
            void imposeImpl_avxAccelerated(const PotentialGrid& targetPotential, const Base::PixelCoordinate& minIdxs, const Base::PixelCoordinate& maxIdxs, const Base::PixelCoordinate& startIdxs);
#else
            void imposeImpl_noAcceleration(const PotentialGrid& targetPotential, const Base::PixelCoordinate& minIdxs, const Base::PixelCoordinate& maxIdxs, const Base::PixelCoordinate& startIdxs);
#endif
    };
}

#endif // POTENTIALGRID_H
