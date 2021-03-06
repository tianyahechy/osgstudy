//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef __OSG_MATH
#define __OSG_MATH

#include <cmath>

#if defined(WIN32) || defined (macintosh)|| defined (sun) || defined (__DARWIN_OSX__)

    #include <float.h>


    // PJA MAC OSX
    // This appears to be the simplest way to get these defined under MACOSX
    // where they arent in math.h

    #ifndef acosf
    #define acosf (float)acos
    #endif

    #ifndef asinf
    #define asinf (float)asin
    #endif

    #ifndef cosf
    #define cosf (float)cos
    #endif

    #ifndef sinf
    #define sinf (float)sin
    #endif

    #ifndef logf
    #define logf (float)log
    #endif

    #ifndef floorf
    #define floorf (float)floor
    #endif

    #ifndef powf
    #define powf (float)pow
    #endif

    #ifndef sqrtf
    #define sqrtf (float)sqrt
    #endif

    #ifndef fabsf
    #define fabsf (float)fabs
    #endif

    #ifndef isnanf
    #define isnanf (float)isnan
    #endif

#endif

namespace osg {

// define the stand trig values
#ifdef PI
#undef PI
#undef PI_2
#undef PI_4
#endif
const double PI   = 3.14159265358979323846;
const double PI_2 = 1.57079632679489661923;
const double PI_4 = 0.78539816339744830962;

template<typename T>
inline T clampTo(T v,T minimum,T maximum) { return v<minimum?minimum:v>maximum?maximum:v; }

template<typename T>
inline T clampAbove(T v,T minimum) { return v<minimum?minimum:v; }

template<typename T>
inline T clampBelow(T v,T maximum) { return v>maximum?maximum:v; }

template<typename T>
inline T sign(T v) { return v<(T)0?(T)-1:(T)1; }

template<typename T>
inline T square(T v) { return v*v; }

template<typename T>
inline T signedSquare(T v) { return v<(T)0?-v*v:v*v;; }

inline float inDegrees(float angle) { return angle*(float)PI/180.0f; }
inline double inDegrees(double angle) { return angle*PI/180.0; }

template<typename T>
inline T inRadians(T angle) { return angle; }

inline float DegreesToRadians(float angle) { return angle*(float)PI/180.0f; }
inline double DegreesToRadians(double angle) { return angle*PI/180.0; }

inline float RadiansToDegrees(float angle) { return angle*180.0f/(float)PI; }
inline double RadiansToDegrees(double angle) { return angle*180.0/PI; }

#if defined(WIN32) && !defined(__CYGWIN__) && !defined(__MWERKS__)
    inline bool isNaN(float v) { return _isnan(v)!=0; }
    inline bool isNaN(double v) { return _isnan(v)!=0; }
#else
    inline bool isNaN(float v) { return isnan(v); }
    inline bool isNaN(double v) { return isnan(v); }
#endif


/** compute the volume of tetrahedron */
template<typename T>
inline float computeVolume(const T& a,const T& b,const T& c,const T& d)
{
    return fabsf(((b-c)^(a-b))*(d-b));
}

/** compute the volume of prism */
template<typename T>
inline float computeVolume(const T& f1,const T& f2,const T& f3,
                           const T& b1,const T& b2,const T& b3)
{
    return computeVolume(f1,f2,f3,b1)+
           computeVolume(b1,b2,b3,f2)+
           computeVolume(b1,b3,f2,f3);
}

}

#endif  // __OSG_MATH
