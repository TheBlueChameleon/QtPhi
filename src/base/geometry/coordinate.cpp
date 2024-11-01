#include "coordinate.h"

namespace Base
{
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
    Coordinate<T>& Coordinate<T>::operator+=(const Coordinate<T>& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    template<PixelOrReal T>
    Coordinate<T>& Coordinate<T>::operator-=(const Coordinate<T>& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    template<PixelOrReal T>
    Coordinate<T>& Coordinate<T>::operator*=(const Real rhs)
    {
        this->x *= rhs;
        this->y *= rhs;
        return *this;
    }

    template<PixelOrReal T>
    Coordinate<T>& Coordinate<T>::operator/=(const Real rhs)
    {
        this->x /= rhs;
        this->y /= rhs;
        return *this;
    }

    // ...................................................................... //
    // template specializations

    template<>
    PixelCoordinate Coordinate<Pixel>::toPixelCoordinate([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    template<>
    PixelCoordinate Coordinate<Real>::toPixelCoordinate(const Real gridConstant) const
    {
        return PixelCoordinate {Pixel(this->x / gridConstant), Pixel(this->y / gridConstant)};
    }

    template<>
    RealCoordinate Coordinate<Pixel>::toRealCoordinate(const Real gridConstant) const
    {
        return RealCoordinate {this->x * gridConstant, this->y * gridConstant};
    }

    template<>
    RealCoordinate Coordinate<Real>::toRealCoordinate([[maybe_unused]] const Real gridConstant) const
    {
        return *this;
    }

    // ...................................................................... //

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

    // ====================================================================== //
    // instantiations

    template struct Coordinate<Pixel>;
    template struct Coordinate<Real>;
}
