#include "pixelrectiterator.h"
#include "rect.h"

namespace Base
{
    PixelRectIterator::PixelRectIterator(const PixelRect& rect) :
        x(rect.x), y(rect.y), w(rect.w), h(rect.h),
        currentCoordinate(rect.getMin())
    {}

    // prefix operator
    PixelRectIterator& PixelRectIterator::operator++()
    {
        ++currentCoordinate.x;
        if (currentCoordinate.x >= x + w)
        {
            currentCoordinate.x = x;
            ++currentCoordinate.y;
        }

        if (currentCoordinate.y >= y + h)
        {
            *this = PixelRectIterator();
        }

        return *this;
    }

    // postfix operator
    PixelRectIterator PixelRectIterator::operator++(int)
    {
        const auto temp = *this;
        ++(*this);
        return temp;
    }

    PixelRectIterator::reference PixelRectIterator::operator*() const
    {
        return currentCoordinate;
    }

    PixelRectIterator::pointer PixelRectIterator::operator->() const
    {
        return &currentCoordinate;
    }
}
