#ifndef GRID_H
#define GRID_H

#include "base/concepts.h"
#include "coordinate.h"

namespace Base
{
    template<EitherScalarOrVector T>
    struct Grid
    {
        virtual PixelCoordinates getPixelSize() const = 0;
        virtual RealCoordinates getRealSize() const = 0;

        virtual Real getGridConstant() const = 0;

        virtual PixelCoordinates getPixelOrigin() const = 0;
        virtual RealCoordinates getRealOrigin() const = 0;
        virtual void setOrigin(const PixelCoordinates& o) = 0;
        virtual void setOrigin(const RealCoordinates& o) = 0;

        virtual PixelCoordinates getMinPixelCoordinates() const = 0;
        virtual PixelCoordinates getMaxPixelCoordinates() const = 0;

        virtual RealCoordinates getMinRealCoordinates() const = 0;
        virtual RealCoordinates getMaxRealCoordinates() const = 0;

        virtual T& at(const RealCoordinates& c) = 0;
        virtual T& at(const PixelCoordinates& c) = 0;

        virtual T& operator[](const PixelCoordinates& c) = 0;
        virtual T& operator[](const RealCoordinates& c) = 0;
    };
}
#endif // GRID_H
