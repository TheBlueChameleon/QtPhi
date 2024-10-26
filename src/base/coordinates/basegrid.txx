#ifndef BASEGRID_TXX
#define BASEGRID_TXX

#include "base/errors.h"
#include "basegrid.h"
#include "coordinate.h"

namespace Base
{
    template<EitherScalarOrVector T>
    PixelCoordinates BaseGrid<T>::getPixelSize() const
    {
        return size;
    }

    template<EitherScalarOrVector T>
    RealCoordinates BaseGrid<T>::getRealSize() const
    {
        return toRealCoordinates(size, gridConstant);
    }

    template<EitherScalarOrVector T>
    Real BaseGrid<T>::getGridConstant() const
    {
        return gridConstant;
    }

    template<EitherScalarOrVector T>
    BaseGrid<T>::BaseGrid(PixelCoordinates size, Real gridConstant) :
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
    PixelCoordinates BaseGrid<T>::getPixelOrigin() const
    {
        return origin;
    }

    template<EitherScalarOrVector T>
    RealCoordinates BaseGrid<T>::getRealOrigin() const
    {
        return toRealCoordinates(origin, gridConstant);
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const PixelCoordinates& o)
    {
        origin = o;
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const RealCoordinates& o)
    {
        origin = toPixelCoordinates(o, gridConstant);
    }

    template<EitherScalarOrVector T>
    PixelCoordinates BaseGrid<T>::getMinPixelCoordinates() const
    {
        return -origin;
    }

    template<EitherScalarOrVector T>
    PixelCoordinates BaseGrid<T>::getMaxPixelCoordinates() const
    {
        return size - origin;
    }

    template<EitherScalarOrVector T>
    RealCoordinates BaseGrid<T>::getMinRealCoordinates() const
    {
        return toRealCoordinates(getMinPixelCoordinates(), gridConstant);
    }

    template<EitherScalarOrVector T>
    RealCoordinates BaseGrid<T>::getMaxRealCoordinates() const
    {
        return toRealCoordinates(getMaxPixelCoordinates(), gridConstant);
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const RealCoordinates& c)
    {
        PixelCoordinates cp = toPixelCoordinates(c, gridConstant);
        return at(cp);
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const PixelCoordinates& c)
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
    T& BaseGrid<T>::operator [](const PixelCoordinates& c)
    {
        const auto shifted = c + origin;
        const Pixel index = shifted.y * size.x + shifted.x;
        return values[index];
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::operator [](const RealCoordinates& c)
    {
        PixelCoordinates cp = toPixelCoordinates(c, gridConstant);
        return (*this)[cp];
    }
}

#endif
