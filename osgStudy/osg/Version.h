//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_VERSION
#define OSG_VERSION 1

#include <osg/Export.h>

extern "C" {

/**
 * osgGetVersion() returns the library version number.
 * Numbering convention : OpenSceneGraph-0.8-31 will return 0.8.31 from osgGetVersion.
 *
 * This C function can be also used to check for the existence of the OpenSceneGraph
 * library using autoconf and its m4 macro AC_CHECK_LIB.
 *
 * Here is the code to add to your configure.in:
 \verbatim
 #
 # Check for the OpenSceneGraph (OSG) library
 #
 AC_CHECK_LIB(osg, osgGetVersion, ,
    [AC_MSG_ERROR(OpenSceneGraph library not found. See http://www.openscenegraph.org)],)
 \endverbatim
*/
extern SG_EXPORT const char* osgGetVersion();

/**
 * osgGetLibraryName() returns the library name in human friendly form.
*/
extern SG_EXPORT const char* osgGetLibraryName();

}

#endif
