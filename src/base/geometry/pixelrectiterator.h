#ifndef PIXELRECTITERATOR_H
#define PIXELRECTITERATOR_H

#include "coordinate.h"

namespace Base
{
    class PixelRectIterator
    {
        public:
            using iterator_category = std::input_iterator_tag;
            using iterator_concept  = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = PixelCoordinate;
            using pointer           = const PixelCoordinate*;
            using reference         = const PixelCoordinate&;

        private:
            Pixel x;
            Pixel y;
            Pixel w;
            Pixel h;
            value_type currentCoordinate;

        public:
            PixelRectIterator() = default;
            PixelRectIterator(const PixelRectIterator& other) = default;
            PixelRectIterator(PixelRectIterator&& other) = default;
            PixelRectIterator(const PixelRect& rect);

            PixelRectIterator& operator++();        // prefix operator
            PixelRectIterator  operator++(int);     // postfix operator

            reference operator*() const;
            pointer   operator->() const;

            bool operator==(const PixelRectIterator& it) const = default;
            bool operator!=(const PixelRectIterator& it) const = default;

            PixelRectIterator& operator=(const PixelRectIterator& other) = default;
            PixelRectIterator& operator=(PixelRectIterator&& other) = default;
    };
}

#endif // PIXELRECTITERATOR_H
