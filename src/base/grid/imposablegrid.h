#ifndef IMPOSABLEGRID_H
#define IMPOSABLEGRID_H

#include "basegrid.h"
#include "base/geometry/pixelrectiterator.h"

namespace Base
{
    template<ScalarOrVector T>
    class ImposableGrid : public BaseGrid<T>
    {
        public:
            ImposableGrid(const PixelRect& dimensions, const Real gridConstant);

            PixelRect getSrcRect(const BaseGrid<T>& targetGrid, const PixelCoordinate& at) const;
            PixelRect getSrcRect(const BaseGrid<T>& targetGrid, const RealCoordinate& at) const;

            void impose(BaseGrid<T>& targetGrid, const PixelCoordinate at) const;
            void impose(BaseGrid<T>& targetGrid, const RealCoordinate  at) const;
    };

    void imposeScalar(BaseGrid<Scalar>& targetGrid, const BaseGrid<Scalar>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect);
    void imposeVector(BaseGrid<Vector>& targetGrid, const BaseGrid<Vector>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect);
}

#endif // IMPOSABLEGRID_H
