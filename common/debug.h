//
// Created by rot on 11/10/16.
//

#ifndef __UONEWCLIENT_DEBUG_H
#define __UONEWCLIENT_DEBUG_H

#ifndef DEBUG_MODE
#define DEBUG_MODE 0
#endif //DEBUG_MODE

#if DEBUG_MODE > 0
#include <string>
#include <sstream>
#define _DBG_MSG(x, y) { \
    std::stringstream s; \
    s << x << "::" << __FILE__ << "(" << __LINE__ << ")::" << __func__ << ": " << y; \
    _debug_print(s.str().c_str()); \
}
#define debug_init() _debug_init()
#define debug_halt() _debug_halt()
void _debug_init();
void _debug_halt();
void _debug_print(const char * buffer);
#else //DEBUG_MODE > 0
#define _DBG_MSG(x, y)
#define debug_init()
#define debug_halt()
#endif

#ifdef UNUSED_PARAMETER
#undef UNUSED_PARAMETER
#endif //UNUSED_PARAMETER
#define UNUSED_PARAMETER(x) (void)(x)

#ifdef UNREFERENCED_FUNCTION
#undef UNREFERENCED_FUNCTION
#endif //UNREFERENCED_FUNCTION
#define UNREFERENCED_FUNCTION(x) \
void __##x##_unused_function() { \
    void (*f)(void*) = (void (*)(void *))&x; \
    UNUSED_PARAMETER(f); \
} \
void __##x##_unused_function() __attribute__ ((unused))

#define DEBUG_ERROR(x)
#define DEBUG_WARNING(x)
#define DEBUG_NOTICE(x)
#define DEBUG_INFO(x)
#define DEBUG_MSG(x)

#if DEBUG_MODE > 0
#undef DEBUG_ERROR
#define DEBUG_ERROR(x) _DBG_MSG("[ERROR]", x)
#endif
#if DEBUG_MODE > 1
#undef DEBUG_WARNING
#define DEBUG_WARNING(x) _DBG_MSG("[WARNING]", x)
#endif
#if DEBUG_MODE > 2
#undef DEBUG_NOTICE
#define DEBUG_NOTICE(x) _DBG_MSG("[NOTICE]", x)
#endif
#if DEBUG_MODE > 3
#undef DEBUG_INFO
#define DEBUG_INFO(x) _DBG_MSG("[INFO]", x)
#endif
#if DEBUG_MODE > 4
#undef DEBUG_MSG
#define DEBUG_MSG(x) _DBG_MSG("[MSG]", x)
#endif

#define MAX(x, y) (((x)>(y))?(x):(y))

#endif //__UONEWCLIENT_DEBUG_H
