//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_COPYOP
#define OSG_COPYOP 1

#include <osg/Export.h>

namespace osg {

class Referenced;
class Object;
class Image;
class Texture;
class StateSet;
class StateAttribute;
class Node;
class Drawable;

/** Copy Op(erator) used to control the whether shallow or deep copy is used
  * during copy construction and clone operation.*/
class SG_EXPORT CopyOp
{

    public:
    
        enum Options
        {
            SHALLOW_COPY = 0,
            DEEP_COPY_OBJECTS = 1,
            DEEP_COPY_NODES = 2,
            DEEP_COPY_DRAWABLES = 4,
            DEEP_COPY_STATESETS = 8,
            DEEP_COPY_STATEATTRIBUTES = 16,
            DEEP_COPY_TEXTURES = 32,
            DEEP_COPY_IMAGES = 64,
            DEEP_COPY_ALL = 0xffffffff
        };

        typedef unsigned int CopyFlags;

        inline CopyOp(CopyFlags flags=SHALLOW_COPY):_flags(flags) {}
        virtual ~CopyOp() {}

        virtual Referenced*     operator() (const Referenced* ref) const;
        virtual Object*         operator() (const Object* obj) const;
        virtual Node*           operator() (const Node* node) const;
        virtual Drawable*       operator() (const Drawable* drawable) const;
        virtual StateSet*       operator() (const StateSet* stateset) const;
        virtual StateAttribute* operator() (const StateAttribute* attr) const;
        virtual Texture*        operator() (const Texture* text) const;
        virtual Image*          operator() (const Image* image) const;

    protected:
    
        CopyFlags _flags;
};

}

#endif
