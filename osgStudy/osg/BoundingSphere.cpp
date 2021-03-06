#include <osg/BoundingSphere.h>
#include <osg/BoundingBox.h>

using namespace osg;

void BoundingSphere::expandBy(const Vec3& v)
{
    if (valid())
    {
        Vec3 dv = v-_center;
        float r = dv.length();
        if (r>_radius)
        {
            float dr = (r-_radius)*0.5f;
            _center += dv*(dr/r);
            _radius += dr;
        } // else do nothing as vertex is within sphere.
    }
    else
    {
        _center = v;
        _radius = 0.0f;
    }
}


void BoundingSphere::expandRadiusBy(const Vec3& v)
{
    if (valid())
    {
        float r = (v-_center).length();
        if (r>_radius) _radius = r;
        // else do nothing as vertex is within sphere.
    }
    else
    {
        _center = v;
        _radius = 0.0f;
    }
}


void BoundingSphere::expandBy(const BoundingSphere& sh)
{
    if (sh.valid())
    {
        if (valid())
        {
            Vec3 dv = sh._center-_center;
            float dv_len = dv.length();
            if (dv_len+sh._radius>_radius)
            {
                Vec3 e1 = _center-(dv*(_radius/dv_len));
                Vec3 e2 = sh._center+(dv*(sh._radius/dv_len));
                _center = (e1+e2)*0.5f;
                _radius = (e2-_center).length();

            }                    // else do nothing as vertex is within sphere.
        }
        else
        {
            _center = sh._center;
            _radius = sh._radius;
        }
    }
}


void BoundingSphere::expandRadiusBy(const BoundingSphere& sh)
{
    if (sh.valid())
    {
        if (valid())
        {
            float r = (sh._center-_center).length()+sh._radius;
            if (r>_radius) _radius = r;
            // else do nothing as vertex is within sphere.
        }
        else
        {
            _center = sh._center;
            _radius = sh._radius;
        }
    }
}

void BoundingSphere::expandBy(const BoundingBox& bb)
{
    if (bb.valid())
    {
        if (valid())
        {
            BoundingBox newbb(bb);

            for(unsigned int c=0;c<8;++c)
            {
                Vec3 v = bb.corner(c)-_center; // get the direction vector from corner
                v.normalize(); // normalise it.
                v *= -_radius; // move the vector in the opposite direction distance radius.
                v += _center; // move to absolute position.
                newbb.expandBy(v); // add it into the new bounding box.
            }
            
            _center = newbb.center();
            _radius = newbb.radius();
            
        }
        else
        {
            _center = bb.center();
            _radius = bb.radius();
        }
    }
}

void BoundingSphere::expandRadiusBy(const BoundingBox& bb)
{
    if (bb.valid())
    {
        if (valid())
        {
            for(unsigned int c=0;c<8;++c)
            {
                expandRadiusBy(bb.corner(c));
            }
        }
        else
        {
            _center = bb.center();
            _radius = bb.radius();
        }
    }
}
