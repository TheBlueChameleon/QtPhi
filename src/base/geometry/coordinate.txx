#ifndef COORDINATES_TXX
#define COORDINATES_TXX

#include "coordinate.h"

namespace Base
{
    // ====================================================================== //
    // class methods

    // todo: optimize in terms of intrinsics
    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::operator-() const
    {
        return {-this->x, -this->y};
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::operator+(const Coordinate<T>& rhs) const
    {
        return {this->x + rhs.x, this->y + rhs.y};
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::operator-(const Coordinate<T>& rhs) const
    {
        return {this->x - rhs.x, this->y - rhs.y};
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::operator*(const Real rhs) const
    {
        return {static_cast<T>(this->x * rhs), static_cast<T>(this->y * rhs)};
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::operator/(const Real rhs) const
    {
        return {static_cast<T>(this->x / rhs), static_cast<T>(this->y / rhs)};
    }

    template<PixelOrReal T>
    std::string Coordinate<T>::to_string() const
    {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::min(const Coordinate<T>& lhs, const Coordinate<T>& rhs)
    {
        return Coordinate<T>(
                   std::min(lhs.x, rhs.x),
                   std::min(lhs.y, rhs.y)
               );
    }

    template<PixelOrReal T>
    Coordinate<T> Coordinate<T>::max(const Coordinate<T>& lhs, const Coordinate<T>& rhs)
    {
        return Coordinate<T>(
                   std::max(lhs.x, rhs.x),
                   std::max(lhs.y, rhs.y)
               );
    }
}

#endif // COORDINATES_TXX
