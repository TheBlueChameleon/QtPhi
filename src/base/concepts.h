#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <utility>

namespace Base
{
    template<typename T, typename E, typename O>
    concept EitherOr = std::is_convertible_v<T, E> || std::is_convertible_v<T, O>;

    // ...................................................................... //

    using Pixel = int;
    using Real = double;

    template<typename T>
    concept PixelOrReal = EitherOr<T, Pixel, Real>;

    template<PixelOrReal T>
    class Coordinate;

    using PixelCoordinate = Coordinate<Pixel>;
    using RealCoordinate = Coordinate<Real>;

    template<PixelOrReal T>
    class Rect;

    using PixelRect = Rect<Pixel>;
    using RealRect = Rect<Real>;

    // ...................................................................... //

    using Scalar = Real;
    using Vector = RealCoordinate;

    template<typename T>
    concept ScalarOrVector = Base::EitherOr<T, Scalar, Vector>;
}

#endif // CONCEPTS_H
