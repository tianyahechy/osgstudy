//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_LINESEGMENT
#define OSG_LINESEGMENT 1

#include <osg/Matrix.h>
#include <osg/BoundingBox.h>
#include <osg/BoundingSphere.h>

namespace osg {

/** LineSegment class for representing a line segment.*/
class SG_EXPORT LineSegment : public Referenced
{
    public:

        LineSegment() {};
        LineSegment(const LineSegment& seg) : Referenced(),_s(seg._s),_e(seg._e) {}
        LineSegment(const Vec3& s,const Vec3& e) : _s(s),_e(e) {}

        LineSegment& operator = (const LineSegment& seg) { _s = seg._s;  _e = seg._e; return *this; }

        inline void set(const Vec3& s,const Vec3& e) { _s=s; _e=e; }
        
        inline Vec3& start() { return _s; }
        inline const Vec3& start() const { return _s; }

        inline Vec3& end() { return _e; }
        inline const Vec3& end() const { return _e; }

        inline const bool valid() const { return _s.valid() && _e.valid() && _s!=_e; }

        /** return true if segment intersects BoundingBox.*/
        const bool intersect(const BoundingBox& bb) const;

        /** return true if segment intersects BoundingBox and return the intersection ratio's.*/
        const bool intersect(const BoundingBox& bb,float& r1,float& r2) const;

        /** return true if segment intersects BoundingSphere.*/
        const bool intersect(const BoundingSphere& bs) const;

        /** return true if segment intersects BoundingSphere and return the intersection ratio's.*/
        const bool intersect(const BoundingSphere& bs,float& r1,float& r2) const;
        
        /** return true if segment intersects triangle and set ratio long segment. */
        const bool intersect(const Vec3& v1,const Vec3& v2,const Vec3& v3,float& r);

        /** post multiply a segment by matrix.*/
        inline void mult(const LineSegment& seg,const Matrix& m) { _s = seg._s*m; _e = seg._e*m; }
        /** pre multiply a segment by matrix.*/
        inline void mult(const Matrix& m,const LineSegment& seg) { _s = m*seg._s; _e = m*seg._e; }

    protected:

        virtual ~LineSegment() {}
        
        static const bool intersectAndClip(Vec3& s,Vec3& e,const BoundingBox& bb);

        Vec3 _s;
        Vec3 _e;
};

}

#endif
