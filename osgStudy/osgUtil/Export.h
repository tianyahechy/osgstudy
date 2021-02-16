#ifndef OSGUTIL_EXPORT
#define OSGUTIL_EXPORT 1


#if  defined(_MSC_VER)
#pragma warning( disable : 4244)
#pragma warning(disable : 4251)
#pragma warning(disable : 4267)
#pragma warning(disable : 4275)
#pragma warning(disable : 4290)
#pragma warning(disable : 4786)
#endif

#if defined(_MSC_VER) || defined( __CYGWIN__) || defined(__MINGW32__) || defined(__BCPLUSPLUS__) || defined(__MWERKS__)
#ifdef OSGUTIL_LIBRARY
#define OSGUTIL_EXPORT __declspec(dllexport)
#else
#define OSGUTIL_EXPORT __declspec(dllimport)
#endif
#else
#define OSGUTIL_EXPORT
#endif



#endif
