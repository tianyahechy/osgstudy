//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_FOG
#define OSG_FOG 1

#include <osg/StateAttribute.h>
#include <osg/Types.h>
#include <osg/Vec4.h>

namespace osg {


/** Fog - encapsulates OpenGL fog state. */ 
class SG_EXPORT Fog : public StateAttribute
{
    public :

        Fog();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Fog(const Fog& fog,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(fog,copyop),
            _mode(fog._mode),
            _density(fog._density),
            _start(fog._start),
            _end(fog._end),
            _color(fog._color) {}

        META_StateAttribute(osg, Fog,FOG);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Fog,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_mode)
            COMPARE_StateAttribute_Parameter(_density)
            COMPARE_StateAttribute_Parameter(_start)
            COMPARE_StateAttribute_Parameter(_end)
            COMPARE_StateAttribute_Parameter(_color)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_FOG);
        }

        enum Mode {
            LINEAR = GL_LINEAR,
            EXP    = GL_EXP,
            EXP2   = GL_EXP2
        };

        inline void  setMode( const Mode mode )         { _mode = mode; }
        inline Mode getMode() const                     { return _mode; }

        inline void  setDensity( const float density )  { _density = density; }
        inline const float getDensity() const           { return _density; }

        inline void  setStart( const float start )      { _start = start; }
        inline const float getStart() const             { return _start; }

        inline void  setEnd( const float end )          { _end = end; }
        inline const float getEnd() const               { return _end; }

        inline void  setColor( const Vec4 &color )      { _color = color; }
        inline const Vec4& getColor() const             { return _color; }

        virtual void apply(State& state) const;

    protected :

        virtual ~Fog();

        Mode   _mode;
        float  _density;
        float  _start;
        float  _end;
        Vec4 _color;
};

}

#endif
