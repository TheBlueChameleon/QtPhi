#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <utility>

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

    using PixelCoordinate = Coordinate<Pixel>;
    using RealCoordinate = Coordinate<Real>;

    using Scalar = Real;
    using Vector = RealCoordinate;

    template<typename T>
    concept ScalarOrVector = Base::EitherOr<T, Scalar, Vector>;

    using PixelCoordinatePair = std::pair<PixelCoordinate, PixelCoordinate>;
    using RealCoordinatePair = std::pair<RealCoordinate, RealCoordinate>;

    template<typename T>
    concept CoordinatePair = Base::EitherOr<T, PixelCoordinatePair, RealCoordinatePair>;

    template<PixelOrReal T>
    class Rect;

    using PixelRect = Rect<Pixel>;
    using RealRect = Rect<Real>;
}

#endif // CONCEPTS_H
