/** @author: Oliver Ocean */

#ifndef CUSTOM_EXCEPTION_
#define CUSTOM_EXCEPTION_

#include <stdexcept>
#include <string>

class CustomException : public std::logic_error
{
public:
    explicit CustomException(const std::string& e = "") : std::logic_error("<< Custom Exception: " + e) {}
};

#endif