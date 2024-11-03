#include "base/functions/functions.h"
#include "base/interpolation/interpolation.h"

#include "lerpcolormap.h"

using namespace Base;

namespace Gui
{
    LerpColorMap::LerpColorMap(const ColorMapPointsType& points):
        points(points)
    {}

    LerpColorMap::LerpColorMap(const Real min, const Real max, const ColorScheme colorscheme)
    {
        switch (colorscheme)
        {
            case ColorScheme::blueToRed:
                addStop(min, QColor("blue"));
                addStop(max, QColor("red"));
                break;
            case ColorScheme::cyanToYellow:
                addStop(min, QColor("cyan"));
                addStop(max, QColor("yellow"));
                break;
        }
    }

    const LerpColorMap::ColorMapPointsType& LerpColorMap::getPoints() const
    {
        return points;
    }

    void LerpColorMap::addStop(Base::Real at, QColor color)
    {
        // todo: add no overwrite check?
        points[at] = color;
    }

    Base::Real LerpColorMap::getMin() const
    {
        return points.begin()->first;
    }

    Base::Real LerpColorMap::getMax() const
    {
        return (--points.end())->first;
    }

    RangeType<Real> LerpColorMap::getRange() const
    {
        return RangeType<Real>(
                   points.begin()->first,
                   (--points.end())->first
               );
    }

    bool LerpColorMap::contains(Base::Real value) const
    {
        const auto [min, max] = getRange();
        return (value >= min) && (value <= max);
    }

    QColor LerpColorMap::get(const Real at) const
    {
        const auto [pMin, pMax] = getEnclosingStops(at);
        const auto cMin = points.at(pMin);
        const auto cMax = points.at(pMax);
        const auto lambda = Interpolation::linear(
                                at,
                                pMin, 0.0,
                                pMax, 1.0
                            );
        auto c = QColor();
        c.setRed((1 - lambda) * cMin.red() + lambda * cMax.red());
        c.setGreen((1 - lambda) * cMin.green() + lambda * cMax.green());
        c.setBlue((1 - lambda) * cMin.blue() + lambda * cMax.blue());

        return c;
    }

    std::pair<Real, Real> LerpColorMap::getEnclosingStops(const Real at) const
    {
        Real before = getMin();
        Real after = before;

        for (const auto& [key, color]: points)
        {
            if (at < after)
            {
                break;
            }

            before = after;
            after = key;
        }

        return std::make_pair(before, after);
    }
}
