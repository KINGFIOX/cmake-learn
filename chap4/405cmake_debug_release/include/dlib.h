#ifndef _WIN32  // unix
    #define XCPP_API
#else  // windows
    #ifdef xlog_EXPORTS
        #define XCPP_API __declspec(dllexport)
    #else
        #define XCPP_API __declspec(dllimport)
    #endif
#endif
XCPP_API void DLib();
