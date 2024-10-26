#ifndef BASEGRID_H
#define BASEGRID_H

#include <vector>

#include "grid.h"

namespace Base
{
    template<EitherScalarOrVector T>
    class BaseGrid : public Grid<T>
    {
        protected:
            PixelCoordinates size;
            PixelCoordinates origin;
            Real gridConstant;
            std::vector<T> values;

        public:
            BaseGrid(PixelCoordinates size, Real gridConstant);

            // Grid interface
            PixelCoordinates getPixelSize() const;
            RealCoordinates getRealSize() const;

            Real getGridConstant() const;

            PixelCoordinates getPixelOrigin() const;
            RealCoordinates getRealOrigin() const;
            void setOrigin(const PixelCoordinates& o);
            void setOrigin(const RealCoordinates& o);

            PixelCoordinates getMinPixelCoordinates() const;
            PixelCoordinates getMaxPixelCoordinates() const;
            RealCoordinates getMinRealCoordinates() const;
            RealCoordinates getMaxRealCoordinates() const;

            T& at(const RealCoordinates& c);
            T& at(const PixelCoordinates& c);
            T& operator [](const PixelCoordinates& c);
            T& operator [](const RealCoordinates& c);
    };
}

#endif // BASEGRID_H
