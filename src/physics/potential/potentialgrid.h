#ifndef POTENTIALGRID_H
#define POTENTIALGRID_H

#include "base/coordinates/basegrid.h"

namespace Physics
{
    class PotentialGrid : public Base::BaseGrid<Base::Scalar>
    {

        private:
            void imposeImpl_noAcceleration(const PotentialGrid& potential, const Base::PixelCoordinates& minIdxs, const Base::PixelCoordinates& maxIdxs, const Base::PixelCoordinates& startIdxs);
            void imposeImpl_avxAccelerated(const PotentialGrid& potential, const Base::PixelCoordinates& minIdxs, const Base::PixelCoordinates& maxIdxs, const Base::PixelCoordinates& startIdxs);

        public:
            PotentialGrid();
            PotentialGrid(Base::PixelCoordinates size, Base::Real gridConstant, Base::Real level = 0);

            Base::PixelCoordinates getMinimumImposeIndices(const PotentialGrid& potential, const Base::PixelCoordinates at) const;
            Base::PixelCoordinates getMaximumImposeIndices(const PotentialGrid& potential, const Base::PixelCoordinates at) const;

            void imposeAt(const PotentialGrid& potential, const Base::RealCoordinates  at);
            void imposeAt(const PotentialGrid& potential, const Base::PixelCoordinates at);

            std::string to_string() const;
    };
}

#endif // POTENTIALGRID_H
