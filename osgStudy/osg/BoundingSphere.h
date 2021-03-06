//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_BOUNDINGSPHERE
#define OSG_BOUNDINGSPHERE 1

#include <osg/Export.h>
#include <osg/Vec3.h>

namespace osg {

class BoundingBox;

/** General purpose bounding sphere class for enclosing nodes/objects/vertices.
    Used to bound internal osg::Node's in the scene,
    to assist in view frustum culling etc.  Similar in function to BoundingBox
    but is quicker for evaluating culling, but generally encloses a greater volume
    than a BoundingBox so will not cull so aggressively.
*/
class SG_EXPORT BoundingSphere
{
    public:
        
        Vec3 _center;
        float _radius;

        /** construct to invalid values to represent an unset bounding sphere.*/ 
        BoundingSphere() : _center(0.0f,0.0f,0.0f),_radius(-1.0f) {}
    
        /** construct to specified bounding sphere.*/ 
        BoundingSphere(const Vec3& center,float radius) : _center(center),_radius(radius) {}

        /** initialize to invalid values to represent an unset bounding sphere.*/ 
        inline void init()
        {
            _center.set(0.0f,0.0f,0.0f);
            _radius = -1.0f;
        }

#ifdef USE_DEPRECATED_API
        /** deprecated, use valid() instead.*/
        inline const bool isValid() const { return _radius>=0.0f; }
#endif
        /** return true if the bounding sphere contains valid values,
            false if the bounding sphere is effectively unset.*/
        inline const bool valid() const { return _radius>=0.0f; }

        /** set bounding sphere.*/ 
        inline void set(const Vec3& center,float radius)
        {
            _center = center;
            _radius = radius;
        }

        /** return the center of the bounding sphere.*/
        inline Vec3& center() { return _center; }
        /** return the const center of the bounding sphere.*/
        inline const Vec3& center() const { return _center; }

        /** return the radius of the bounding sphere.*/
        inline float& radius() { return _radius; }

        /** return the const radius of the bounding sphere.*/
        inline const float radius() const { return _radius; }
        
        /** return the radius squared. 
            Note, for performance reasons, assumes the calling method has ensured 
            that the sphere is valid before calling radius2(), i.e. has _radius>=0.0,
            as it does not check th validity of sphere and will erroneously return a positive value.*/
        inline const float radius2() const { return _radius*_radius; }
        
        /** If the vertex is out-with the sphere expand to encompass vertex.
            Calculates the combination of movement of center and radius which
            minimizes the radius increase. If this sphere is empty then
            move the center to v and set radius to 0.*/
        void expandBy(const Vec3& v);

        /** If the vertex is outwith the sphere expand radius to ecompass vertex.
            Unlike update, does not move the center, just increasing the radius.
            If this sphere is empty then move the centrer to v and set radius to 0 */
        void expandRadiusBy(const Vec3& v);

        /** If incomming sphere is outwith the sphere expand to ecompass incomming sphere.
            calculates the combination of movement of center and radius which
            minimizes the radius increase. If this sphere is empty then
            move the centrer to v and set radius to 0.*/
        void expandBy(const BoundingSphere& sh);

        /** If incomming sphere is outwith the sphere expand radius to ecompass incomming sphere.
            Unlike update, does not move the center, just increasing the radius.
            If this sphere is empty then move the centrer to v and set radius to 0. */
        void expandRadiusBy(const BoundingSphere& sh);

        /** If incomming box is outwith the sphere expand to ecompass incomming box.
            calculates the combination of movement of center and radius which
            minimizes the radius increase. If this boz is empty then
            move the centrer to v and set radius to 0.*/
        void expandBy(const BoundingBox& bb);

        /** If incomming box is outwith the sphere expand radius to ecompass incomming box.
            Unlike update, does not move the center, just increasing the radius.
            If this sphere is empty then move the centrer to v and set radius to 0. */
        void expandRadiusBy(const BoundingBox& bb);

        /** return true is vertex v is within the sphere.*/
        inline const bool contains(const Vec3& v) const
        {
            return valid() && ((v-_center).length2()<=radius2());
        }

        /** return true if bounding sphere's intersect each other.*/
        inline const bool intersects( const BoundingSphere& bs ) const
        {
            return valid() && bs.valid() &&
                   ((_center - bs._center).length2() <= (_radius + bs._radius)*(_radius + bs._radius));
        }

};

}

#endif
