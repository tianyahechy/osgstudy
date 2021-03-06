//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_BLENDFUNC
#define OSG_BLENDFUNC 1

#include <osg/StateAttribute.h>

namespace osg {

/** BlendFunc - encapsulates the OpenGL blend/transparency state.*/
class SG_EXPORT BlendFunc : public StateAttribute
{
    public :

        BlendFunc();
        
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        BlendFunc(const BlendFunc& trans,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(trans,copyop),
            _source_factor(trans._source_factor),
            _destination_factor(trans._destination_factor) {}

        META_StateAttribute(osg, BlendFunc,BLENDFUNC);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(BlendFunc,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_source_factor)
            COMPARE_StateAttribute_Parameter(_destination_factor)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_BLEND);
        }

        enum BlendFuncMode {
            DST_ALPHA            = GL_DST_ALPHA,
            DST_COLOR            = GL_DST_COLOR,
            ONE                  = GL_ONE,
            ONE_MINUS_DST_ALPHA  = GL_ONE_MINUS_DST_ALPHA,
            ONE_MINUS_DST_COLOR  = GL_ONE_MINUS_DST_COLOR,
            ONE_MINUS_SRC_ALPHA  = GL_ONE_MINUS_SRC_ALPHA,
            ONE_MINUS_SRC_COLOR  = GL_ONE_MINUS_SRC_COLOR,
            SRC_ALPHA            = GL_SRC_ALPHA,
            SRC_ALPHA_SATURATE   = GL_SRC_ALPHA_SATURATE,
            SRC_COLOR            = GL_SRC_COLOR,
            ZERO                 = GL_ZERO
        };

        inline void setFunction( const int source, const int destination )
        {
            _source_factor = source;
            _destination_factor = destination;
        }

        void setSource(const int source) { _source_factor = source; }
        inline const int getSource() const { return _source_factor; }
        
        void setDestination(const int destination) { _destination_factor = destination; }
        inline const int getDestination() const { return _destination_factor; }

        virtual void apply(State& state) const;

    protected :

        virtual ~BlendFunc();

        int _source_factor;
        int _destination_factor;
};

}

#endif
