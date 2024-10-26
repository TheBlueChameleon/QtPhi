#include "errors.h"

#define DEF_ERROR(__name__) __name__::__name__(const std::string& message) : Base::PhiError(message) {}

namespace Base
{
    PhiError::PhiError(const std::string& message) : std::runtime_error(message) {}
    DEF_ERROR(AccessRightsError);
    DEF_ERROR(KeyError);
    DEF_ERROR(MemoryManagementError);
    DEF_ERROR(DimensionError);
    DEF_ERROR(CoordinatesError);
}

namespace Physics
{
}

namespace UiBase
{
    DEF_ERROR(SdlError);
}
