//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_BOUNDINGBOX
#define OSG_BOUNDINGBOX 1

#include <osg/Export.h>
#include <osg/Vec3.h>
#include <float.h.h>

namespace osg {

class BoundingSphere;

/** General purpose axis-aligned bounding box class for enclosing objects/vertices.
    Used to bounding the leaf objects in the scene,
    i.e. osg::Drawable's to assist in view frustum culling etc.
*/
class SG_EXPORT BoundingBox
{
    public:
    
	/** The corner with the smallest values for each coordinate of the
	    bounding box.*/
	Vec3 _min;
	/** The corner with the largest values for each coordinate of the
	    bounding box.*/
	Vec3 _max;

        /** construct to invalid values to represent an unset bounding box.*/ 
        inline BoundingBox() : _min(FLT_MAX,FLT_MAX,FLT_MAX),
                        _max(-FLT_MAX,-FLT_MAX,-FLT_MAX) {}
    
        /** construct to with specified min and max values.*/ 
        inline BoundingBox(float xmin,float ymin,float zmin,
                    float xmax,float ymax,float zmax) :
                    _min(xmin,ymin,zmin),
                    _max(xmax,ymax,zmax) {}

        /** construct to with specified min and max values.*/ 
        inline BoundingBox(const Vec3& min,const Vec3& max) : 
                    _min(min),
                    _max(max) {}

        /** initialize to invalid values to represent an unset bounding box.*/ 
        inline void init()
        {
            _min.set(FLT_MAX,FLT_MAX,FLT_MAX);
            _max.set(-FLT_MAX,-FLT_MAX,-FLT_MAX);
        }
        
#ifdef USE_DEPRECATED_API
        /** deprecated, use valid() instead.*/
        inline const bool isValid() const { return _max.x()>=_min.x(); }
#endif
                
        inline const bool valid() const
        {
            return _max.x()>=_min.x();
        }

        inline void set (float xmin,float ymin,float zmin,
                         float xmax,float ymax,float zmax)
        {
            _min.set(xmin,ymin,zmin);
            _max.set(xmax,ymax,zmax);
        }

        /** construct to with specified min and max values.*/ 
        inline void set(const Vec3& min,const Vec3& max)
        {
            _min = min;
            _max = max;
        }


        inline float& xMin() { return _min.x(); }
        inline const float xMin() const { return _min.x(); }
 
        inline float& yMin() { return _min.y(); }
        inline const float yMin() const { return _min.y(); }
 
        inline float& zMin() { return _min.z(); }
        inline const float zMin() const { return _min.z(); }

        inline float& xMax() { return _max.x(); }
        inline const float xMax() const { return _max.x(); }
 
        inline float& yMax() { return _max.y(); }
        inline const float yMax() const { return _max.y(); }
 
        inline float& zMax() { return _max.z(); }
        inline const float zMax() const { return _max.z(); }

        /** Calculate and return the center of the bounding box.*/
        inline const Vec3 center() const
        {
            return (_min+_max)*0.5f;
        }

        /** Calculate and return the radius of the bounding box.*/
        inline const float radius() const
        {
            return sqrtf(radius2());
        }

        /** Calculate and return the radius squared of the bounding box.
            Note, radius2() is faster to calculate than radius().*/            
        inline const float radius2() const
        {
            return 0.25f*((_max-_min).length2());
        }

        /** return the corner of the bounding box.
            Position (pos) is specified by a number between 0 and 7,
            the first bit toggles between x min and x max, second
            bit toggles between y min and y max, third bit toggles
            between z min and z max.*/
        inline const Vec3 corner(unsigned int pos) const
        {
            return Vec3(pos&1?_max.x():_min.x(),pos&2?_max.y():_min.y(),pos&4?_max.z():_min.z());
        }

        /** If the vertex is out-with the box expand to encompass vertex.
            If this box is empty then move set this box's min max to vertex. */
        inline void expandBy(const Vec3& v)
        {
            if(v.x()<_min.x()) _min.x() = v.x();
            if(v.x()>_max.x()) _max.x() = v.x();

            if(v.y()<_min.y()) _min.y() = v.y();
            if(v.y()>_max.y()) _max.y() = v.y();

            if(v.z()<_min.z()) _min.z() = v.z();
            if(v.z()>_max.z()) _max.z() = v.z();
        }

        /** If the vertex is out-with the box expand to encompass vertex.
            If this box is empty then move set this box's min max to vertex. */
        inline void expandBy(float x,float y,float z)
        {
            if(x<_min.x()) _min.x() = x;
            if(x>_max.x()) _max.x() = x;

            if(y<_min.y()) _min.y() = y;
            if(y>_max.y()) _max.y() = y;

            if(z<_min.z()) _min.z() = z;
            if(z>_max.z()) _max.z() = z;
        }

        /** If incoming box is out-with the box expand to encompass incoming box.
            If this box is empty then move set this box to incoming box. */
        void expandBy(const BoundingBox& bb);

        /** If incoming sphere is out-with the box expand to encompass incoming sphere.
            If this box is empty then move set this box to encompass the sphere. */
        void expandBy(const BoundingSphere& sh);

        /** return true is vertex v is within the box.*/
        inline const bool contains(const Vec3& v) const
        {
            return valid() && 
                   (v.x()>=_min.x() && v.x()<=_max.x()) &&
                   (v.y()>=_min.y() && v.y()<=_max.y()) &&
                   (v.z()>=_min.z() && v.z()<=_max.z());
        }
};

}

#endif
