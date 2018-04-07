
#pragma once
#ifndef NDGM_CONFIG_H
#define NDGM_CONFIG_H

// NDGM_COMPILE_DLL
//  - We're compiling the Nodegrams.dll (or .dylib etc)
#if defined (NDGM_COMPILE_DLL)

	#ifdef _WIN32
		#if defined (__GNUC__)
			#define NDGM_EXPORT __attribute__((dllexport))
		#else
			#define NDGM_EXPORT __declspec(dllexport)
		#endif
	#endif

// NDGM_COMPILE_STATIC
//  - We're compiling as a static library
#elif defined (NDGM_COMPILE_STATIC)

	#define NDGM_EXPORT

// NDGM_DLL
// - We're including using the dll
#elif defined (NDGM_DLL)

	#ifdef _WIN32
		#ifdef __GNUC__
			#define NDGM_EXPORT __attribute__((dllimport))
		#else
			#define NDGM_EXPORT __declspec(dllimport)
		#endif
	#endif

// - We're including Dsse using a static library
#else

	#define NDGM_EXPORT

#endif // if defined (NDGM_COMPILE_DLL)


#ifndef NDGM_ALLOC_STATS
	#define NDGM_ALLOC_STATS 0
#endif

#if NDGM_ALLOC_STATS

	#include <memory>
    void* operator new(std::size_t size) throw(std::bad_alloc);
    void operator delete(void *mem) throw();

	#define NDGM_IF_ALLOC_STATS(X) X
#else
	#define NDGM_IF_ALLOC_STATS(X) // ignore
#endif // NDGM_ALLOC_STATS

#endif // NDGM_CONFIG_H
