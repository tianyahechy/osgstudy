//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_VEC2
#define OSG_VEC2 1

#include <osg/Math.h>

#include <iostream>

namespace osg {

/** General purpose float pair, uses include representation of
    texture coordinates.
    No support yet added for float * Vec2 - is it necessary?
    Need to define a non-member non-friend operator*  etc.
    BTW:	     Vec2 * float is okay
*/

class Vec2
{
    public:

        Vec2() {_v[0]=0.0f; _v[1]=0.0f;}
        Vec2(float x,float y) { _v[0]=x; _v[1]=y; }

        float _v[2];

        inline const bool operator == (const Vec2& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1]; }

        inline const bool operator != (const Vec2& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1]; }

	inline const bool operator <  (const Vec2& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else return (_v[1]<v._v[1]);
        }

        inline float* ptr() { return _v; }
        inline const float* ptr() const { return _v; }

        inline void set( float x, float y ) { _v[0]=x; _v[1]=y; }

        inline float& operator [] (int i) { return _v[i]; }
        inline const float operator [] (int i) const { return _v[i]; }

        inline float& x() { return _v[0]; }
        inline float& y() { return _v[1]; }

        inline const float x() const { return _v[0]; }
        inline const float y() const { return _v[1]; }

        inline const bool valid() const { return !isNaN(); }
        inline const bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]); }

        /// dot product
        inline const float operator * (const Vec2& rhs) const
        {
            return _v[0]*rhs._v[0]+_v[1]*rhs._v[1];
        }

        /// multiply by scalar
        inline const Vec2 operator * (const float& rhs) const
        {
            return Vec2(_v[0]*rhs, _v[1]*rhs);
        }

        /// unary multiply by scalar
        inline Vec2& operator *= (const float& rhs)
        {
            _v[0]*=rhs;
	    _v[1]*=rhs;
	    return *this;
        }

        /// divide by scalar
        inline const Vec2 operator / (const float& rhs) const
        {
            return Vec2(_v[0]/rhs, _v[1]/rhs);
        }

        /// unary divide by scalar
        inline Vec2& operator /= (const float& rhs)
        {
            _v[0]/=rhs;
	    _v[1]/=rhs;
	    return *this;
        }

        /// binary vector add
        inline const Vec2 operator + (const Vec2& rhs) const
        {
            return Vec2(_v[0]+rhs._v[0], _v[1]+rhs._v[1]);
        }

        /** unary vector add.  Slightly more efficient because no temporary
            intermediate object.*/
        inline Vec2& operator += (const Vec2& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
	    return *this;
        }

        /// binary vector subtract
        inline const Vec2 operator - (const Vec2& rhs) const
        {
            return Vec2(_v[0]-rhs._v[0], _v[1]-rhs._v[1]);
        }

        /// unary vector subtract
        inline Vec2& operator -= (const Vec2& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
	    return *this;
	}

        /// negation operator.  Returns the negative of the Vec2
        inline const Vec2 operator - () const
        {
	    return Vec2 (-_v[0], -_v[1]);
	}

        /// Length of the vector = sqrt( vec . vec )
	inline const float length() const
	{
	    return sqrtf( _v[0]*_v[0] + _v[1]*_v[1] );
	}

        /// Length squared of the vector = vec . vec
        inline const float length2( void ) const
        {
            return _v[0]*_v[0] + _v[1]*_v[1];
        }

        /** normalize the vector so that it has length unity
            returns the previous length of the vector*/
	inline const float normalize()
	{
	    float norm = Vec2::length();
	    _v[0] /= norm;
	    _v[1] /= norm;
	    return( norm );
	}

	friend inline std::ostream& operator << (std::ostream& output, const Vec2& vec)
        {
	    output << vec._v[0] << " "
                   << vec._v[1];
	    return output; 	// to enable cascading
	}

};	// end of class Vec2

}	// end of namespace osg
#endif
