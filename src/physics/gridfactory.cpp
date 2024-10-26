#include <cmath>

#include "gridfactory.h"

using namespace Base;
namespace Physics
{
    const PixelCoordinate GridFactory::USE_DEFAULT = PixelCoordinate(-1, -1);

    GridFactory::GridFactory(PixelCoordinate size, Real gridConstant) :
        size(size), gridConstant(gridConstant)
    {}

    PotentialGrid GridFactory::makeWorld() const
    {
        return PotentialGrid(size, gridConstant);
    }

    PotentialGrid GridFactory::makeOverlayAtConstantLevel(Real level, PixelCoordinate size) const
    {
        PotentialGrid result;
        if (size == USE_DEFAULT)
        {
            result = PotentialGrid(this->size, gridConstant, level);
        }
        else
        {
            result = PotentialGrid(size, gridConstant, level);
        }
        result.setOrigin(result.getPixelSize() / 2);

        return result;
    }

    Pixel getSizeLimitedToDoubleWorldSize(const Pixel cutoffSize, const Pixel worldSize)
    {
        const Pixel doubleWorldSize = 2 * worldSize + 1;
        return cutoffSize > doubleWorldSize ? doubleWorldSize : cutoffSize;
    }

    PotentialGrid GridFactory::makeOverlayFromCharge(Real charge, Real cutoff) const
    {
        Pixel cutoffSize = std::abs(charge / (cutoff * gridConstant));
        cutoffSize += !(cutoffSize & 1);   // guarantee this is an odd number

        PixelCoordinate createdSize = {getSizeLimitedToDoubleWorldSize(cutoffSize, size.x),
                                        getSizeLimitedToDoubleWorldSize(cutoffSize, size.y)
                                       };
        PixelCoordinate quadrantSize = createdSize / 2;
        PotentialGrid result = PotentialGrid(createdSize, gridConstant);
        result.setOrigin(quadrantSize);

        // TODO: this can be optimized further by iterating only over one octant, reconstructing the rest from symmetry as well
        for (int y = 0; y < quadrantSize.y; ++y)
        {
            // skip coordinate (0, 0), otherwise cover full quadrant
            for (int x = (y == 0); x < quadrantSize.x; ++x)
            {
                const Real value = charge / std::sqrt(x*x + y*y);
                result[PixelCoordinate{+x, +y}] = value;
                result[PixelCoordinate{-x, +y}] = value;
                result[PixelCoordinate{+x, -y}] = value;
                result[PixelCoordinate{-x, -y}] = value;
            }
        }

        result[PixelCoordinate{0, 0}] = 2 * charge / gridConstant;

        return result;
    }
}
