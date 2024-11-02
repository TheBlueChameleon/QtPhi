#include "base/errors.h"
#include "base/interpolation/interpolation.h"

#include "colormap.h"

using namespace Base;

namespace Gui
{
    bool ColorMap::crossesZero(const Base::Real min, const Base::Real max)
    {
        const auto sign = [](const Real x)
        {
            return
                0 * (x == 0)
                +1 * (x > 0)
                -1 * (x < 0)
                ;
        };
        return std::abs(sign(min) + sign(max)) == 0;
    }

    QColor ColorMap::blueToRed(const Real at, const Real min, const Real max)
    {
        auto c = QColor();

        if (crossesZero(min, max))
        {
            if (at < 0)
            {
                c.setRed(Interpolation::linear<Real>(at, min, 0, 0, 128));
                c.setBlue(Interpolation::linear<Real>(at, min, 255, 0, 128));
            }
            else
            {
                c.setRed(Interpolation::linear<Real>(at, 0, 128, max, 255));
                c.setBlue(Interpolation::linear<Real>(at, 0, 128, max, 0));
            }
        }
        else
        {
            c.setRed(Interpolation::linear<Real>(at, min, 0, max, 255));
            c.setBlue(Interpolation::linear<Real>(at, min, 255, max, 0));
        }

        return c;
    }

    // ...................................................................... //

    ColorMap::ColorMap(const Real min, const Real max, const MappingFunctionType mappingFunction) :
        min(min), max(max), mappingFunction(mappingFunction)
    {
        assertValidSettings();
    }

    Real ColorMap::getMin() const
    {
        return min;
    }

    void ColorMap::setMin(const Real newMin)
    {
        min = newMin;
        assertValidSettings();
    }

    Real ColorMap::getMax() const
    {
        return max;
    }

    void ColorMap::setMax(const Real newMax)
    {
        max = newMax;
        assertValidSettings();
    }

    std::pair<Real, Real> ColorMap::getRange() const
    {
        return std::make_pair(min, max);
    }

    void ColorMap::setRange(const Base::Real min, const Base::Real max)
    {
        this->min = min;
        this->max = max;
        assertValidSettings();
    }

    bool ColorMap::contains(Real value) const
    {
        return (value >= min) && (value <= max);
    }

    bool ColorMap::crossesZero() const
    {
        return crossesZero(min, max);
    }

    ColorMap::MappingFunctionType ColorMap::getMappingFunction() const
    {
        return mappingFunction;
    }

    void ColorMap::setMappingFunction(const MappingFunctionType& newMappingFunction)
    {
        mappingFunction = newMappingFunction;
        assertValidSettings();
    }

    QColor ColorMap::get(const Real at) const
    {
        return mappingFunction(at, min, max);
    }

    void ColorMap::assertValidSettings() const
    {
        if (min > max)
        {
            throw DimensionError("ColorMap: min > max!");
        }
        if (!mappingFunction)
        {
            throw IllegalStateError("ColorMap: illegal function provided");
        }
    }

}
