//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_VEC4
#define OSG_VEC4 1

#include <osg/Vec3.h>

#include <iostream>

namespace osg {

/** General purpose float quad, uses include representation
    of colour coordinates.
    No support yet added for float * Vec4 - is it necessary?
    Need to define a non-member non-friend operator*  etc.
   			     Vec4 * float is okay
*/
class Vec4
{
    public:

	// Methods are defined here so that they are implicitly inlined

        Vec4() { _v[0]=0.0f; _v[1]=0.0f; _v[2]=0.0f; _v[3]=0.0f;}
        
        Vec4(float x, float y, float z, float w)
        {
            _v[0]=x;
            _v[1]=y;
            _v[2]=z;
            _v[3]=w;
        }

        Vec4(const Vec3& v3,float w)
        {
            _v[0]=v3[0];
            _v[1]=v3[1];
            _v[2]=v3[2];
            _v[3]=w;
        }
            

        float _v[4];

        inline const bool operator == (const Vec4& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2] && _v[3]==v._v[3]; }

        inline const bool operator != (const Vec4& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2] || _v[3]!=v._v[3]; }

        inline const bool operator <  (const Vec4& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        inline float* ptr() { return _v; }
        inline const float* ptr() const { return _v; }

        inline void set( float x, float y, float z, float w)
        {
            _v[0]=x; _v[1]=y; _v[2]=z; _v[3]=w;
        }

        inline float& operator [] (const int i) { return _v[i]; }
        inline float  operator [] (const int i) const { return _v[i]; }

        inline float& x() { return _v[0]; }
        inline float& y() { return _v[1]; }
        inline float& z() { return _v[2]; }
        inline float& w() { return _v[3]; }

        inline float x() const { return _v[0]; }
        inline float y() const { return _v[1]; }
        inline float z() const { return _v[2]; }
        inline float w() const { return _v[3]; }

        inline unsigned long asABGR() const
        {
            return (unsigned long)clampTo((_v[0]*255.0f),0.0f,255.0f)<<24 |
                   (unsigned long)clampTo((_v[1]*255.0f),0.0f,255.0f)<<16 |
                   (unsigned long)clampTo((_v[2]*255.0f),0.0f,255.0f)<<8  |
                   (unsigned long)clampTo((_v[3]*255.0f),0.0f,255.0f);
        }

        inline const unsigned long asRGBA() const
        {
            return (unsigned long)clampTo((_v[3]*255.0f),0.0f,255.0f)<<24 |
                   (unsigned long)clampTo((_v[2]*255.0f),0.0f,255.0f)<<16 |
                   (unsigned long)clampTo((_v[1]*255.0f),0.0f,255.0f)<<8  |
                   (unsigned long)clampTo((_v[0]*255.0f),0.0f,255.0f);
        }

        inline const bool valid() const { return !isNaN(); }
        inline const bool isNaN() const { return osg::isNaN(_v[0]) || osg::isNaN(_v[1]) || osg::isNaN(_v[2]) || osg::isNaN(_v[3]); }

        /// dot product
        inline float operator * (const Vec4& rhs) const
        {
            return _v[0]*rhs._v[0]+
	           _v[1]*rhs._v[1]+
	           _v[2]*rhs._v[2]+
	           _v[3]*rhs._v[3] ;
        }

        /// multiply by scalar
        inline Vec4 operator * (const float rhs) const
        {
            return Vec4(_v[0]*rhs, _v[1]*rhs, _v[2]*rhs, _v[3]*rhs);
        }

        /// unary multiply by scalar
        inline Vec4& operator *= (const float rhs)
        {
            _v[0]*=rhs;
            _v[1]*=rhs;
            _v[2]*=rhs;
            _v[3]*=rhs;
            return *this;
        }

        /// divide by scalar
        inline Vec4 operator / (const float rhs) const
        {
            return Vec4(_v[0]/rhs, _v[1]/rhs, _v[2]/rhs, _v[3]/rhs);
        }

        /// unary divide by scalar
        inline Vec4& operator /= (const float rhs)
        {
            _v[0]/=rhs;
            _v[1]/=rhs;
            _v[2]/=rhs;
            _v[3]/=rhs;
            return *this;
        }

        /// binary vector add
        inline Vec4 operator + (const Vec4& rhs) const
        {
            return Vec4(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
		        _v[2]+rhs._v[2], _v[3]+rhs._v[3]);
        }

        /** unary vector add.  Slightly more efficient because no temporary
            intermediate object*/
        inline Vec4& operator += (const Vec4& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;
        }

        /// binary vector subtract
        inline Vec4 operator - (const Vec4& rhs) const
        {
            return Vec4(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
		        _v[2]-rhs._v[2], _v[3]-rhs._v[3] );
        }

        /// unary vector subtract
        inline Vec4& operator -= (const Vec4& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            _v[3]-=rhs._v[3];
            return *this;
        }

        /// negation operator.  Returns the negative of the Vec4
        inline const Vec4 operator - () const
        {
            return Vec4 (-_v[0], -_v[1], -_v[2], -_v[3]);
        }

        /// Length of the vector = sqrt( vec . vec )
        inline const float length() const
        {
            return sqrtf( _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3]);
        }

        /// Length squared of the vector = vec . vec
        inline const float length2() const
        {
            return _v[0]*_v[0] + _v[1]*_v[1] + _v[2]*_v[2] + _v[3]*_v[3];
        }

        /** normalize the vector so that it has length unity
            returns the previous length of the vector*/
        inline const float normalize()
        {
            float norm = Vec4::length();
            _v[0] /= norm;
            _v[1] /= norm;
            _v[2] /= norm;
            _v[3] /= norm;
            return( norm );
        }

        friend inline std::ostream& operator << (std::ostream& output, const Vec4& vec)
        {
	    output << vec._v[0] << " "
                   << vec._v[1] << " "
                   << vec._v[2] << " "
                   << vec._v[3];
	    return output; 	// to enable cascading
	}

};	// end of class Vec4


/** Compute the dot product of a (Vec3,1.0) and a Vec4.*/
inline float operator * (const Vec3& lhs,const Vec4& rhs)
{
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+rhs[3];
}

/** Compute the dot product of a Vec4 and a (Vec3,1.0).*/
inline float operator * (const Vec4& lhs,const Vec3& rhs)
{
    return lhs[0]*rhs[0]+lhs[1]*rhs[1]+lhs[2]*rhs[2]+lhs[3];
}

}	// end of namespace osg

#endif
