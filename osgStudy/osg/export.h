#ifndef OSG_EXPORT
#define OSG_EXPORT 1

#define USE_DEPRECATED_API

#if  defined(_MSC_VER)
#pragma warning( disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4275)
#pragma warning(disable : 4290)
#pragma warning(disable : 4786)
#endif

#if defined(_MSC_VER) || defined( __CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
	#ifdef SG_LIBRARY
	#define SG_EXPORT __declspec(dllexport)
	#else
	#define SG_EXPORT __declspec(dllimport)
	#endif
#else
	#define SG_EXPORT
#endif

#ifdef _MSC_VER
	#if (_MSC_VER >= 1300)
		#define __STL_MEMBER_TEMPLATES
	#endif
#endif

#ifndef NULL
	#ifdef __cplusplus
		#define NULL	0
	#else
		#define NULL	((void*) 0)
	#endif
#endif

#include <osg/MemoryManager.h>


#endif
