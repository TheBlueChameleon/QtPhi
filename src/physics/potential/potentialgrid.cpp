#include <algorithm>

#include <immintrin.h>

#include "potentialgrid.h"

using namespace Base;
namespace Physics
{
    PotentialGrid::PotentialGrid() : BaseGrid<Scalar>({0,0}, 0) {}

    PotentialGrid::PotentialGrid(PixelCoordinates size, Real gridConstant, Real level) : BaseGrid<Scalar>(size, gridConstant)
    {
        std::fill(values.begin(), values.end(), level);
    }

    template<Base::EitherScalarOrVector T>
    T negativeReLU(T x)
    {
        return x >= 0 ? 0 : - x;
    }

    constexpr PixelCoordinates offByOne = {1,1};

    PixelCoordinates PotentialGrid::getMinimumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const
    {
        PixelCoordinates minPos = at - (potential.size - potential.origin + this->origin) + offByOne;
        return {negativeReLU(minPos.x), negativeReLU(minPos.y)};
    }

    PixelCoordinates PotentialGrid::getMaximumImposeIndices(const PotentialGrid& potential, const PixelCoordinates at) const
    {
        PixelCoordinates maxPos = at + potential.getMaxPixelCoordinates() + this->origin - offByOne;
        PixelCoordinates clippedPos = min(maxPos, this->getMaxPixelCoordinates() - offByOne);
        PixelCoordinates deltaClipping = maxPos - clippedPos;
        PixelCoordinates existingPos = potential.size - deltaClipping - offByOne;

        return existingPos;
    }

    void PotentialGrid::imposeAt(const PotentialGrid& potential, const RealCoordinates at)
    {
        const PixelCoordinates pc = toPixelCoordinates(at, gridConstant);
        imposeAt(potential, pc);
    }

    void PotentialGrid::imposeAt(const PotentialGrid& potential, const PixelCoordinates at)
    {
        PixelCoordinates minIdxs = getMinimumImposeIndices(potential, at);
        PixelCoordinates maxIdxs = getMaximumImposeIndices(potential, at);
        PixelCoordinates startIdxs = origin + at - potential.origin + minIdxs;

#ifdef NO_AVX_ACCELERATION
        imposeImpl_noAcceleration(potential, minIdxs, maxIdxs, startIdxs);
#else
        imposeImpl_avxAccelerated(potential, minIdxs, maxIdxs, startIdxs);
#endif
    }

    int to_index(int x, int y, int w)
    {
        return y * w + x;
    }

#ifdef NO_AVX_ACCELERATION
    void PotentialGrid::imposeImpl_noAcceleration(const PotentialGrid& potential, const PixelCoordinates& minIdxs, const PixelCoordinates& maxIdxs, const PixelCoordinates& startIdxs)
    {
        const auto width = maxIdxs.x - minIdxs.x + 1;
        const auto potBegin  = potential.values.begin();
        const auto selfBegin = this->values.begin();

        for (auto y = minIdxs.y; y <= maxIdxs.y; ++y)
        {
            const auto from = to_index(minIdxs.x, y, potential.size.x);
            const auto till = from + width;
            const auto to   = to_index(startIdxs.x, startIdxs.y + y - minIdxs.y, size.x);

            std::transform(potBegin + from, potBegin + till,
                           selfBegin + to,
                           selfBegin + to,
                           std::plus<> {}
                          );
        }
    }
#else
    void PotentialGrid::imposeImpl_avxAccelerated(const PotentialGrid& potential, const PixelCoordinates& minIdxs, const PixelCoordinates& maxIdxs, const PixelCoordinates& startIdxs)
    {
        const auto width = maxIdxs.x - minIdxs.x + 1;
        const auto potBegin  = potential.values.data();
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
            const auto from = to_index(minIdxs.x, y, potential.size.x);
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
#endif

    std::string PotentialGrid::to_string() const
    {
        constexpr char shades[] = "?Vv=- +*tT!";

        const int length = size.x * size.y + size.y;
        auto result = std::string(length, 'x');

        const Real min = *std::min_element(values.begin(), values.end());
        const Real max = *std::max_element(values.begin(), values.end());
        const Real width = max - min;

        if (width == 0)
        {
            return "(flat potential)";
        }

        const Real factor = (sizeof(shades) - 2) / width;
        int idx_string = 0, idx_field = 0;
        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
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

