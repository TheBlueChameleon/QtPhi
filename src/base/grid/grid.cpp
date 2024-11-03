#include "base/errors.h"

#include "grid.h"

namespace Base
{
    void assertNoNullptr(const Grid* const castResult)
    {
        if (castResult == nullptr)
        {
            throw MemoryManagementError("Invalid cast of Grid to ImplType");
        }
    }

    template<ScalarOrVector T>
    GridImpl<T>& Grid::forContent()
    {
        auto* const result = dynamic_cast<GridImpl<T>*>(this);
        assertNoNullptr(result);
        return *result;
    }

    template<ScalarOrVector T>
    const GridImpl<T>& Grid::forContent() const
    {
        auto* const result = dynamic_cast<const GridImpl<T>*>(this);
        assertNoNullptr(result);
        return *result;
    }

    template<>       GridImpl<Scalar>& Grid::forContent();
    template<> const GridImpl<Scalar>& Grid::forContent() const;

    template<>       GridImpl<Vector>& Grid::forContent();
    template<> const GridImpl<Vector>& Grid::forContent() const;
}
