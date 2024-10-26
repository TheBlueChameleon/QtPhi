#include <cmath>

#include "gridfactory.h"

using namespace Base;
namespace Physics
{
    const PixelCoordinates GridFactory::USE_DEFAULT = PixelCoordinates(-1, -1);

    GridFactory::GridFactory(PixelCoordinates size, Real gridConstant) :
        size(size), gridConstant(gridConstant)
    {}

    PotentialGrid GridFactory::makeWorld() const
    {
        return PotentialGrid(size, gridConstant);
    }

    PotentialGrid GridFactory::makeOverlayAtConstantLevel(Real level, PixelCoordinates size) const
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

        PixelCoordinates createdSize = {getSizeLimitedToDoubleWorldSize(cutoffSize, size.x),
                                        getSizeLimitedToDoubleWorldSize(cutoffSize, size.y)
                                       };
        PixelCoordinates quadrantSize = createdSize / 2;
        PotentialGrid result = PotentialGrid(createdSize, gridConstant);
        result.setOrigin(quadrantSize);

        // TODO: this can be optimized further by iterating only over one octant, reconstructing the rest from symmetry as well
        for (int y = 0; y < quadrantSize.y; ++y)
        {
            // skip coordinate (0, 0), otherwise cover full quadrant
            for (int x = (y == 0); x < quadrantSize.x; ++x)
            {
                const Real value = charge / std::sqrt(x*x + y*y);
                result[PixelCoordinates{+x, +y}] = value;
                result[PixelCoordinates{-x, +y}] = value;
                result[PixelCoordinates{+x, -y}] = value;
                result[PixelCoordinates{-x, -y}] = value;
            }
        }

        result[PixelCoordinates{0, 0}] = 2 * charge / gridConstant;

        return result;
    }
}
