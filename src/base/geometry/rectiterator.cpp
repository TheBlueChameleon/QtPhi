#include "rectiterator.h"
#include "rect.h"

namespace Base
{
    template<PixelOrReal T>
    RectIterator<T>::RectIterator(const Rect<T>& rect) :
        x(rect.x), y(rect.y), w(rect.w), h(rect.h),
        gridConstant(rect.gridConstant),
        currentCoordinate(rect.getMin())
    {}

    // prefix operator
    template<PixelOrReal T>
    RectIterator<T>& RectIterator<T>::operator++()
    {
        if constexpr(std::is_integral<T>::value)
        {
            ++currentCoordinate.x;
        }
        else
        {
            currentCoordinate.x += gridConstant;
        }

        if (currentCoordinate.x >= x + w)
        {
            currentCoordinate.x = x;
            if constexpr(std::is_integral<T>::value)
            {
                ++currentCoordinate.y;
            }
            else
            {
                currentCoordinate.y += gridConstant;
            }
        }

        if (currentCoordinate.y >= y + h)
        {
            *this = RectIterator();
        }

        return *this;
    }

    // postfix operator
    template<PixelOrReal T>
    RectIterator<T> RectIterator<T>::operator++(int)
    {
        const auto temp = *this;
        ++(*this);
        return temp;
    }

    template<PixelOrReal T>
    RectIterator<T>::reference RectIterator<T>::operator*() const
    {
        return currentCoordinate;
    }

    template<PixelOrReal T>
    RectIterator<T>::pointer RectIterator<T>::operator->() const
    {
        return &currentCoordinate;
    }

    // ====================================================================== //
    // instantiations

    template class RectIterator<Pixel>;
    template class RectIterator<Real>;
}
