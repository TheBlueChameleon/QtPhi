#ifndef IMPOSABLEGRID_H
#define IMPOSABLEGRID_H

#include "basegrid.h"

namespace Base
{
    template<ScalarOrVector T>
    class ImposableGrid : public BaseGrid<T>
    {
        public:
            ImposableGrid(const PixelRect& dimensions, const Real gridConstant);

            PixelRect getSrcRect(const Grid<T>& targetGrid, const PixelCoordinate& at) const;
            PixelRect getSrcRect(const Grid<T>& targetGrid, const RealCoordinate& at) const;

            PixelCoordinate getDstStart(const Grid<T>& targetGrid, const PixelCoordinate& at) const;
            PixelCoordinate getDstStart(const Grid<T>& targetGrid, const RealCoordinate& at) const;
    };
}

#endif // IMPOSABLEGRID_H
