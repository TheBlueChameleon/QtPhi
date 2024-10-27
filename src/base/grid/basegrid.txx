#ifndef BASEGRID_TXX
#define BASEGRID_TXX

#include "base/errors.h"
#include "basegrid.h"
#include "base/geometry/coordinate.h"

namespace Base
{
    template<ScalarOrVector T>
    BaseGrid<T>::BaseGrid(const PixelRect& dimensions, const Real gridConstant):
        dimensions(dimensions),
        gridConstant(gridConstant),
        values(std::vector<T>(dimensions.w * dimensions.h))
    {
        if (gridConstant <= 0.0)
        {
            throw DimensionError("grid constant equal to or less than zero");
        }
    }

    template<ScalarOrVector T>
    const PixelRect& BaseGrid<T>::getPixelDimensions() const
    {
        return dimensions;
    }

    template<ScalarOrVector T>
    RealRect BaseGrid<T>::getRealDimensions() const
    {
        return dimensions.toRealRect(gridConstant);
    }

    template<ScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelOrigin() const
    {
        return PixelCoordinate(-dimensions.x, -dimensions.y);
    }

    template<ScalarOrVector T>
    PixelCoordinate BaseGrid<T>::getPixelSize() const
    {
        return PixelCoordinate(dimensions.w, dimensions.h);
    }

    template<ScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealOrigin() const
    {
        return getPixelOrigin().toRealCoordinate(gridConstant);
    }

    template<ScalarOrVector T>
    RealCoordinate BaseGrid<T>::getRealSize() const
    {
        return getPixelSize().toRealCoordinate(gridConstant);
    }

    template<ScalarOrVector T>
    Real BaseGrid<T>::getGridConstant() const
    {
        return gridConstant;
    }

    template<ScalarOrVector T>
    void BaseGrid<T>::setOrigin(const PixelCoordinate& origin)
    {
        dimensions.x = -origin.x;
        dimensions.y = -origin.y;
    }

    template<ScalarOrVector T>
    void BaseGrid<T>::setOrigin(const RealCoordinate& origin)
    {
        setOrigin(origin.toPixelCoordinate(gridConstant));
    }

    template<ScalarOrVector T>
    T& BaseGrid<T>::at(const RealCoordinate& coordinate)
    {
        PixelCoordinate pixelCoordinate = coordinate.toPixelCoordinate(gridConstant);
        return at(pixelCoordinate);
    }

    template<ScalarOrVector T>
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

    template<ScalarOrVector T>
    Pixel BaseGrid<T>::getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const
    {
        const auto shiftedByOrigin = coordinate - dimensions.getMin();
        return shiftedByOrigin.y * dimensions.w + shiftedByOrigin.x;
    }

    template<ScalarOrVector T>
    T& BaseGrid<T>::operator [](const PixelCoordinate& coordinate)
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    T& BaseGrid<T>::operator [](const RealCoordinate& coordinate)
    {
        PixelCoordinate pixelCoordinate = coordinate.toPixelCoordinate(gridConstant);
        return (*this)[pixelCoordinate];
    }

    template<ScalarOrVector T>
    const T& BaseGrid<T>::get(const PixelCoordinate& coordinate) const
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    const T& BaseGrid<T>::get(const RealCoordinate& coordinate) const
    {
        return get(coordinate.toPixelCoordinate(gridConstant));
    }

    template<ScalarOrVector T>
    const std::vector<T>& BaseGrid<T>::exposeValues() const
    {
        return values;
    }
}

#endif
