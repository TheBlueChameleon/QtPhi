#ifndef BASEGRID_H
#define BASEGRID_H

#include <vector>

#include "grid.h"
#include "rect.h"

namespace Base
{
    template<EitherScalarOrVector T>
    class BaseGrid : public Grid<T>
    {
        protected:
            Rect<Pixel> dimensions;

            PixelCoordinate size;
            PixelCoordinate origin;
            Real gridConstant;
            std::vector<T> values;

        public:
            BaseGrid(PixelCoordinate size, Real gridConstant);

            // Grid interface
            PixelCoordinate getPixelSize() const;
            RealCoordinate getRealSize() const;

            Real getGridConstant() const;

            PixelCoordinate getPixelOrigin() const;
            RealCoordinate getRealOrigin() const;
            void setOrigin(const PixelCoordinate& o);
            void setOrigin(const RealCoordinate& o);

            PixelCoordinate getMinPixelCoordinates() const;
            PixelCoordinate getMaxPixelCoordinates() const;
            RealCoordinate getMinRealCoordinates() const;
            RealCoordinate getMaxRealCoordinates() const;

            T& at(const RealCoordinate& c);
            T& at(const PixelCoordinate& c);
            T& operator [](const PixelCoordinate& c);
            T& operator [](const RealCoordinate& c);
    };
}

#endif // BASEGRID_H
