//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_LineWidth
#define OSG_LineWidth 1

#include <osg/StateAttribute.h>

namespace osg {

/** LineWidth - encapsulates the OpenGL glLineWidth for setting the width of lines in pixels.*/
class SG_EXPORT LineWidth : public StateAttribute
{
    public :

        LineWidth();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        LineWidth(const LineWidth& lw,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(lw,copyop),
            _width(lw._width) {}
            
        META_StateAttribute(osg, LineWidth, LINEWIDTH);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(LineWidth,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_width)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        void setWidth(const float width);
        inline const float getWidth() const { return _width; }

        virtual void apply(State& state) const;

    protected :

        virtual ~LineWidth();

        float       _width;

};

}

#endif
