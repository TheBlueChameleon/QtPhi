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
            virtual Base::Real getMin() const = 0;
            virtual Base::Real getMax() const = 0;
            virtual std::pair<Base::Real, Base::Real> getRange() const = 0;

            virtual bool contains(Base::Real value) const = 0;
            virtual QColor get(const Base::Real at) const = 0;
    };
}

#endif // COLORMAP_H
