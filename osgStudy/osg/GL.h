//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_GL
#define OSG_GL 1

#ifndef WIN32

    // non windows, doesn't require nonsense as seen below :-)    
    #ifndef __gl_h_
        #ifdef __DARWIN_OSX__
            #include <OpenGL/gl.h>
        #else
	        #include <GL/gl.h>
	    #endif
    #endif

    // required for compatibility with glext.h sytle function definitions of 
    // OpenGL extensions, such as in src/osg/Point.cpp.
    #ifndef APIENTRY
        #define APIENTRY
    #endif

#else

#if defined(__CYGWIN__) || defined(__MINGW32__)
#  ifndef APIENTRY
#   define GLUT_APIENTRY_DEFINED
#   define APIENTRY    __stdcall
#  endif
	   // XXX This is from Win32's <winnt.h> 
#  ifndef CALLBACK
#    define CALLBACK __stdcall
#  endif

#else // ! __CYGWIN__

    // Under windows avoid including <windows.h>
    // to avoid name space pollution, but Win32's <GL/gl.h> 
    // needs APIENTRY and WINGDIAPI defined properly. 
    // F
    # if defined(__MWERKS__)
    #  define  WIN32_LEAN_AND_MEAN
    #  include <windows.h>
    # else
       // XXX This is from Win32's <windef.h> 
    #  ifndef APIENTRY
    #   define GLUT_APIENTRY_DEFINED
    #   if (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED)
    #    define APIENTRY    __stdcall
    #   else
    #    define APIENTRY
    #   endif
    #  endif
       // XXX This is from Win32's <winnt.h> 
    #  ifndef CALLBACK
    #   if (defined(_M_MRX000) || defined(_M_IX86) || defined(_M_ALPHA) || defined(_M_PPC)) && !defined(MIDL_PASS)
    #    define CALLBACK __stdcall
    #   else
    #    define CALLBACK
    #   endif
    #  endif

#endif // __CYGWIN__

	   // XXX This is from Win32's <wingdi.h> and <winnt.h> 
#  ifndef WINGDIAPI
#   define GLUT_WINGDIAPI_DEFINED
#   define WINGDIAPI __declspec(dllimport)
#  endif
	   // XXX This is from Win32's <ctype.h> 
#  ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#   define _WCHAR_T_DEFINED
#  endif
# endif

    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif

#endif

#endif  // __osgGL_h
