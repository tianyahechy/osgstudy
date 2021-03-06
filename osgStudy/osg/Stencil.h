//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_STENCIL
#define OSG_STENCIL 1

#include <osg/StateAttribute>
#include <osg/Types>

namespace osg {

/** Encapsulate OpenGL glStencilFunc/Op/Mask functions.
*/     
class SG_EXPORT Stencil : public StateAttribute
{
    public :
    
    
        Stencil();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Stencil(const Stencil& stencil,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(stencil,copyop),
            _func(stencil._func),
            _funcRef(stencil._funcRef),
            _funcMask(stencil._funcMask),
            _sfail(stencil._sfail),
            _zfail(stencil._zfail),
            _zpass(stencil._zpass),
            _writeMask(stencil._writeMask) {}


        META_StateAttribute(osg, Stencil, STENCIL);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Stencil,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_func)
            COMPARE_StateAttribute_Parameter(_funcRef)
            COMPARE_StateAttribute_Parameter(_funcMask)
            COMPARE_StateAttribute_Parameter(_sfail)
            COMPARE_StateAttribute_Parameter(_zfail)
            COMPARE_StateAttribute_Parameter(_zpass)
            COMPARE_StateAttribute_Parameter(_writeMask)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_STENCIL_TEST);
        }

        enum Function
        {
            NEVER = GL_NEVER,
            LESS = GL_LESS,
            EQUAL = GL_EQUAL,
            LEQUAL = GL_LEQUAL,
            GREATER = GL_GREATER,
            NOTEQUAL = GL_NOTEQUAL,
            GEQUAL = GL_GEQUAL,
            ALWAYS = GL_ALWAYS
        };

        inline void setFunction(const Function func,int ref,uint mask)
        {
            _func = func;
            _funcRef = ref;
            _funcMask = mask;
        }
        
        inline const Function getFunction() const { return _func; }
        
        inline const int getFunctionRef() const { return _funcRef; }

        inline const uint getFunctionMask() const { return _funcMask; }
        
        
        enum Operation 
        {
            KEEP = GL_KEEP,
            ZERO = GL_ZERO,
            REPLACE = GL_REPLACE,
            INCR = GL_INCR,
            DECR = GL_DECR,
            INVERT = GL_INVERT
        };
        
        /** set the operations to apply when the various stencil and depth 
          * tests fail or pass.  First parameter is to control the operation
          * when the stencil test fails.  The second parameter is to control the
          * operation when the stencil test passes, but depth test fails. The
          * third parameter controls the operation when both the stencil test
          * and depth pass.  Ordering of parameter is the same as if using
          * glStencilOp(,,).*/
        inline void setOperation(const Operation sfail, const Operation zfail, const Operation zpass)
        {
            _sfail = sfail;
            _zfail = zfail;
            _zpass = zpass;
        }
        
        /** get the operation when the stencil test fails.*/
        inline const Operation getStencilFailOperation() const { return _sfail; }
        
        /** get the operation when the stencil test passes but the depth test fails*/
        inline const Operation getStencilPassAndDepthFailOperation() const { return _zfail; }
        
        /** get the operation when both the stencil test and the depth test pass*/
        inline const Operation getStencilPassAndDepthPassOperation() const { return _zpass; }
        

        inline void setWriteMask(uint mask) { _writeMask = mask; }
        
        inline const uint getWriteMask() const { return _writeMask; }


        virtual void apply(State& state) const;

    protected:
    
        virtual ~Stencil();

        Function            _func;
        int                 _funcRef;
        uint                _funcMask;
        
        Operation           _sfail;
        Operation           _zfail;
        Operation           _zpass;
        
        uint                _writeMask;

};

}

#endif
