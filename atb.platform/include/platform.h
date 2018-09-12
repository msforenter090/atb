// -----------------------------------------------------------------------------
// Defines platform independent types.
// -----------------------------------------------------------------------------

#pragma once

#ifdef __linux__
#include<stdint.h>
// -----------------------------------------------------------------------------
// Types for Linux system compiled with gcc or g++.
// -----------------------------------------------------------------------------

#define BYTE8       int8_t
#define UBYTE8      unsigned int8_t

#define SHORT16     int16_t
#define USHORT16    unsigned int16_t

#define INT32       int32_t
#define UINT32      unsigned int32_t

#define LONG64      int64_t
#define ULONG64     unsigned int64_t

#elif _WIN32

// -----------------------------------------------------------------------------
// Types for Linux system compiled with gcc or g++.
// -----------------------------------------------------------------------------

#define BYTE8       __int8
#define UBYTE8      unsigned __int8

#define SHORT16     __int16
#define USHORT16    unsigned __int8

#define INT32       __int32
#define UINT32      unsigned __int32

#define LONG64      __int64
#define ULONG64     unsigned __int64

#else
#error Cannot compile on this platform.
#endif

