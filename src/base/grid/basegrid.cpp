#include <algorithm>
#include <ranges>

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
    T& BaseGrid<T>::operator [](const PixelCoordinate& coordinate)
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    Pixel BaseGrid<T>::getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const
    {
        const auto shiftedByOrigin = coordinate - dimensions.getMin();
        return shiftedByOrigin.y * dimensions.w + shiftedByOrigin.x;
    }

    template<ScalarOrVector T>
    const T& BaseGrid<T>::get(const PixelCoordinate& coordinate) const
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    const T BaseGrid<T>::get(const RealCoordinate& coordinate) const
    {
        using IPM = BaseGrid<T>::InterpolationMethod;

        const auto ipd = getInterpolationData(coordinate);
        const auto valueLo = get(ipd.p1);
        const auto valueHi = get(ipd.p2);

        switch (ipd.interpolationMethod)
        {
            case IPM::Point:
                return valueHi;

            case IPM::LinearX:
                return Interpolation::linear(
                           coordinate.x,
                           ipd.p1.x, valueLo,
                           ipd.p2.x, valueHi
                       );

            case IPM::LinearY:
                return Interpolation::linear(
                           coordinate.y,
                           ipd.p1.y, valueLo,
                           ipd.p2.y, valueHi
                       );

            case IPM::Planar:
                {
                    const auto valueLR = get(PixelCoordinate(ipd.p2.x, ipd.p1.y));
                    const auto valueUL = get(PixelCoordinate(ipd.p1.x, ipd.p2.y));
                    const auto realCoordinateLo = ipd.p1.toRealCoordinate(gridConstant);
                    const auto realCoordinateHi = ipd.p2.toRealCoordinate(gridConstant);
                    return Interpolation::planar(coordinate,
                                                 realCoordinateLo, realCoordinateHi,
                                                 valueLo, valueLR,
                                                 valueUL, valueHi);
                }
            default:
                throw IllegalStateError("Unknown InterpolationMethod in BaseGrid::get(RealCoordinate)");
        };
    }

    template<ScalarOrVector T>
    BaseGrid<T>::InterpolationData BaseGrid<T>::getInterpolationData(const RealCoordinate& coordinate) const
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

        using IPD = BaseGrid<T>::InterpolationData;
        using IPM = BaseGrid<T>::InterpolationMethod;

        const auto anchor = coordinate.toPixelCoordinate(gridConstant);
        const auto maxCoords = dimensions.getMax();

        // safety override: p2..p4 not within the grid
        if (anchor == maxCoords)
        {
            // no check for == minCoordinates needed -- see below
            return IPD(IPM::Point, anchor, anchor);
        }

        /* toPixelCoordinate uses truncate => round to zero.
         * ensure that anchor plus p2..p4 enclose coordinate */
        /* ">=" (instead of e.g. ">") gives bias to (+x, +y)
         * ==> no need for minCoords */
        const auto x2 = anchor.x + (coordinate.x >= anchor.x ? 1 : -1);
        const auto y2 = anchor.y + (coordinate.y >= anchor.y ? 1 : -1);

        const auto p2 = PixelCoordinate(x2, anchor.y);
        const auto p3 = PixelCoordinate(anchor.x, y2);
        const auto p4 = PixelCoordinate(p2.x, p3.y);

        // safety override. p2, p3 not in grid: interpolate only using y
        if (x2 > maxCoords.x)
        {
            return IPD(IPM::LinearY, anchor, p3);
        }

        // safety override. p3, p4 not in grid: interpolate only using y
        if (y2 > maxCoords.y)
        {
            return IPD(IPM::LinearX, anchor, p2);
        }

        return IPD(IPM::Planar, anchor, p4);
    }

    template<ScalarOrVector T>
    const RangeType<T> BaseGrid<T>::getValuesRange() const
    {
        auto prj = [](T element)
        {
            if constexpr(std::is_same<T, Scalar>::value)
            {
                return element;
            }
            else
            {
                return element.length();
            }
        };

        return std::ranges::minmax(values, {}, prj);

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
