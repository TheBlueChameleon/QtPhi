#include <algorithm>
#include <ranges>

#include "base/errors.h"
#include "base/interpolation/interpolation.h"
#include "gridimpl.h"

namespace Base
{
    template<ScalarOrVector T>
    GridImpl<T>::GridImpl(const PixelRect& dimensions):
        dimensions(dimensions),
        values(std::vector<T>(dimensions.w * dimensions.h))
    {}

    template<ScalarOrVector T>
    GridImpl<T>::GridImpl(const RealRect& dimensions):
        dimensions(dimensions.toPixelRect()),
        values(std::vector<T>(dimensions.w * dimensions.h))
    {}

    template<ScalarOrVector T>
    const PixelRect& GridImpl<T>::getPixelDimensions() const
    {
        return dimensions;
    }

    template<ScalarOrVector T>
    RealRect GridImpl<T>::getRealDimensions() const
    {
        return dimensions.toRealRect();
    }

    template<ScalarOrVector T>
    PixelCoordinate GridImpl<T>::getPixelOrigin() const
    {
        return PixelCoordinate(-dimensions.x, -dimensions.y);
    }

    template<ScalarOrVector T>
    PixelCoordinate GridImpl<T>::getPixelSize() const
    {
        return PixelCoordinate(dimensions.w, dimensions.h);
    }

    template<ScalarOrVector T>
    RealCoordinate GridImpl<T>::getRealOrigin() const
    {
        return getPixelOrigin().toRealCoordinate(dimensions.gridConstant);
    }

    template<ScalarOrVector T>
    RealCoordinate GridImpl<T>::getRealSize() const
    {
        return getPixelSize().toRealCoordinate(dimensions.gridConstant);
    }

    template<ScalarOrVector T>
    Real GridImpl<T>::getGridConstant() const
    {
        return dimensions.gridConstant;
    }

    template<ScalarOrVector T>
    void GridImpl<T>::setOrigin(const PixelCoordinate& origin)
    {
        dimensions.x = -origin.x;
        dimensions.y = -origin.y;
    }

    template<ScalarOrVector T>
    void GridImpl<T>::setOrigin(const RealCoordinate& origin)
    {
        setOrigin(origin.toPixelCoordinate(dimensions.gridConstant));
    }

    template<ScalarOrVector T>
    T& GridImpl<T>::operator [](const PixelCoordinate& coordinate)
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    Pixel GridImpl<T>::getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const
    {
        const auto shiftedByOrigin = coordinate - dimensions.getMin();
        return shiftedByOrigin.y * dimensions.w + shiftedByOrigin.x;
    }

    template<ScalarOrVector T>
    const T& GridImpl<T>::get(const PixelCoordinate& coordinate) const
    {
        return values[getIndexFromPixelCoordinate(coordinate)];
    }

    template<ScalarOrVector T>
    const T GridImpl<T>::get(const RealCoordinate& coordinate) const
    {
        using IPM = GridImpl<T>::InterpolationMethod;

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
                    const auto realCoordinateLo = ipd.p1.toRealCoordinate(dimensions.gridConstant);
                    const auto realCoordinateHi = ipd.p2.toRealCoordinate(dimensions.gridConstant);
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
    GridImpl<T>::InterpolationData GridImpl<T>::getInterpolationData(const RealCoordinate& coordinate) const
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

        using IPD = GridImpl<T>::InterpolationData;
        using IPM = GridImpl<T>::InterpolationMethod;

        const auto anchor = coordinate.toPixelCoordinate(dimensions.gridConstant);
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
    RangeType<Real> GridImpl<T>::getAmplitudeRange() const
    {
        auto transform = [](T element)
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

        return std::ranges::minmax(
                   std::ranges::transform_view(values, transform)
               );
    }

    template<ScalarOrVector T>
    RangeType<T> GridImpl<T>::getValuesRange() const
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
    const std::vector<T>& GridImpl<T>::exposeValues() const
    {
        return values;
    }

    // ====================================================================== //
    // instantiations

    template class GridImpl<Scalar>;
    template class GridImpl<Vector>;
}
