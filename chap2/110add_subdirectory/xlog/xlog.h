// xlog.h

#ifndef XLOG_H
#define XLOG_H

#ifndef _Win32
#define XCPP_API
#else // windows
#ifdef xlog_STATIC
#define XCPP_API
#else
#ifdef xlog_EXPORTS
#define XCPP_API __declspec(dllexport)
#else
#define XCPP_API __declspec(dllimport)
#endif
#endif
#endif

class XCPP_API XLog {
public:
    XLog();
};

#endif