#include "imposablegrid.txx"
#include <iostream>

namespace Base
{
    template struct ImposableGrid<Real>;
    template struct ImposableGrid<Vector>;

    template<>
    void ImposableGrid<Real>::impose(BaseGrid<Real>& targetGrid, const PixelCoordinate at) const
    {
        std::cout << "### IMPOSE ON SCALAR GRID" << std::endl;

        const auto& [srcRect, dstStart] = getImposeInfo(targetGrid, at);

#ifdef ENABLE_AVX
        throw std::runtime_error("AVX ACCELERATION not implemented yet");
#else
        // const auto width = maxIdxs.x - minIdxs.x + 1;
        // const auto potBegin  = targetPotential.values.begin();
        // const auto selfBegin = this->values.begin();

        // for (auto y = minIdxs.y; y <= maxIdxs.y; ++y)
        // {
        //     const auto from = to_index(minIdxs.x, y, targetPotential.getPixelSize().x);
        //     const auto till = from + width;
        //     const auto to   = to_index(startIdxs.x, startIdxs.y + y - minIdxs.y, getPixelSize().x);

        //     std::transform(potBegin + from, potBegin + till,
        //                    selfBegin + to,
        //                    selfBegin + to,
        //                    std::plus<> {}
        //                   );
        // }
#endif
    }

    template<>
    void ImposableGrid<Vector>::impose(BaseGrid<Vector>& targetGrid, const PixelCoordinate at) const
    {
        std::cout << "### IMPOSE ON VECTOR GRID" << std::endl;
    }
}
