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
    bool Coordinate<T>::operator==(const Coordinate<T>& rhs) const
    {
        return this->x == rhs.x && this->y == rhs.y;
    }

    template<PixelOrReal T>
    std::string Coordinate<T>::to_string() const
    {
        return "(" + std::to_string(this->x) + ", " + std::to_string(this->y) + ")";
    }

    // ====================================================================== //
    // helper functions

    template<PixelOrReal T>
    Coordinate<T> min(const Coordinate<T>& a, const Coordinate<T>& b)
    {
        return { std::min(a.x, b.x), std::min(a.y, b.y) };
    }

    template<PixelOrReal T>
    Coordinate<T> max(const Coordinate<T>& a, const Coordinate<T>& b)
    {
        return { std::max(a.x, b.x), std::max(a.y, b.y) };
    }

    template<PixelOrReal T>
    std::array<T, 4> getBoundariesSorted(const Coordinate<T>& boundary1, const Coordinate<T>& boundary2)
    {
        T x1 = boundary1.x;
        T x2 = boundary2.x;
        T y1 = boundary1.y;
        T y2 = boundary2.y;

        // *INDENT-OFF*
        if (x1 > x2) {std::swap(x1, x2);}
        if (y1 > y2) {std::swap(y1, y2);}
        // *INDENT-ON*

        return {x1, x2, y1, y2};
    }

    template<PixelOrReal T>
    bool isWithin(const Coordinate<T>& point, const Coordinate<T>& boundary1, const Coordinate<T>& boundary2)
    {
        const auto [x1, x2, y1, y2] = getBoundariesSorted(boundary1, boundary2);

        if (x1 <= point.x && point.x < x2)
        {
            if (y1 <= point.y && point.y < y2)
            {
                return true;
            }
        }
        return false;
    }
}

#endif // COORDINATES_TXX
