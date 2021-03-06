//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_CLIPPLANE
#define OSG_CLIPPLANE 1

#include "Plane.h"
#include "StateAttribute.h"

namespace osg {

/** ClipPlane state class which encapsulates OpenGL glClipPlane() functionality.*/
class SG_EXPORT ClipPlane : public StateAttribute
{
    public :

        ClipPlane();
        inline ClipPlane(unsigned int no,const Vec4& plane)    { setClipPlaneNum(no); setClipPlane(plane); }
        inline ClipPlane(unsigned int no,const Plane& plane)   { setClipPlaneNum(no); setClipPlane(plane); }
        inline ClipPlane(unsigned int no,const double a,const double b,const double c,const double d)  { setClipPlaneNum(no); setClipPlane(a,b,c,d); }

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        ClipPlane(const ClipPlane& cp,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(cp,copyop)
        {
            _clipPlane[0]=cp._clipPlane[0];
            _clipPlane[1]=cp._clipPlane[1];
            _clipPlane[2]=cp._clipPlane[2];
            _clipPlane[3]=cp._clipPlane[3];
            _clipPlaneNum=cp._clipPlaneNum;
        }
        
        META_StateAttribute(osg, ClipPlane, (Type)(CLIPPLANE+_clipPlaneNum));
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(ClipPlane,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_clipPlaneNum)
            COMPARE_StateAttribute_Parameter(_clipPlane[0])
            COMPARE_StateAttribute_Parameter(_clipPlane[1])
            COMPARE_StateAttribute_Parameter(_clipPlane[2])
            COMPARE_StateAttribute_Parameter(_clipPlane[3])

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back((GLMode)(GL_CLIP_PLANE0+_clipPlaneNum));
        }


	/** Set the clip plane, using a Vec4 to define plane. */
        void setClipPlane(const Vec4& plane);

	/** Set the clip plane, using a Plane to define plane. */
        void setClipPlane(const Plane& plane);

	/** Set the clip plane, using a double[4] to define plane. */
        void setClipPlane(const double* plane);

	/** Set the clip plane, using a a to define plane. */
        void setClipPlane(const double a,const double b,const double c,const double d)
        {
            _clipPlane[0]=a;_clipPlane[1]=b;_clipPlane[2]=c;_clipPlane[3]=d;
        }

	/** Get the clip plane, values entered into a Vec4 passed to the getClipPlane. */
        void getClipPlane(Vec4& plane) const;

	/** Get the clip plane, values entered into a Plane passed to the getClipPlane. */
        void getClipPlane(Plane& plane) const;

	/** Get the clip plane, values entered into a double[4] passed to the getClipPlane. */
        void getClipPlane(double* plane) const;

	/** Set the clip plane number. */
        void setClipPlaneNum(const unsigned int num);

	/** Get the clip plane number. */
        const unsigned int getClipPlaneNum() const;

	/** Apply the clip plane's state to the OpenGL state machine. */
        virtual void apply(State& state) const;

    protected :
    
        virtual ~ClipPlane();
        
        double              _clipPlane[4];
        unsigned int        _clipPlaneNum;

};

}

#endif
