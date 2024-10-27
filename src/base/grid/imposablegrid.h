#ifndef IMPOSABLEGRID_H
#define IMPOSABLEGRID_H

#include "basegrid.h"

namespace Base
{
    template<ScalarOrVector T>
    class ImposableGrid : public BaseGrid<T>
    {
        public:
            using ImposeInfo = std::pair<PixelRect, PixelCoordinate>;

        public:
            ImposableGrid(const PixelRect& dimensions, const Real gridConstant);

            ImposeInfo getImposeInfo(const BaseGrid<T>& targetGrid, const PixelCoordinate& at) const;
            ImposeInfo getImposeInfo(const BaseGrid<T>& targetGrid, const RealCoordinate& at) const;

            PixelRect getSrcRect(const BaseGrid<T>& targetGrid, const PixelCoordinate& at) const;
            PixelRect getSrcRect(const BaseGrid<T>& targetGrid, const RealCoordinate& at) const;

            PixelCoordinate getDstStart(const BaseGrid<T>& targetGrid, const PixelCoordinate& at) const;
            PixelCoordinate getDstStart(const BaseGrid<T>& targetGrid, const RealCoordinate& at) const;

            void impose(BaseGrid<T>& targetGrid, const PixelCoordinate at) const;
            void impose(BaseGrid<T>& targetGrid, const RealCoordinate  at) const;
    };
}

#endif // IMPOSABLEGRID_H
