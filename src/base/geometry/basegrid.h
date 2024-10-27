#ifndef BASEGRID_H
#define BASEGRID_H

#include <vector>

#include "grid.h"
#include "rect.h"

namespace Base
{
    template<ScalarOrVector T>
    class BaseGrid : public Grid<T>
    {
        protected:
            PixelRect       dimensions;
            Real            gridConstant;
            std::vector<T>  values;

        public:
            BaseGrid(const PixelRect& dimensions, const Real gridConstant);

            // Grid interface
            PixelRect getPixelDimensions() const;
            RealRect  getRealDimensions() const;

            PixelCoordinate getPixelOrigin() const;
            PixelCoordinate getPixelSize() const;

            RealCoordinate getRealOrigin() const;
            RealCoordinate getRealSize() const;

            Real getGridConstant() const;

            void setOrigin(const PixelCoordinate& origin);
            void setOrigin(const RealCoordinate& origin);

            T& at(const RealCoordinate& coordinate);
            T& at(const PixelCoordinate& coordinate);

            T& operator [](const PixelCoordinate& coordinate);
            T& operator [](const RealCoordinate& coordinate);
    };
}

#endif // BASEGRID_H
