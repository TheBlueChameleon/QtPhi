#ifndef BASEGRID_H
#define BASEGRID_H

#include <vector>

#include "base/geometry/rect.h"

namespace Base
{
    template<ScalarOrVector T>
    class BaseGrid
    {
        public:
            enum class InterpolationMethod
            {
                Planar, LinearX, LinearY, Point
            };
            struct InterpolationData
            {
                BaseGrid<T>::InterpolationMethod interpolationMethod;
                PixelCoordinate p1;
                PixelCoordinate p2;
            };

        protected:
            PixelRect       dimensions;
            Real            gridConstant;
            std::vector<T>  values;

        public:
            BaseGrid(const PixelRect& dimensions, const Real gridConstant);

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

            const T& get(const PixelCoordinate& coordinate) const;
            const T  get(const RealCoordinate& coordinate) const;

            BaseGrid<T>::InterpolationData getInterpolationData(const RealCoordinate& coordinate) const;

            const std::vector<T>& exposeValues() const;

        private:
            Pixel getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const;
    };
}

#endif // BASEGRID_H
