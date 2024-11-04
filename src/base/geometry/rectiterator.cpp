#include "rectiterator.h"
#include "rect.h"

namespace Base
{
    RectIterator::RectIterator(const PixelRect& rect) :
        x(rect.x), y(rect.y), w(rect.w), h(rect.h),
        gridConstant(rect.gridConstant),
        currentCoordinate(rect.getMin())
    {}

    // prefix operator
    RectIterator& RectIterator::operator++()
    {
        ++currentCoordinate.x;
        if (currentCoordinate.x >= x + w)
        {
            currentCoordinate.x = x;
            ++currentCoordinate.y;
        }

        if (currentCoordinate.y >= y + h)
        {
            *this = RectIterator();
        }

        return *this;
    }

    // postfix operator
    RectIterator RectIterator::operator++(int)
    {
        const auto temp = *this;
        ++(*this);
        return temp;
    }

    RectIterator::reference RectIterator::operator*() const
    {
        return currentCoordinate;
    }

    RectIterator::pointer RectIterator::operator->() const
    {
        return &currentCoordinate;
    }
}
