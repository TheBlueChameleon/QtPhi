#ifndef IMPOSABLEGRID_H
#define IMPOSABLEGRID_H

#include "gridimpl.h"
#include "base/geometry/rectiterator.h"

namespace Base
{
    template<ScalarOrVector T>
    class ImposableGrid : public GridImpl<T>
    {
        public:
            ImposableGrid(const PixelRect& dimensions, const Real gridConstant);

            PixelRect getSrcRect(const GridImpl<T>& targetGrid, const PixelCoordinate& at) const;
            PixelRect getSrcRect(const GridImpl<T>& targetGrid, const RealCoordinate& at) const;

            void impose(GridImpl<T>& targetGrid, const PixelCoordinate at) const;
            void impose(GridImpl<T>& targetGrid, const RealCoordinate  at) const;
    };

    void imposeScalar(GridImpl<Scalar>& targetGrid, const GridImpl<Scalar>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect);
    void imposeVector(GridImpl<Vector>& targetGrid, const GridImpl<Vector>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect);
}

#endif // IMPOSABLEGRID_H
