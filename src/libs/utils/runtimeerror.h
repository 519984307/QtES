#ifndef RUNTIMEERROR_H
#define RUNTIMEERROR_H

#include <stdexcept>

#include "utils_global.h"

namespace Utils {
class UTILSSHARED_EXPORT RuntimeError : public std::runtime_error
{
public:
    explicit RuntimeError(const std::string &err) : std::runtime_error(err) {}
};
} // namespace Utils
#endif
