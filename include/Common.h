#ifndef FORGE_COMMON_H
#define FORGE_COMMON_H
// Shared helpers. You do not need to change this file.
#include <stdexcept>
#include <string>

// Marks code you have not written yet. The test runner reports it as TODO.
struct NotImplemented : std::logic_error {
    NotImplemented() : std::logic_error("not implemented yet") {}
};
#define NOT_IMPLEMENTED() throw NotImplemented()

#endif
