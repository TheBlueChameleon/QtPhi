#ifndef COORDINATES_H
#define COORDINATES_H

#include <array>
#include <string>

#include "base/concepts.h"

namespace Base
{
    template<PixelOrReal T>
    struct Coordinate
    {
        using baseType = T;

        T x;
        T y;

        Coordinate<T> operator-() const;
        Coordinate<T> operator+(const Coordinate<T>& rhs) const;
        Coordinate<T> operator-(const Coordinate<T>& rhs) const;
        Coordinate<T> operator*(const Real rhs) const;
        Coordinate<T> operator/(const Real rhs) const;
        bool operator==(const Coordinate<T>& rhs) const;

        std::string to_string() const;
    };

    template<PixelOrReal T>
    Coordinate<T> min(const Coordinate<T>& a, const Coordinate<T>& b);

    template<PixelOrReal T>
    Coordinate<T> max(const Coordinate<T>& a, const Coordinate<T>& b);

    template<PixelOrReal T>
    std::array<T, 4> getBoundariesSorted(const Coordinate<T>& boundary1, const Coordinate<T>& boundary2);

    template<PixelOrReal T>
    bool isWithin(const Coordinate<T>& point, const Coordinate<T>& boundary1, const Coordinate<T>& boundary2);

    PixelCoordinate toPixelCoordinates(const RealCoordinate& c, Real gridConstant);
    RealCoordinate  toRealCoordinates(const PixelCoordinate& c, Real gridConstant);
}

#endif // COORDINATES_H
