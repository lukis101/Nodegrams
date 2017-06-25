
#pragma once
#ifndef DSSE_CONFIG_H
#define DSSE_CONFIG_H

// DSSE_COMPILE_DLL
//  - We're compiling the Dsse.dll (or .dylib etc)
#if defined (DSSE_COMPILE_DLL)

	#ifdef _WIN32
		#if defined (__GNUC__)
			#define DSSE_EXPORT __attribute__((dllexport))
		#else
			#define DSSE_EXPORT __declspec(dllexport)
		#endif
	#endif

// DSSE_COMPILE_STATIC
//  - We're compiling Dsse as a static library
#elif defined (DSSE_COMPILE_STATIC)

	#define DSSE_EXPORT

// DSSE_DLL
// - We're including Dsse using the dll
#elif defined (DSSE_DLL)

	#ifdef _WIN32
		#ifdef __GNUC__
			#define DSSE_EXPORT __attribute__((dllimport))
		#else
			#define DSSE_EXPORT __declspec(dllimport)
		#endif
	#endif

// - We're including Dsse using a static library
#else

	#define DSSE_EXPORT

#endif // if defined (DSSE_COMPILE_DLL)


// Enable animation functions.
#define DSSE_ANIMATE 1


#ifndef DSSE_ALLOC_STATS
	#define DSSE_ALLOC_STATS 0
#endif

#if DSSE_ALLOC_STATS

	#include <memory>
    void* operator new(std::size_t size) throw(std::bad_alloc);
    void operator delete(void *mem) throw();

	#define DSSE_IF_ALLOC_STATS(X) X
#else
	#define DSSE_IF_ALLOC_STATS(X) // ignore
#endif // DSSE_ALLOC_STATS

#endif // DSSE_CONFIG_H
