//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_REFERENCED
#define OSG_REFERENCED 1

#include <osg/Export.h>

namespace osg {

/** Base class from providing referencing counted objects.*/
class SG_EXPORT Referenced
{

    public:
        Referenced() { _refCount=0; }
        Referenced(const Referenced&) { _refCount=0; }

        inline Referenced& operator = (Referenced&) { return *this; }

        /** increment the reference count by one, indicating that 
            this object has another pointer which is referencing it.*/
        inline void ref() const { ++_refCount; }
        
        /** decrement the reference count by one, indicating that 
            a pointer to this object is referencing it.  If the
            reference count goes to zero, it is assumed that this object
            is no longer referenced and is automatically deleted.*/
        inline void unref() const { --_refCount; if (_refCount<=0) delete this; }
        
        /** decrement the reference count by one, indicating that 
            a pointer to this object is referencing it.  However, do
            not delete it, even if ref count goes to 0.  Warning, unref_nodelete() 
            should only be called if the user knows exactly who will
            be resonsible for, one should prefer unref() over unref_nodelete() 
            as the later can lead to memory leaks.*/
        inline void unref_nodelete() const { --_refCount; }
        
        /** return the number pointers currently referencing this object. */
        inline const int referenceCount() const { return _refCount; }

    protected:
        virtual ~Referenced();
        mutable int _refCount;

};

}

#endif
