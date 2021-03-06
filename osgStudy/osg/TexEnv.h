//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_TEXENV
#define OSG_TEXENV 1

#include <osg/GL.h>
#include <osg/StateAttribute.h>
#include <osg/Vec4.h>

namespace osg {

/** TexEnv - encapsulates the OpenGL glTexEnv (texture environment) state.*/
class SG_EXPORT TexEnv : public StateAttribute
{
    public :

        TexEnv();
        
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        TexEnv(const TexEnv& texenv,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(texenv,copyop),
            _mode(texenv._mode),
            _color(texenv._color) {}


        META_StateAttribute(osg, TexEnv, TEXENV);

        virtual bool isTextureAttribute() const { return true; }

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(TexEnv,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_mode)
            COMPARE_StateAttribute_Parameter(_color)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        enum Mode {
            DECAL     = GL_DECAL,
            MODULATE  = GL_MODULATE,
            BLEND     = GL_BLEND,
            REPLACE   = GL_REPLACE
        };

        void setMode( const Mode mode ) { _mode = mode; }
        
        const Mode getMode() const { return _mode; }
        
        void setColor( const Vec4& color ) { _color = color; }
        
        Vec4& getColor() { return _color; }

        const Vec4& getColor() const { return _color; }


        virtual void apply(State& state) const;

    protected :

        virtual ~TexEnv( void );

        Mode        _mode;
        osg::Vec4   _color;
};

}

#endif
