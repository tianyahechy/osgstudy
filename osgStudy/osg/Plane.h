//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_PLANE
#define OSG_PLANE 1

#include <osg/Export.h>
#include <osg/Vec3.h>
#include <osg/Vec4.h>
#include <osg/Matrix.h>
#include <osg/BoundingSphere.h>
#include <osg/BoundingBox.h>

#include <vector>

namespace osg {

/** A plane class. It can be used to represent an infinite plane.*/
class SG_EXPORT Plane
{

    public:

	inline Plane():_fv(0.0f,0.0f,0.0f,0.0f) { _lowerBBCorner = 0; _upperBBCorner = 0; }
	inline Plane(const Plane& pl):_fv(pl._fv) { calculateUpperLowerBBCorners(); }
	inline Plane(const float a,const  float b,const float c,const float d):_fv(a,b,c,d) { calculateUpperLowerBBCorners(); }
	inline Plane(const Vec4& vec):_fv(vec) { calculateUpperLowerBBCorners(); }
	inline Plane(const Vec3& norm,const float d):_fv(norm[0],norm[1],norm[2],d) { calculateUpperLowerBBCorners(); }
        inline Plane(const Vec3& v1, const Vec3& v2, const Vec3& v3) { set(v1,v2,v3); calculateUpperLowerBBCorners(); }
        
        inline Plane& operator = (const Plane& pl)
        {
            if (&pl==this) return *this;
            _fv = pl._fv;
            _lowerBBCorner = pl._lowerBBCorner;
            _upperBBCorner = pl._upperBBCorner;
            return *this;
        }

	inline void set(const Plane& pl) { _fv = pl._fv; calculateUpperLowerBBCorners(); }
	inline void set(const float a,const  float b,const float c,const float d) { _fv.set(a,b,c,d); calculateUpperLowerBBCorners(); }
	inline void set(const Vec4& vec) { _fv = vec; calculateUpperLowerBBCorners(); }
	inline void set(const Vec3& norm,const float d) { _fv.set(norm[0],norm[1],norm[2],d); calculateUpperLowerBBCorners(); }
        inline void set(const Vec3& v1, const Vec3& v2, const Vec3& v3)
        {
            osg::Vec3 norm = (v2-v1)^(v3-v2);
            float length = norm.length();
            if (length>1e-6) norm/= length;
            else norm.set(0.0f,0.0f,0.0f);
            _fv.set(norm[0],norm[1],norm[2],-(v1*norm));
            calculateUpperLowerBBCorners();
        }
        
        /** flip/reverse the orientation of the plane.*/
        inline void flip()
        {
            _fv = -_fv;
            calculateUpperLowerBBCorners();
        }


        inline void makeUnitLength()
        {
            float length = sqrtf(_fv[0]*_fv[0] + _fv[1]*_fv[1]+ _fv[2]*_fv[2]);
            _fv /= length;
        }

        /** calculate the upper and lower bounding box corners to be used
          * in the intersect(BoundingBox&) method for speeding calculations.*/
        inline void calculateUpperLowerBBCorners()
        {
            _upperBBCorner = (_fv.x()>=0.0f?1:0) |
                             (_fv.y()>=0.0f?2:0) |
                             (_fv.z()>=0.0f?4:0);

            _lowerBBCorner = (~_upperBBCorner)&7;

        }

        inline const bool valid() const { return _fv[0]==0.0f && _fv[1]==0.0f && _fv[2]==0.0f; }

	inline Vec4& asVec4() { return _fv; }

	inline const Vec4& asVec4() const { return _fv; }
        
        inline float& operator [] (const int i) { return _fv[i]; }
        inline float  operator [] (const int i) const { return _fv[i]; }
        
        
        inline osg::Vec3 getNormal() { return osg::Vec3(_fv[0],_fv[1],_fv[2]); }
      
              /** calculate the distance between a point and the plane.*/
        inline const float distance(const osg::Vec3& v) const
        {
            return _fv[0]*v.x()+
                   _fv[1]*v.y()+
                   _fv[2]*v.z()+
                   _fv[3];
        }

        /** intersection test between plane and vertex list
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline const int intersect(const std::vector<Vec3>& vertices) const
        {
            if (vertices.empty()) return -1;
        
            int noAbove = 0;
            int noBelow = 0;
            int noOn = 0;
            for(std::vector<Vec3>::const_iterator itr=vertices.begin();
                itr != vertices.end();
                ++itr)
            {
                float d = distance(*itr);
                if (d>0.0f) ++noAbove;
                else if (d<0.0f) ++noBelow;
                else ++noOn;
            }
            
            if (noAbove>0)
            {
                if (noBelow>0) return 0;
                else return 1;
            }
            return -1; // treat points on line as outside...
        }

        /** intersection test between plane and bounding sphere.
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline const int intersect(const BoundingSphere& bs) const
        {
            float d = distance(bs.center());
                      
            if (d>bs.radius()) return 1;
            else if (d<-bs.radius()) return -1;
            else return 0;
        }
        
        
        /** intersection test between plane and bounding sphere.
            return 1 if the bs is completely above plane,
            return 0 if the bs intersects the plane,
            return -1 if the bs is completely below the plane.*/
        inline const int intersect(const BoundingBox& bb) const
        {
             // if lowest point above plane than all above.
            if (distance(bb.corner(_lowerBBCorner))>0.0f) return 1;
            
            // if highest point is below plane then all below.
            if (distance(bb.corner(_upperBBCorner))<0.0f) return -1;
            
            // d_lower<=0.0f && d_upper>=0.0f
            // therefore must be crossing plane.
            return 0;
            
        }

        /** Transform the plane by matrix.  Note, this operations carries out
          * the calculation of the inverse of the matrix since to transforms
          * planes must be multiplied my the inverse transposed. This
          * make this operation expensive.  If the inverse has been already
          * calculated elsewhere then use transformProvidingInverse() instead.
          * See http://www.worldserver.com/turk/computergraphics/NormalTransformations.pdf*/
        inline void transform(const osg::Matrix& matrix)
        {
            osg::Matrix inverse;
            inverse.invert(matrix);
            transformProvidingInverse(inverse);
        }
        
        /** Transform the plane by provide a pre inverted matrix.
          * see transform for details. */
        inline void transformProvidingInverse(const osg::Matrix& matrix)
        {
            // note pre multiplications, which effectively transposes matrix.
            _fv = matrix * _fv;
            makeUnitLength();
            calculateUpperLowerBBCorners();
        }

        friend inline std::ostream& operator << (std::ostream& output, const Plane& pl);


    protected:

	Vec4                _fv;
        
        // variables cached to optimize calcs against bounding boxes.
        unsigned int        _upperBBCorner;
        unsigned int        _lowerBBCorner;


};

inline std::ostream& operator << (std::ostream& output, const Plane& pl)
{
    output << pl._fv[0] << " "
	   << pl._fv[1] << " "
	   << pl._fv[2] << " "
	   << pl._fv[3];
    return output; 	// to enable cascading
}

}	// end of namespace

#endif 
