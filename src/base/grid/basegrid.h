#ifndef BASEGRID_H
#define BASEGRID_H

#include <optional>
#include <vector>

#include "base/geometry/rect.h"

namespace Base
{
    template<ScalarOrVector T>
    class BaseGrid
    {
        protected:
            PixelRect       dimensions;
            Real            gridConstant;
            std::vector<T>  values;

        public:
            BaseGrid(const PixelRect& dimensions, const Real gridConstant);

            const PixelRect& getPixelDimensions() const;
            RealRect         getRealDimensions() const;

            PixelCoordinate getPixelOrigin() const;
            PixelCoordinate getPixelSize() const;

            RealCoordinate getRealOrigin() const;
            RealCoordinate getRealSize() const;

            Real getGridConstant() const;

            void setOrigin(const PixelCoordinate& origin);
            void setOrigin(const RealCoordinate& origin);

            T& at(const RealCoordinate& coordinate);
            T& at(const PixelCoordinate& coordinate);

            T& operator [](const PixelCoordinate& coordinate);
            T& operator [](const RealCoordinate& coordinate);

            const T& get(const PixelCoordinate& coordinate) const;
            const T& get(const RealCoordinate& coordinate) const;

            const std::vector<T>& exposeValues() const;

        private:
            Pixel getIndexFromPixelCoordinate(const PixelCoordinate& coordinate) const;
    };
}

#endif // BASEGRID_H
