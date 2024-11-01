#include <iostream>

#include "base/errors.h"
#include "base/interpolation/interpolation.h"
#include "basegrid.h"

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
    const T& BaseGrid<T>::get(const PixelCoordinate& coordinate) const
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    const T BaseGrid<T>::get(const RealCoordinate& coordinate) const
    {
        /* construct this rect for interpolation purpose:
         *
         * FOR POSITIVE COORDINATES         | FOR NEGATIVE COORDINATES
         *  anchor   p2                     |     p4   p3
         *       *---*                      |      *---*
         *       | * |  ·· coordinate.y     |      | * |  ·· coordinate.y
         *       *---*  ·· y2               |      *---*  ·· y2
         *      p3 : p4                     |     p2 : anchor
         *         : :                      |      : :
         *         : x2                     |     x2 :
         *      coordinate.x                |     coordinate.x
         */

        const auto anchor = coordinate.toPixelCoordinate(gridConstant);
        const auto minCoords = dimensions.getMin();
        const auto maxCoords = dimensions.getMax();

        // safety override: p2..p4 not within the grid
        if (anchor == maxCoords || anchor == minCoords)
        {
            return this->get(anchor);
        }

        // toPixelCoordinate uses truncate => round to zero.
        // ensure that anchor plus p2..p4 enclose coordinate
        const auto x2 = anchor.x + (coordinate.x >= anchor.x ? 1 : -1);
        const auto y2 = anchor.y + (coordinate.y >= anchor.x ? 1 : -1);

        const auto p2 = PixelCoordinate(x2, anchor.y);
        const auto p3 = PixelCoordinate(anchor.x, y2);
        const auto p4 = PixelCoordinate(p2.x, p3.y);

        // safety override. p2, p3 not in grid: interpolate only using y
        if (x2 > maxCoords.x || x2 < minCoords.x)
        {
            const auto v1 = get(anchor);
            const auto v2 = get(p3);
            return Interpolation::linear(
                       coordinate.y,
                       anchor.y, v1,
                       y2, v2
                   );
        }

        // safety override. p3, p4 not in grid: interpolate only using y
        if (y2 > maxCoords.y | y2 < minCoords.y)
        {
            const auto v1 = get(anchor);
            const auto v2 = get(p2);
            return Interpolation::linear(
                       coordinate.x,
                       anchor.x, v1,
                       x2, v2
                   );
        }

        const auto r1 = anchor.toRealCoordinate(gridConstant);
        const auto r4 = p4.toRealCoordinate(gridConstant);

        const auto v1 = get(anchor);
        const auto v2 = get(p2);
        const auto v3 = get(p3);
        const auto v4 = get(p4);

        return Interpolation::planar(coordinate,
                                     r1, r4,
                                     v1, v2,
                                     v3, v4);
    }

    template<ScalarOrVector T>
    const std::vector<T>& BaseGrid<T>::exposeValues() const
    {
        return values;
    }

    // ====================================================================== //
    // instantiations

    template class BaseGrid<Scalar>;
    template class BaseGrid<Vector>;
}
