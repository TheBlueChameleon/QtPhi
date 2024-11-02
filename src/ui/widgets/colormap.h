#ifndef COLORMAP_H
#define COLORMAP_H

#include <functional>

#include <QColor>

#include "base/concepts.h"

namespace Gui
{
    class ColorMap
    {
        public:
            using MappingFunctionType = std::function<QColor(const Base::Real at, const Base::Real min, const Base::Real max)>;

            static bool   crossesZero(const Base::Real min, const Base::Real max);
            static QColor blueToRed(const Base::Real at, const Base::Real min, const Base::Real max);

        private:
            Base::Real min;
            Base::Real max;
            MappingFunctionType mappingFunction;

        public:
            ColorMap(const Base::Real min, const Base::Real max, const MappingFunctionType mappingFunction = blueToRed);

            Base::Real getMin() const;
            void setMin(const Base::Real newMin);

            Base::Real getMax() const;
            void setMax(const Base::Real newMax);

            std::pair<Base::Real, Base::Real> getRange() const;
            void setRange(const Base::Real min, const Base::Real max);

            bool contains(Base::Real value) const;
            bool crossesZero() const;

            MappingFunctionType getMappingFunction() const;
            void setMappingFunction(const MappingFunctionType& newMappingFunction);

            QColor get(const Base::Real at) const;

        private:
            void assertValidSettings() const;
    };
}

#endif // COLORMAP_H
