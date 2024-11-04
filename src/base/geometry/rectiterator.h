#ifndef RECTITERATOR_H
#define RECTITERATOR_H

#include "coordinate.h"

namespace Base
{
    class RectIterator
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
            Real gridConstant;
            value_type currentCoordinate;

        public:
            RectIterator() = default;
            RectIterator(const RectIterator& other) = default;
            RectIterator(RectIterator&& other) = default;
            RectIterator(const PixelRect& rect);

            RectIterator& operator++();        // prefix operator
            RectIterator  operator++(int);     // postfix operator

            reference operator*() const;
            pointer   operator->() const;

            bool operator==(const RectIterator& it) const = default;
            bool operator!=(const RectIterator& it) const = default;

            RectIterator& operator=(const RectIterator& other) = default;
            RectIterator& operator=(RectIterator&& other) = default;
    };

    static_assert(std::weakly_incrementable<RectIterator>);
    static_assert(std::input_or_output_iterator<RectIterator>);
    static_assert(std::indirectly_readable<RectIterator>);
    static_assert(std::input_iterator<RectIterator>);
    static_assert(std::incrementable<RectIterator>);
}

#endif // RECTITERATOR_H
