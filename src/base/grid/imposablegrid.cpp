#include "base/errors.h"
#include "imposablegrid.h"

namespace Base
{
    template<ScalarOrVector T>
    Base::ImposableGrid<T>::ImposableGrid(const PixelRect& dimensions, const Real gridConstant) :
        GridImpl<T>(dimensions, gridConstant)
    {}

    PixelCoordinate clipToPositive(const PixelCoordinate& p)
    {
        return PixelCoordinate(
                   p.x > 0 ? p.x : 0,
                   p.y > 0 ? p.y : 0
               );
    }

    template<ScalarOrVector T>
    PixelRect ImposableGrid<T>::getSrcRect(const GridImpl<T>& targetGrid, const PixelCoordinate& at) const
    {
        const auto targetDimensions = targetGrid.getPixelDimensions();

        const auto unclippedMin = at + this->dimensions.getMin();
        const auto clippedMin = PixelCoordinate::max(unclippedMin, targetDimensions.getMin());
        const auto deltaMin = clipToPositive(clippedMin - unclippedMin);
        const auto srcStart = this->dimensions.getMin() + deltaMin;

        const auto unclippedMax = at + this->dimensions.getMax();
        const auto clippedMax = PixelCoordinate::min(unclippedMax, targetDimensions.getMax());
        const auto deltaMax = clipToPositive(unclippedMax - clippedMax);
        const auto size = this->getPixelSize() - deltaMin - deltaMax;

        return PixelRect(srcStart.x, srcStart.y, size.x, size.y);
    }

    template<ScalarOrVector T>
    PixelRect ImposableGrid<T>::getSrcRect(const GridImpl<T>& targetGrid, const RealCoordinate& at) const
    {
        return getSrcRect(targetGrid, at.toPixelCoordinate(this->gridConstant));
    }

    template<ScalarOrVector T>
    void ImposableGrid<T>::impose(GridImpl<T>& targetGrid, const PixelCoordinate at) const
    {
        const auto srcRect = getSrcRect(targetGrid, at);
        if      constexpr(std::same_as<T, Scalar>)
        {
            imposeScalar(targetGrid, *this, at, srcRect);
        }
        else if constexpr(std::same_as<T, Vector>)
        {
            imposeVector(targetGrid, *this, at, srcRect);
        }
        else
        {
            throw IllegalStateError("Typing Error in ImposableGrid::impose");
        }
    }

    template<ScalarOrVector T>
    void ImposableGrid<T>::impose(GridImpl<T>& targetGrid, const RealCoordinate at) const
    {
        impose(targetGrid, at.toPixelCoordinate(this->gridConstant));
    }

    // ====================================================================== //
    // non class methods

    void imposeScalar(GridImpl<Scalar>& targetGrid, const GridImpl<Scalar>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect)
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

    void imposeVector(GridImpl<Vector>& targetGrid, const GridImpl<Vector>& sourceGrid, const PixelCoordinate at, const PixelRect& srcRect)
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

    // ====================================================================== //
    // instantiations

    template struct ImposableGrid<Real>;
    template struct ImposableGrid<Vector>;
}
