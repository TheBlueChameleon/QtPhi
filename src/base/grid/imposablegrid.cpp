#include "imposablegrid.txx"

namespace Base
{
    template struct ImposableGrid<Real>;
    template struct ImposableGrid<Vector>;

    void imposeScalar(Base::BaseGrid<Base::Scalar>& targetGrid, const BaseGrid<Scalar>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect)
    {
#ifdef ENABLE_AVX
        throw std::runtime_error("AVX ACCELERATION not implemented yet");
#else
        for (const auto offset : srcRect)
        {
            const auto dstCoord = at + offset;
            targetGrid[dstCoord] += sourceGrid.get(offset);
        }
#endif
    }

    void imposeVector(BaseGrid<Vector>& targetGrid, const BaseGrid<Vector>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect)
    {

    }

}
