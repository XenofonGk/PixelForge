#ifndef FORGE_CHECK_H
#define FORGE_CHECK_H
#include <functional>
#include <iostream>
#include <string>

extern int g_checks;
extern int g_failures;

#define CHECK(COND)                                                        \
    do {                                                                   \
        ++g_checks;                                                        \
        if (!(COND)) {                                                     \
            ++g_failures;                                                  \
            std::cout << "    failed line " << __LINE__ << ": " #COND "\n"; \
        }                                                                  \
    } while (0)

#define CHECK_THROWS(EXPR, TYPE)                                                \
    do {                                                                        \
        ++g_checks;                                                             \
        bool ok_ = false;                                                       \
        try { EXPR; } catch (const TYPE&) { ok_ = true; }                       \
        if (!ok_) {                                                             \
            ++g_failures;                                                       \
            std::cout << "    failed line " << __LINE__ << ": expected " #TYPE " from " #EXPR "\n"; \
        }                                                                       \
    } while (0)

#endif
