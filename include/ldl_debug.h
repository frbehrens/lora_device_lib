/* Copyright (c) 2019-2020 Cameron Harper
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * */

#ifndef LDL_DEBUG_H
#define LDL_DEBUG_H

/** @file */

/**
 * @addtogroup ldl_build_options
 *
 * @{
 * */

#include "ldl_platform.h"

#ifndef LDL_ERROR
    /** A printf-like function that captures run-time error level messages
     *
     * Example:
     *
     * @code{.c}
     * #define LDL_ERROR(...) do{printf(__VA_ARGS__);printf("\n");}while(0);
     * @endcode
     *
     * If not defined, all LDL_ERROR() messages will be left out of the build.
     *
     * */
    #define LDL_ERROR(...)
#endif

#ifndef LDL_INFO
    /** A printf-like function that captures run-time info level messages
     *
     * Example:
     *
     * @code{.c}
     * #define LDL_INFO(...) do{printf(__VA_ARGS__);printf("\n");}while(0);
     * @endcode
     *
     * If not defined, all LDL_INFO() messages will be left out of the build.
     *
     * */
    #define LDL_INFO(...)
#endif

#ifndef LDL_TRACE_BEGIN
    #define LDL_TRACE_BEGIN()
#endif

#ifndef LDL_TRACE_PART
    #define LDL_TRACE_DISABLED
    #define LDL_TRACE_PART(...)
#endif

#ifndef LDL_TRACE_HEX
    #define LDL_TRACE_HEX(PTR, LEN)
#endif

#ifndef LDL_TRACE_BIT_STRING
    #define LDL_TRACE_BIT_STRING(PTR, LEN)
#endif

#ifndef LDL_TRACE_FINAL
    #define LDL_TRACE_FINAL()
#endif

#define LDL_TRACE(...) do{\
    LDL_TRACE_BEGIN()\
    LDL_TRACE_PART(__VA_ARGS__)\
    LDL_TRACE_FINAL()\
}while(0);


#ifndef LDL_DEBUG
    /** A printf-like function that captures run-time debug level messages with
     * varaidic arguments
     *
     * Example:
     *
     * @code{.c}
     * #define LDL_DEBUG(...) do{printf(__VA_ARGS__);printf("\n");}while(0);
     * @endcode
     *
     * If not defined, all LDL_DEBUG() messages will be left out of the build.
     *
     * */
    #define LDL_DEBUG(...)
#endif

#ifndef LDL_ASSERT
    /** An assert-like function that performs run-time assertions on 'X'.
     *
     * Example:
     *
     * @code{.c}
     * #define LDL_ASSERT(X) assert(X);
     * @endcode
     *
     * If not defined, all LDL_ASSERT() checks will be left out of the build.
     *
     * LDL_ASSERT() should be defined for development and production.
     *
     * */
    #define LDL_ASSERT(X)
#endif

#ifndef LDL_ABORT
    #define LDL_ABORT() LDL_ASSERT(true)
#endif

#ifndef LDL_PEDANTIC
    /** An assert-like function that performs run-time assertions on 'X'.
     *
     * Example:
     *
     * @code{.c}
     * #define LDL_PEDANTIC(X) assert(X);
     * @endcode
     *
     * If not defined, all LDL_PEDANTIC() checks will be left out of the build.
     *
     * LDL_PEDANTIC() should be defined for development.
     *
     * */
    #define LDL_PEDANTIC(X)
#endif

/** @} */
#endif
