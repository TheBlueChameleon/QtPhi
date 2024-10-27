#include <algorithm>

#include <immintrin.h>

#include "potentialgrid.h"

using namespace Base;
namespace Physics
{
    PotentialGrid::PotentialGrid():
        BaseGrid<Scalar>(PixelRect(), 1.0)
    {}

    PotentialGrid::PotentialGrid(const PixelRect& dimensions, Base::Real gridConstant, Base::Real level):
        BaseGrid<Scalar>(dimensions, gridConstant)
    {
        std::fill(values.begin(), values.end(), level);
    }

    template<Base::ScalarOrVector T>
    T negativeReLU(T x)
    {
        return x >= 0 ? 0 : - x;
    }

    constexpr PixelCoordinate offByOne = {1,1};

    PixelCoordinate PotentialGrid::getMinimumImposeIndices(const PotentialGrid& targetPotential, const PixelCoordinate at) const
    {
        PixelCoordinate minPos = at - (targetPotential.getPixelSize() - targetPotential.getPixelOrigin() + this->getPixelOrigin()) + offByOne;
        return {negativeReLU(minPos.x), negativeReLU(minPos.y)};
    }

    PixelCoordinate PotentialGrid::getMaximumImposeIndices(const PotentialGrid& targetPotential, const PixelCoordinate at) const
    {
        PixelCoordinate maxPos = at + targetPotential.getPixelDimensions().getMax() + this->getPixelOrigin() - offByOne;
        PixelCoordinate clippedPos = PixelCoordinate::min(maxPos, this->getPixelDimensions().getMax() - offByOne);
        PixelCoordinate deltaClipping = maxPos - clippedPos;
        PixelCoordinate existingPos = targetPotential.getPixelSize() - deltaClipping - offByOne;

        return existingPos;
    }

    void PotentialGrid::imposeAt(const PotentialGrid& targetPotential, const RealCoordinate at)
    {
        const PixelCoordinate pixelAt = at.toPixelCoordinate(gridConstant);
        imposeAt(targetPotential, pixelAt);
    }

    void PotentialGrid::imposeAt(const PotentialGrid& targetPotential, const PixelCoordinate at)
    {
        PixelCoordinate minIdxs = getMinimumImposeIndices(targetPotential, at);
        PixelCoordinate maxIdxs = getMaximumImposeIndices(targetPotential, at);
        PixelCoordinate startIdxs = getPixelOrigin() + at - targetPotential.getPixelOrigin() + minIdxs;

#ifdef ENABLE_AVX
        imposeImpl_avxAccelerated(potential, minIdxs, maxIdxs, startIdxs);
#else
        imposeImpl_noAcceleration(targetPotential, minIdxs, maxIdxs, startIdxs);
#endif
    }

    int to_index(int x, int y, int w)
    {
        return y * w + x;
    }

#ifdef ENABLE_AVX
    void PotentialGrid::imposeImpl_avxAccelerated(const PotentialGrid& targetPotential, const PixelCoordinate& minIdxs, const PixelCoordinate& maxIdxs, const PixelCoordinate& startIdxs)
    {
        const auto width = maxIdxs.x - minIdxs.x + 1;
        const auto potBegin  = targetPotential.values.data();
        const auto selfBegin = this->values.data();

        /* This uses _mm512_maskz_expandloadu_pd(mask, mem_adr) to get values from memory to the AVX registers.
         * Here ...
         *   mem_adr is the source address from which to copy the values
         *   mask    is a bit mask indicating which values to actually load
         *   returns the load result
         * https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#ig_expand=0,135,140,3772,2925&cats=Load&techs=AVX_512
         */
        __m512d  sum, a, b;
        __mmask8 mask = 0b11111111;

        /* Then, the loaded values are added with _mm512_add_pd(a, b), where a, b are of type __m512d */

        /* Finally, write back the sums with _mm512_mask_storeu_pd(void* base_addr, __mmask8 k, __m512d a)
         * Here, the parameters are analogous to the load operation
         */

        for (auto y = minIdxs.y; y <= maxIdxs.y; ++y)
        {
            const auto from = to_index(minIdxs.x, y, targetPotential.size.x);
            const auto to   = to_index(startIdxs.x, startIdxs.y + y - minIdxs.y, size.x);

            for (auto x = 0; x <= width; x+=8)
            {
                if (x + 8 >= width)
                {
                    const auto presentCount = width - x;
                    mask = (1 << presentCount) - 1;
                }
                a = _mm512_maskz_expandloadu_pd(mask, potBegin + from + x);
                b = _mm512_maskz_expandloadu_pd(mask, selfBegin + to + x);
                sum = _mm512_add_pd(a, b);
                _mm512_mask_storeu_pd(selfBegin + to + x, mask, sum);
            }
            mask = 0b11111111;
        }

    }
#else
    void PotentialGrid::imposeImpl_noAcceleration(const PotentialGrid& targetPotential, const PixelCoordinate& minIdxs, const PixelCoordinate& maxIdxs, const PixelCoordinate& startIdxs)
    {
        const auto width = maxIdxs.x - minIdxs.x + 1;
        const auto potBegin  = targetPotential.values.begin();
        const auto selfBegin = this->values.begin();

        for (auto y = minIdxs.y; y <= maxIdxs.y; ++y)
        {
            const auto from = to_index(minIdxs.x, y, targetPotential.getPixelSize().x);
            const auto till = from + width;
            const auto to   = to_index(startIdxs.x, startIdxs.y + y - minIdxs.y, getPixelSize().x);

            std::transform(potBegin + from, potBegin + till,
                           selfBegin + to,
                           selfBegin + to,
                           std::plus<> {}
                          );
        }
    }
#endif

    std::string PotentialGrid::to_string() const
    {
        constexpr char shades[] = "?Vv=- +*tT!";

        const int length = dimensions.w * (dimensions.h + 1);       // +1 for line breaks
        auto result = std::string(length, 'x');

        const Real min = *std::min_element(values.begin(), values.end());
        const Real max = *std::max_element(values.begin(), values.end());
        const Real rng = max - min;

        if (rng == 0)
        {
            return "(flat potential)";
        }

        const Real factor = (sizeof(shades) - 2) / rng;
        int idx_string = 0, idx_field = 0;
        for (int y = 0; y < dimensions.h; ++y)
        {
            for (int x = 0; x < dimensions.w; ++x)
            {
                const int level = (values[idx_field] - min) * factor;
                result[idx_string] = shades[level];
                ++idx_field;
                ++idx_string;
            }
            result[idx_string] = '\n';
            ++idx_string;
        }

        return result;
    }
}
