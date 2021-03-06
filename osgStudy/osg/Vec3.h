//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_VEC3
#define OSG_VEC3 1

#include <osg/Math.h>

#include <iostream>

namespace osg {

/** General purpose float triple for use as vertices, vectors and normals.
    Provides general maths operations from addition through to cross products.
    No support yet added for float * Vec3 - is it necessary?
    Need to define a non-member non-friend operator*  etc.
   			     Vec3 * float is okay
*/
class Vec3
{
    public:

        Vec3() { _v[0]=0.0f; _v[1]=0.0f; _v[2]=0.0f;}
        Vec3(float x,float y,float z) { _v[0]=x; _v[1]=y; _v[2]=z; }

        float _v[3];

	inline const bool operator == (const Vec3& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2]; }
        
        inline const bool operator != (const Vec3& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2]; }

	inline const bool operator <  (const Vec3& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else return (_v[2]<v._v[2]);
        }

        inline float* ptr() { return _v; }
        inline const float* ptr() const { return _v; }

        inline void set( float x, float y, float z)
        {
            _v[0]=x; _v[1]=y; _v[2]=z;
        }

        inline float& operator [] (int i) { return _v[i]; }
        inline const float operator [] (int i) const { return _v[i]; }

        inline float& x() { return _v[0]; }
        inline float& y() { return _v[1]; }
        inline float& z() { return _v[2]; }

        inline const float x() const { return _v[0]; }
        inline const float y() const { return _v[1]; }
        inline const float z() const { return _v[2]; }

        inline const bool valid() const { return !isNaN(); }
        inline const bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]) || osg::isNaN(_v[2]); }

        /// dot product
        inline float operator * (const Vec3& rhs) const
        {
            return _v[0]*rhs._v[0]+_v[1]*rhs._v[1]+_v[2]*rhs._v[2];
        }

        /// cross product
        inline const Vec3 operator ^ (const Vec3& rhs) const
        {
            return Vec3(_v[1]*rhs._v[2]-_v[2]*rhs._v[1],
                _v[2]*rhs._v[0]-_v[0]*rhs._v[2] ,
                _v[0]*rhs._v[1]-_v[1]*rhs._v[0]);
        }

        /// multiply by scalar
        inline const Vec3 operator * (const float& rhs) const
        {
            return Vec3(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs);
        }

        /// unary multiply by scalar
        inline Vec3& operator *= (const float& rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            return *this;
        }

        /// divide by scalar
        inline const Vec3 operator / (const float& rhs) const
        {
            return Vec3(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs);
        }

        /// unary divide by scalar
        inline Vec3& operator /= (const float& rhs)
        {
            _v[0]/=rhs;
            _v[1]/=rhs;
            _v[2]/=rhs;
            return *this;
        }

        /// binary vector add
        inline const Vec3 operator + (const Vec3& rhs) const
        {
            return Vec3(_v[0]+rhs._v[0], _v[1]+rhs._v[1], _v[2]+rhs._v[2]);
        }

        /** unary vector add.  Slightly more efficient because no temporary
            intermediate object*/
        inline Vec3& operator += (const Vec3& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            return *this;
        }

        /// binary vector subtract
        inline const Vec3 operator - (const Vec3& rhs) const
        {
            return Vec3(_v[0]-rhs._v[0], _v[1]-rhs._v[1], _v[2]-rhs._v[2]);
        }

        /// unary vector subtract
        inline Vec3& operator -= (const Vec3& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            return *this;
        }

        /// negation operator.  Returns the negative of the Vec3
        inline const Vec3 operator - () const
        {
            return Vec3 (-_v[0], -_v[1], -_v[2]);
        }

        /// Length of the vector = sqrt( vec . vec )
        inline const float length() const
        {
            return sqrtf( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] );
        }

        /// Length squared of the vector = vec . vec
        inline const float length2() const
        {
            return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2];
        }

        /** normalize the vector so that it has length unity
            returns the previous length of the vector*/
        inline const float normalize()
        {
            float norm = Vec3::length();
            if (norm>0.0f)
            {
                _v[0] /= norm;
                _v[1] /= norm;
                _v[2] /= norm;
            }                
            return( norm );
        }

	friend inline std::ostream& operator << (std::ostream& output, const Vec3& vec);

};	// end of class Vec3

inline std::ostream& operator << (std::ostream& output, const Vec3& vec)
{
    output << vec._v[0] << " "
           << vec._v[1] << " "
           << vec._v[2];
    return output; 	// to enable cascading
}

}	// end of namespace osg

#endif
