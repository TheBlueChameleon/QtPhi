#ifndef RECTITERATOR_H
#define RECTITERATOR_H

#include "coordinate.h"

namespace Base
{
    template<PixelOrReal T>
    class RectIterator
    {
        public:
            using iterator_category = std::input_iterator_tag;
            using iterator_concept  = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Coordinate<T>;
            using pointer           = const Coordinate<T>* ;
            using reference         = const Coordinate<T>& ;

        private:
            T x;
            T y;
            T w;
            T h;
            Real       gridConstant;
            value_type currentCoordinate;

        public:
            RectIterator() = default;
            RectIterator(const RectIterator& other) = default;
            RectIterator(RectIterator&& other) = default;
            RectIterator(const Rect<T>& rect);

            RectIterator<T>& operator++();        // prefix operator
            RectIterator<T>  operator++(int);     // postfix operator

            reference operator*() const;
            pointer   operator->() const;

            bool operator==(const RectIterator<T>& it) const = default;
            bool operator!=(const RectIterator<T>& it) const = default;

            RectIterator& operator=(const RectIterator<T>& other) = default;
            RectIterator& operator=(RectIterator<T>&& other) = default;
    };

    static_assert(std::weakly_incrementable<RectIterator<Real>>);
    static_assert(std::input_or_output_iterator<RectIterator<Real>>);
    static_assert(std::indirectly_readable<RectIterator<Real>>);
    static_assert(std::input_iterator<RectIterator<Real>>);
    static_assert(std::incrementable<RectIterator<Real>>);
}

#endif // RECTITERATOR_H
