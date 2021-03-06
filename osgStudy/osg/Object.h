//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_OBJECT
#define OSG_OBJECT 1

#include <osg/Referenced.h>
#include <osg/CopyOp.h>
#include <osg/ref_ptr.h>

namespace osg {

/** META_Object macro define the standard clone, isSameKindAs and className methods.
  * Use when subclassing from Object to make it more convinient to define 
  * the standard pure virtual clone, isSameKindAs and className methods 
  * which are required for all Object subclasses.*/
#define META_Object(library,name) \
        virtual osg::Object* cloneType() const { return osgNew name (); } \
        virtual osg::Object* clone(const osg::CopyOp& copyop) const { return osgNew name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; }\
        virtual const char* className() const { return #name; }


/** Base class/standard interface for objects which require IO support, 
    cloning and reference counting.
    Based on GOF Composite, Prototype and Template Method patterns.
*/
class SG_EXPORT Object : public Referenced
{
    public:


        /** Construct an object. Note Object is a pure virtual base class
            and therefore cannot be constructed on its own, only derived
            classes which override the clone and className methods are
            concrete classes and can be constructed.*/
        inline Object():Referenced(),_dataVariance(DYNAMIC) {}

        /** Copy constructor, optional CopyOp object can be used to control
          * shallow vs deep copying of dynamic data.*/
        Object(const Object&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        /** Clone the type of an object, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* cloneType() const = 0;

        /** Clone the an object, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* clone(const CopyOp&) const = 0;

        virtual bool isSameKindAs(const Object*) const { return true; }

        /** return the name of the object's library. Must be defined
            by derived classes. The OpenSceneGraph convention the is
            that the namspace of a library is the same as the library name.*/
        virtual const char* libraryName() const = 0;

        /** return the name of the object's class type. Must be defined
            by derived classes.*/
        virtual const char* className() const = 0;
        

        enum DataVariance
        {
            DYNAMIC,
            STATIC
        };
        
        /** Set the data variance of this object.
           * Can be set to either STATIC for values that do not change over the lifetime of the object,
           * or DYNAMIC for values that vary over the lifetime of the object. The DataVariance value
           * can be used be routines such as optimzation codes that wish to share static data.*/
        inline void setDataVariance(const DataVariance dv) { _dataVariance = dv; }

        /** Get the data variance of this object.*/
        inline const DataVariance getDataVariance() const { return _dataVariance; }


        /**
         * Set user data, data must be subclased from Referenced to allow
         * automatic memory handling.  If you own data isn't directly 
         * subclassed from Referenced then create and adapter object
         * which points to your own objects and handles the memory addressing.
         */
        inline void setUserData(Referenced* obj) { _userData = obj; }
        
        /** Get user data.*/
        inline Referenced* getUserData() { return _userData.get(); }
        
        /** Get const user data.*/
        inline const Referenced* getUserData() const { return _userData.get(); }


    protected:

        /** Object destructor. Note, is protected so that Objects cannot
            be deleted other than by being dereferenced and the reference
            count being zero (see osg::Referenced), preventing the deletion
            of nodes which are still in use. This also means that
            Node's cannot be created on stack i.e Node node will not compile,
            forcing all nodes to be created on the heap i.e Node* node
            = new Node().*/
        virtual ~Object() {}
        
         DataVariance _dataVariance;

        ref_ptr<Referenced> _userData;

    private:

        /** disallow any copy operator.*/
        Object& operator = (const Object&) { return *this; }
};

}

#endif
