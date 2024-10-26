#ifndef BASEGRID_TXX
#define BASEGRID_TXX

#include "base/errors.h"
#include "basegrid.h"
#include "coordinate.h"

namespace Base
{
    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelSize() const
    {
        return size;
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealSize() const
    {
        return toRealCoordinates(size, gridConstant);
    }

    template<EitherScalarOrVector T>
    Real BaseGrid<T>::getGridConstant() const
    {
        return gridConstant;
    }

    template<EitherScalarOrVector T>
    BaseGrid<T>::BaseGrid(PixelCoordinate size, Real gridConstant) :
        size(size), gridConstant(gridConstant)
    {
        if (size.x < 0 || size.y < 0)
        {
            throw DimensionError("Negative Grid Size");
        }
        values = std::vector<T>(size.x * size.y);
        origin = {0, 0};
    }

    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelOrigin() const
    {
        return origin;
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealOrigin() const
    {
        return toRealCoordinates(origin, gridConstant);
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const PixelCoordinate& o)
    {
        origin = o;
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const RealCoordinate& o)
    {
        origin = toPixelCoordinates(o, gridConstant);
    }

    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getMinPixelCoordinates() const
    {
        return -origin;
    }

    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getMaxPixelCoordinates() const
    {
        return size - origin;
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getMinRealCoordinates() const
    {
        return toRealCoordinates(getMinPixelCoordinates(), gridConstant);
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getMaxRealCoordinates() const
    {
        return toRealCoordinates(getMaxPixelCoordinates(), gridConstant);
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const RealCoordinate& c)
    {
        PixelCoordinate cp = toPixelCoordinates(c, gridConstant);
        return at(cp);
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const PixelCoordinate& c)
    {
        if (isWithin(c, getMinPixelCoordinates(), getMaxPixelCoordinates()))
        {
            return (*this)[c];
        }
        else
        {
            throw CoordinatesError("Coordinate out of bounds");
        }
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::operator [](const PixelCoordinate& c)
    {
        const auto shifted = c + origin;
        const Pixel index = shifted.y * size.x + shifted.x;
        return values[index];
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::operator [](const RealCoordinate& c)
    {
        PixelCoordinate cp = toPixelCoordinates(c, gridConstant);
        return (*this)[cp];
    }
}

#endif
