#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

namespace Base
{
    template<typename T, typename E, typename O>
    concept EitherOr = std::is_convertible_v<T, E> || std::is_convertible_v<T, O>;

    using Pixel = int;
    using Real = double;

    template<typename T>
    concept PixelOrReal = EitherOr<T, Pixel, Real>;

    template<PixelOrReal T>
    class Coordinate;

    using PixelCoordinates = Coordinate<Pixel>;
    using RealCoordinates = Coordinate<Real>;

    using Scalar = Real;
    using Vector = RealCoordinates;

    template<typename T>
    concept EitherScalarOrVector = Base::EitherOr<T, Scalar, Vector>;
}

#endif // CONCEPTS_H
