#ifndef GRIDIMPL_H
#define GRIDIMPL_H

#include <vector>

#include "base/geometry/rect.h"

#include "grid.h"

namespace Base
{
    template<ScalarOrVector T>
    class GridImpl : public virtual Grid
    {
        public:
            enum class InterpolationMethod
            {
                Planar, LinearX, LinearY, Point
            };
            struct InterpolationData
            {
                GridImpl<T>::InterpolationMethod interpolationMethod;
                PixelCoordinate p1;
                PixelCoordinate p2;
            };

        protected:
            PixelRect       dimensions;
            Real            gridConstant;
            std::vector<T>  values;

        public:
            GridImpl(const PixelRect& dimensions, const Real gridConstant);

            const PixelRect& getPixelDimensions() const;
            RealRect         getRealDimensions() const;

            PixelCoordinate  getPixelOrigin() const;
            PixelCoordinate  getPixelSize() const;

            RealCoordinate   getRealOrigin() const;
            RealCoordinate   getRealSize() const;

            Real getGridConstant() const;

            void setOrigin(const PixelCoordinate& origin);
            void setOrigin(const RealCoordinate& origin);

            T& operator [](const PixelCoordinate& coordinate);
            Pixel getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const;

            const T& get(const PixelCoordinate& coordinate) const;
            const T  get(const RealCoordinate& coordinate) const;
            GridImpl<T>::InterpolationData getInterpolationData(const RealCoordinate& coordinate) const;

            RangeType<Real> getAmplitudeRange() const;
            RangeType<T> getValuesRange() const;

            const std::vector<T>& exposeValues() const;

    };
}

#endif // GRIDIMPL_H
