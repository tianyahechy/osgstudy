//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_POINT
#define OSG_POINT 1

#include <osg/Vec3.h>
#include <osg/StateAttribute.h>

namespace osg {

/** Point - encapsulates the OpenGL point smoothing and size state.*/
class SG_EXPORT Point : public StateAttribute
{
    public :

        Point();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Point(const Point& point,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(point,copyop),
            _size(point._size),
            _fadeThresholdSize(point._fadeThresholdSize),
            _distanceAttenuation(point._distanceAttenuation) {}

        META_StateAttribute(osg, Point, POINT);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Point,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_size)
            COMPARE_StateAttribute_Parameter(_fadeThresholdSize)
            COMPARE_StateAttribute_Parameter(_distanceAttenuation)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_POINT_SMOOTH);
        }

        void setSize(const float size);
        inline const float getSize() const { return _size; }

        void setFadeThresholdSize(const float fadeThresholdSize);
        inline const float getFadeThresholdSize() const { return _fadeThresholdSize; }

        void setDistanceAttenuation(const Vec3& distanceAttenuation);
        inline const Vec3& getDistanceAttenuation() const { return _distanceAttenuation; }

        virtual void apply(State& state) const;

        static void init_GL_EXT();

    protected :

        virtual ~Point();

        float       _size;
        float       _fadeThresholdSize;
        Vec3        _distanceAttenuation;

};

}

#endif
