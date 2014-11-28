#ifndef CG1RAYTRACER_MACROS_HEADER
#define CG1RAYTRACER_MACROS_HEADER

#include <iostream>

#ifdef _MSC_VER
#define ALIGN(n) __declspec(align(n))
#define THREADLOCAL __declspec(thread)
#else
#define ALIGN(n) __attribute__((aligned(n)))
#define THREADLOCAL __thread
#endif

#define DEBUG true

/**
 * print debug message, due to the standard out arguments use << as concatination!
 */
#define LOG_DEBUG(message) if (DEBUG) std::cout << message << "\n"


#endif
