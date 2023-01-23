#ifndef DEFINES_H
#define DEFINES_H

#define TRUE 1
#define FALSE 0

// Unsigned types
typedef unsigned char uchar8;
typedef	unsigned short ushort16;
typedef unsigned short int usint16;
typedef unsigned long ulong32;
typedef unsigned int uint32;
typedef unsigned long long ullong64;

// Signed types
typedef signed char schar8;
typedef	signed short sshort16;
typedef signed long slong32;
typedef signed int sint32;
typedef signed long long sllong64;

// Floating point types
typedef float f32;
typedef double d64;

// Boolean types
typedef char b8;
typedef int b32;

// Platform detection
#if defined(__linux__) || defined(__gnu_linux__)
#define LF_PLATFORM_LINUX 1
#else
#error "ERROR: Unknown platform."
#endif

// Inline functions
#if defined(__linux__) || defined(__gnu_linux__)
#define INLINE static inline
#endif

#endif // DEFINES_H
