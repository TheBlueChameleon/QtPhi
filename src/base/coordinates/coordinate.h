#ifndef COORDINATES_H
#define COORDINATES_H

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
        bool operator==(const Coordinate<T>& rhs) const = default;

        std::string to_string() const;
    };

    PixelCoordinate toPixelCoordinate(const RealCoordinate& c, Real gridConstant);
    RealCoordinate  toRealCoordinate(const PixelCoordinate& c, Real gridConstant);
}

#endif // COORDINATES_H
