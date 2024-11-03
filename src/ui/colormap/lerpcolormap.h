#ifndef LERPCOLORMAP_H
#define LERPCOLORMAP_H

#include <map>

#include "colormap.h"

namespace Gui
{
    class LerpColorMap : public virtual ColorMap
    {
        public:
            enum class ColorScheme
            {
                blueToRed,
                cyanToYellow,
                blackToWhite
            };

            using ColorMapPointsType = std::map<Base::Real, QColor>;

        private:
            ColorMapPointsType points;

        public:
            LerpColorMap(const ColorMapPointsType& points);
            LerpColorMap(const Base::Real min, const Base::Real max, const ColorScheme colorscheme);

            const ColorMapPointsType& getPoints() const;
            void addStop(Base::Real at, QColor color);

            // ColorMap interface
            Base::Real getMin() const;
            Base::Real getMax() const;
            Base::RangeType<Base::Real> getRange() const;

            bool contains(Base::Real value) const;
            QColor get(const Base::Real at) const;

        private:
            std::pair<Base::Real, Base::Real> getEnclosingStops(const Base::Real at) const;
    };
}

#endif // LERPCOLORMAP_H
