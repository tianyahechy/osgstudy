//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_LINESTIPPLE
#define OSG_LINESTIPPLE 1

#include <osg/StateAttribute.h>

namespace osg {

class SG_EXPORT LineStipple : public StateAttribute
{
    public :

        LineStipple();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        LineStipple(const LineStipple& lw,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
          StateAttribute(lw,copyop),
          _factor(lw._factor),
          _pattern(lw._pattern) {}

        META_StateAttribute(osg, LineStipple, LINESTIPPLE);

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(LineStipple,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_factor)
            COMPARE_StateAttribute_Parameter(_pattern)

            return 0; // passed all the above comparison macro's, must be equal.
        }
        
        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_LINE_STIPPLE);
        }

        void setFactor(const int factor);
        inline const int getFactor() const { return _factor; }

        void setPattern(const unsigned short pattern);
        inline const unsigned short getPattern() const { return _pattern; }

        virtual void apply(State& state) const;


    protected :

        virtual ~LineStipple();

        int			_factor;
        unsigned short	        _pattern;

};

}

#endif
