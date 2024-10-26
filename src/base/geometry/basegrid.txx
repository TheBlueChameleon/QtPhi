#ifndef BASEGRID_TXX
#define BASEGRID_TXX

#include "base/errors.h"
#include "basegrid.h"
#include "coordinate.h"

namespace Base
{
    template<EitherScalarOrVector T>
    BaseGrid<T>::BaseGrid(const PixelRect& dimensions, const Real gridConstant):
        dimensions(dimensions),
        gridConstant(gridConstant),
        values(std::vector<T>(dimensions.w * dimensions.h))
    {}

    template<EitherScalarOrVector T>
    PixelRect BaseGrid<T>::getPixelDimensions() const
    {
        return dimensions;
    }

    template<EitherScalarOrVector T>
    RealRect BaseGrid<T>::getRealDimensions() const
    {
        return RealRect(RealCoordinatePair(getRealOrigin(), getRealSize()));
    }

    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelOrigin() const
    {
        return PixelCoordinate(dimensions.x, dimensions.y);
    }

    template<EitherScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelSize() const
    {
        return PixelCoordinate(dimensions.w, dimensions.h);
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealOrigin() const
    {
        return toRealCoordinate(getPixelOrigin(), gridConstant);
    }

    template<EitherScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealSize() const
    {
        return toRealCoordinate(getPixelSize(), gridConstant);
    }

    template<EitherScalarOrVector T>
    Real BaseGrid<T>::getGridConstant() const
    {
        return gridConstant;
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const PixelCoordinate& origin)
    {
        dimensions.x = origin.x;
        dimensions.y = origin.y;
    }

    template<EitherScalarOrVector T>
    void BaseGrid<T>::setOrigin(const RealCoordinate& origin)
    {
        setOrigin(toPixelCoordinate(origin, gridConstant));
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const RealCoordinate& coordinate)
    {
        PixelCoordinate pixelCoordinate = toPixelCoordinate(coordinate, gridConstant);
        return at(pixelCoordinate);
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::at(const PixelCoordinate& coordinate)
    {
        if (this->dimensions.contains(coordinate))
        {
            return (*this)[coordinate];
        }
        else
        {
            throw CoordinatesError("Coordinate out of bounds");
        }
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::operator [](const PixelCoordinate& coordinate)
    {
        const auto shiftedByOrigin = coordinate + dimensions.getMin();
        const Pixel index = shiftedByOrigin.y * dimensions.w + shiftedByOrigin.x;
        return values[index];
    }

    template<EitherScalarOrVector T>
    T& BaseGrid<T>::operator [](const RealCoordinate& coordinate)
    {
        PixelCoordinate pixelCoordinate = toPixelCoordinate(coordinate, gridConstant);
        return (*this)[pixelCoordinate];
    }
}

#endif
