#ifndef GRID_H
#define GRID_H

#include "base/concepts.h"
#include "coordinate.h"

namespace Base
{
    template<ScalarOrVector T>
    struct Grid
    {
        virtual PixelRect getPixelDimensions() const = 0;
        virtual RealRect getRealDimensions() const = 0;

        virtual PixelCoordinate getPixelOrigin() const = 0;
        virtual PixelCoordinate getPixelSize() const = 0;

        virtual RealCoordinate getRealOrigin() const = 0;
        virtual RealCoordinate getRealSize() const = 0;

        virtual Real getGridConstant() const = 0;

        virtual void setOrigin(const PixelCoordinate& o) = 0;
        virtual void setOrigin(const RealCoordinate& o) = 0;

        virtual T& at(const RealCoordinate& c) = 0;
        virtual T& at(const PixelCoordinate& c) = 0;

        virtual T& operator[](const PixelCoordinate& c) = 0;
        virtual T& operator[](const RealCoordinate& c) = 0;
    };
}
#endif // GRID_H
