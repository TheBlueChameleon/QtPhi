#ifndef GRID_H
#define GRID_H

#include "base/geometry/rect.h"

namespace Base
{
    template<ScalarOrVector T>
    class GridImpl;

    class Grid
    {
        public:
            virtual const PixelRect& getPixelDimensions() const = 0;
            virtual RealRect         getRealDimensions() const = 0;

            virtual PixelCoordinate  getPixelOrigin() const = 0;
            virtual PixelCoordinate  getPixelSize() const = 0;

            virtual RealCoordinate   getRealOrigin() const = 0;
            virtual RealCoordinate   getRealSize() const = 0;

            virtual Real getGridConstant() const = 0;

            virtual void setOrigin(const PixelCoordinate& origin) = 0;
            virtual void setOrigin(const RealCoordinate& origin) = 0;

            virtual Pixel getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const = 0;

            virtual RangeType<Real> getAmplitudeRange() const = 0;

            template<ScalarOrVector T>
            GridImpl<T>& forContent();

            template<ScalarOrVector T>
            const GridImpl<T>& forContent() const;
    };
}

#endif // GRID_H
