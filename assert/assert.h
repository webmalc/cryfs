#pragma once
#ifndef MESSMER_CPP_UTILS_ASSERT_ASSERT_H
#define MESSMER_CPP_UTILS_ASSERT_ASSERT_H

/**
 * This implements an ASSERT(expr, msg) macro.
 * In a debug build, it will crash and halt the program on an assert failure.
 * In a release build, it will throw an AssertFailed exception instead, which can then be caught.
 */

#include "AssertFailed.h"
#include <iostream>
#include <string>
#include <execinfo.h>

namespace cpputils {
    namespace _assert {
        inline std::string format(const char *expr, const char *message, const char *file, int line) {
            // get void*'s for all entries on the stack
            constexpr unsigned int MAX_SIZE = 100;
            void *array[MAX_SIZE];
            size_t size = backtrace(array, MAX_SIZE);
            char **backtrace_str = backtrace_symbols(array, size);
            std::string result = std::string()+"Assertion ["+expr+"] failed in "+file+":"+std::to_string(line)+": "+message+"\n\n";
            for (unsigned int i = 0; i < size; ++i) {
                result += std::string(backtrace_str[i]) + "\n";
            }
            free(backtrace_str);
            return result;
        }

        inline void assert_fail_release [[noreturn]] (const char *expr, const char *message, const char *file, int line) {
            throw AssertFailed(format(expr, message, file, line));
        }

        inline void assert_fail_debug [[noreturn]] (const char *expr, const char *message, const char *file, int line) {
            std::cerr << format(expr, message, file, line) << std::endl;
            abort();
        }
    }
}

#ifdef NDEBUG
//TODO Check whether disabling assertions in prod affects speed.
# define ASSERT(expr, msg) (void)((expr) || (cpputils::_assert::assert_fail_release(#expr, msg, __FILE__, __LINE__),0))
#else
# define ASSERT(expr, msg) (void)((expr) || (cpputils::_assert::assert_fail_debug(#expr, msg, __FILE__, __LINE__),0))
#endif

#endif