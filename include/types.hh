#pragma once

namespace au
{
    // Unsigned integers
    typedef unsigned char       u8;
    typedef unsigned short      u16;
    typedef unsigned int        u32;
    typedef unsigned long long  u64;

    // Signed integers
    typedef signed char         s8;
    typedef signed short        s16;
    typedef signed int          s32;
    typedef signed long long    s64;

    // Pointer-sized integer
    #if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8
        typedef long long ssize;
        typedef unsigned long long usize;
    #else
        typedef int ssize;
        typedef unsigned int usize;
    #endif
}