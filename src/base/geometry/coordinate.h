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

        PixelCoordinate toPixelCoordinate(Real gridConstant) const;
        RealCoordinate  toRealCoordinate(Real gridConstant) const;

        std::string to_string() const;

        static Coordinate<T> min(const Coordinate<T>& lhs, const Coordinate<T>& rhs);
        static Coordinate<T> max(const Coordinate<T>& lhs, const Coordinate<T>& rhs);
    };
}

#endif // COORDINATES_H
