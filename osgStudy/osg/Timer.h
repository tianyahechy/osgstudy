//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_TIMER
#define OSG_TIMER 1

#include <osg/Export.h>


#if defined(_MSC_VER)
	namespace osg {
	    typedef __int64 Timer_t;
	}
#elif defined(__linux) || defined(__FreeBSD__) || defined(__CYGWIN__)|| defined(__MINGW32__)
	namespace osg {
	    typedef unsigned long long Timer_t;
	}
#elif defined(__sgi)
	namespace osg {
	    typedef unsigned long long Timer_t;
	}
#elif defined(unix)
	namespace osg {
	    typedef unsigned long long Timer_t;
	}
#elif defined __APPLE__ || defined macintosh
	namespace osg {
		typedef double Timer_t;
	}
#else
    #include <ctime>
	namespace osg {
	    typedef std::clock_t Timer_t;
	}
#endif

namespace osg {

/** A high resolution, low latency time stamper.*/
class SG_EXPORT Timer {

    public:

        Timer();
        ~Timer() {}

	#if defined __DARWIN_OSX__  || defined macintosh
	// PJA MAC OSX - inline Tick() pollutes namespace so badly 
	// we cant compile, due to Carbon.h ...
        Timer_t tick() const;
	#else
		inline Timer_t tick() const;
	#endif
		
        inline double delta_s( Timer_t t1, Timer_t t2 ) const { return (double)(t2 - t1)*_secsPerClick; }
        inline double delta_m( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e3; }
        inline double delta_u( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e6; }
        inline double delta_n( Timer_t t1, Timer_t t2 ) const { return delta_s(t1,t2)*1e9; }

    private :

        double                  _secsPerClick;
        bool                    _useStandardClock;
       
#       ifdef __sgi
        unsigned long*          _clockAddress_32;
        unsigned long long*     _clockAddress_64;
        int                     _cycleCntrSize;
#       endif
        
};

}

#if defined(_MSC_VER)

    #include <time.h>
    #pragma optimize("",off)

    namespace osg{

        inline Timer_t Timer::tick( void ) const
        {
            if (_useStandardClock) return clock();

            volatile Timer_t ts;
            volatile unsigned int HighPart;
            volatile unsigned int LowPart;
            _asm
            {
                xor eax, eax        //  Used when QueryPerformanceCounter()
                xor edx, edx        //  not supported or minimal overhead
                _emit 0x0f          //  desired
                _emit 0x31          //
                mov HighPart,edx
                mov LowPart,eax
            }
            //ts = LowPart | HighPart >> 32;
            *((unsigned int*)&ts) = LowPart;
            *((unsigned int*)&ts+1) = HighPart;
            return ts;
        }

    }
    #pragma optimize("",on)

#elif defined(__MINGW32__)

    #include <sys/time.h>

    #define CLK(x)      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x))
    namespace osg{

	inline Timer_t Timer::tick() const
	{
		if (_useStandardClock)
			return clock();
		else
		{
			Timer_t x;CLK(x);return x;
		}
	}

    }

#elif defined(__linux) || defined(__FreeBSD__) || defined(__CYGWIN__)

    #include <sys/time.h>

    #define CLK(x)      __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x))

    namespace osg{

        inline Timer_t Timer::tick() const
        {
            if (_useStandardClock)
            {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
            }
            else
            {
                Timer_t x;CLK(x);return x;
            }
        }

    }
  
#elif defined(__sgi)

    #include <sys/time.h>

    namespace osg{

        inline  Timer_t Timer::tick()  const
        {
            if (_useStandardClock)
            {
                struct timeval tv;
                gettimeofday(&tv, NULL);
                return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
            }
            else
            {
                if ( _clockAddress_64 )
                    return *_clockAddress_64;
                else
                    return *_clockAddress_32;
            }
        }
    }
    
#elif defined(unix)

    #include <sys/time.h>

    namespace osg{
        inline  Timer_t Timer::tick() const
        {
            struct timeval tv;
            gettimeofday(&tv, NULL);
            return ((osg::Timer_t)tv.tv_sec)*1000000+(osg::Timer_t)tv.tv_usec;
        }
    }

#elif !defined (__DARWIN_OSX__) && !defined (macintosh)

    // no choice, always use std::clock()
    namespace osg{

        inline  Timer_t Timer::tick( void ) const { return std::clock(); }
    }

#endif

// note, MacOSX compiled in the Timer.cpp.

#endif
