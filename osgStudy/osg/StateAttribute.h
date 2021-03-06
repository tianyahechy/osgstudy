//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_STATEATTRIBUTE
#define OSG_STATEATTRIBUTE 1

#include <osg/Export.h>
#include <osg/Object.h>
#include <osg/GL.h>

#include <typeinfo>
#include <vector>

namespace osg {

// forward declare State & StateSet
class State;
class StateSet;

/** META_StateAttribute macro define the standard clone, isSameKindAs,
  * className and getType methods.
  * Use when subclassing from Object to make it more convinient to define 
  * the standard pure virtual methods which are required for all Object 
  * subclasses.*/
#define META_StateAttribute(library,name,type) \
        virtual osg::Object* cloneType() const { return osgNew name(); } \
        virtual osg::Object* clone(const osg::CopyOp& copyop) const { return osgNew name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* libraryName() const { return #library; } \
        virtual const char* className() const { return #name; } \
        virtual const Type getType() const { return type; }

/** COMPARE_StateAttribute_Types macro is a helper for implementing the StatateAtribute::compare(..) method.*/
#define COMPARE_StateAttribute_Types(TYPE,rhs_attribute) \
            if (this==&rhs_attribute) return 0;\
            const std::type_info* type_lhs = &typeid(*this);\
            const std::type_info* type_rhs = &typeid(rhs_attribute);\
            if (type_lhs->before(*type_rhs)) return -1;\
            if (*type_lhs != *type_rhs) return 1;\
            const TYPE& rhs = static_cast<const TYPE&>(rhs_attribute);


/** COMPARE_StateAttribute_Parameter macro is a helper for implementing the StatateAtribute::compare(..) method.
  * Macro assumes that variable rhs has been corrected defined by code preceesing
  * macro.*/
#define COMPARE_StateAttribute_Parameter(parameter) \
        if (parameter<rhs.parameter) return -1; \
        if (rhs.parameter<parameter) return 1;

/** Base class for state attribuets.
*/     
class SG_EXPORT StateAttribute : public Object
{
    public :
    
        /** GLMode is the value used in glEnable/glDisable(mode) */
        typedef GLenum          GLMode;
        /** GLModeValue is used to specified whether an mode is enabled (ON) or disabled (OFF).
          * GLMoveValue is also used to specify the override behavior of modes from parent to children. 
          * See enum Value description for more details.*/
        typedef unsigned int    GLModeValue;
        /** Override is used to specified the override behavior of StateAttributes
          * from from parent to children. 
          * See enum Value description for more details.*/
        typedef unsigned int	OverrideValue;

        /** list values which can be used in to set either GLModeValues
          * or OverrideValues. When using in conjunction with GLModeValues
          * all Values have meaning.  When using in conjection with 
          * StateAttribute OverrideValue only OFF,OVERRIDE and INHERIT
          * are meaningful. However, they are useful when using GLModeValue 
          * and OverrideValue in conjunction with each other as when using
          * StateSet::setAttributeAndModes(..).*/
        enum Values
        {
            /** means that associated GLMode and Override is disabled.*/
            OFF          = 0x0,
            /** means that associated GLMode is enabled and Override is disabled.*/
            ON           = 0x1,
            /** Overriding of GLMode's or StateAttributes is enabled.*/
            OVERRIDE     = 0x2,
            /** Equivilant to OFF | OVERRIDE.*/
            OVERRIDE_OFF = 0x2,
            /** Equivilant to ON | OVERRIDE.*/
            OVERRIDE_ON  = 0x3,
            /** means that GLMode or StateAttribute should in inherited from above.*/
            INHERIT      = 0x4
        };
        
        /** Type identifier to differentiate between different state types. */
        typedef unsigned int Type;

        /** Values of StateAttribute::Type used to aid identification
          * of different StateAttribute subclasses. Each subclass defines
          * it own value in the virtual Type getType() method.  When 
          * extending the osg's StateAttribute's simply define your
          * own Type value which is unique, using the StateAttribute::Type
          * enum as a guide of what values to use.  If your new subclass
          * needs to override a standard StateAttriubte then simple use 
          * that types value. */
        enum Types
        {
            TEXTURE,
            
            POLYGONMODE,
            POLYGONOFFSET,
            MATERIAL,
            ALPHAFUNC,
            ANTIALIAS,
            COLORTABLE,
            CULLFACE,
            FOG,
            FRONTFACE,
            
            LIGHT,
            LIGHT_0         =LIGHT,
            LIGHT_1,
            LIGHT_2,
            LIGHT_3,
            LIGHT_4,
            LIGHT_5,
            LIGHT_6,
            LIGHT_7,

            POINT,
            LINEWIDTH,
            LINESTIPPLE,
            SHADEMODEL,
            TEXENV,
            TEXGEN,
            TEXMAT,
            LIGHTMODEL,
            BLENDFUNC,
            STENCIL,
            COLORMASK,
            DEPTH,
            VIEWPORT,
            
            CLIPPLANE,
            CLIPPLANE_0     =CLIPPLANE,
            CLIPPLANE_1,
            CLIPPLANE_2,
            CLIPPLANE_3,
            CLIPPLANE_4,
            CLIPPLANE_5,
            
            COLORMATRIX
        };


        StateAttribute() { setDataVariance(STATIC); }
        
        StateAttribute(const StateAttribute& sa,const CopyOp& copyop=CopyOp::SHALLOW_COPY): 
            Object(sa,copyop) {}
        

        /** Clone the type of an attribute, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* cloneType() const = 0;

        /** Clone an attribute, with Object* return type.
            Must be defined by derived classes.*/
        virtual Object* clone(const CopyOp&) const = 0;

        /** return true if this and obj are of the same kind of object.*/
        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const StateAttribute*>(obj)!=NULL; }

        /** return the name of the attribute's library.*/
        virtual const char* libraryName() const { return "osg"; }

        /** return the name of the attribute's class type.*/
        virtual const char* className() const { return "StateAttribute"; }
        
        /** return the Type identifier of the attribute's class type.*/
        virtual const Type getType() const = 0;

        /** return true if StateAttribute is a type which controls texturing and needs to be issued w.r.t to specific texture unit.*/
        virtual bool isTextureAttribute() const { return false; }

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const = 0;
        
        bool operator <  (const StateAttribute& rhs) const { return compare(rhs)<0; }
        bool operator == (const StateAttribute& rhs) const { return compare(rhs)==0; }
        bool operator != (const StateAttribute& rhs) const { return compare(rhs)!=0; }
        

        /** return the modes associated with this StateSet*/        
        virtual void getAssociatedModes(std::vector<GLMode>& /*modes*/) const 
        {
            // default to no GLMode's associated with use of the StateAttribute.
        }
    
        /** apply the OpenGL state attributes. 
          * The global state for the current OpenGL context is passed
          * in to allow the StateAttribute to obtain details on the
          * the current context and state.
          */
        virtual void apply(State&) const = 0 ;
        
        /** default to nothing to compile - all state is applied immediately. */
        virtual void compile(State&) const {};

    protected:
    
        virtual ~StateAttribute() {}

};

}

#endif
