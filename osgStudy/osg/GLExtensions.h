//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_GLEXTENSIONS
#define OSG_GLEXTENSIONS 1

#include <osg/Export.h>

namespace osg {

/** return true if OpenGL "extension" is supported.
  * note: Must only called within a valid OpenGL context,
  * undefined behavior may occur otherwise.
  */
SG_EXPORT extern const bool isGLExtensionSupported(const char *extension);

/** return the address of the specified OpenGL function.
  * return NULL if function not supported by OpenGL library.
  */
SG_EXPORT extern void* getGLExtensionFuncPtr(const char *funcName);

/** return the address of the specified OpenGL function, if not found then
  * check a second function name, if this fails then return NULL as function is
  * not supported by OpenGL library.  This is usual for checking something
  * like glActiveTexture (which is in OGL1.3) or glActiveTextureARB.
  */
inline void* getGLExtensionFuncPtr(const char *funcName,const char *fallbackFuncName)
{
    void* ptr = getGLExtensionFuncPtr(funcName);
    if (ptr) return ptr;
    return getGLExtensionFuncPtr(fallbackFuncName);
}

}

#endif
