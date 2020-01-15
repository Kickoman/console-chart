#ifndef OSDETECT_H
#define OSDETECT_H

#if !defined(WIN32) && !defined(_WIN32) && !defined(__WIN32)
#define _UNIX
#define PLATFORM_LINUX
#else
#define PLATFORM_WINDOWS
#endif

#endif // OSDETECT_H
