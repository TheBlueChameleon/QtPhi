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

        Coordinate<T>& operator+=(const Coordinate<T>& rhs);
        Coordinate<T>& operator-=(const Coordinate<T>& rhs);
        Coordinate<T>& operator*=(const Real rhs);
        Coordinate<T>& operator/=(const Real rhs);

        bool operator==(const Coordinate<T>& rhs) const = default;

        PixelCoordinate toPixelCoordinate(const Real gridConstant) const;
        RealCoordinate  toRealCoordinate(const Real gridConstant) const;

        std::string to_string() const;

        static Coordinate<T> min(const Coordinate<T>& lhs, const Coordinate<T>& rhs);
        static Coordinate<T> max(const Coordinate<T>& lhs, const Coordinate<T>& rhs);
    };

    template<PixelOrReal T>
    std::ostream& operator<< (std::ostream& stream, const Coordinate<T>& coordinate);
}

#endif // COORDINATES_H
