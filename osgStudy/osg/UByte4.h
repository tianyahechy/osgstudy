//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_UBYTE4
#define OSG_UBUTE 1

#include <osg/Vec3.h>

#include <iostream>

namespace osg {

/** General purpose float quad, uses include representation
    of colour coordinates.
    No support yet added for float * UByte4 - is it necessary?
    Need to define a non-member non-friend operator*  etc.
   			     UByte4 * float is okay
*/
class UByte4
{
    public:

	// Methods are defined here so that they are implicitly inlined

        UByte4() { _v[0]=0; _v[1]=0; _v[2]=0; _v[3]=0;}
        
        UByte4(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            _v[0]=r; _v[1]=g; _v[2]=b; _v[3]=a;
        }

        unsigned char _v[4];

        inline const bool operator == (const UByte4& v) const { return _v[0]==v._v[0] && _v[1]==v._v[1] && _v[2]==v._v[2] && _v[3]==v._v[3]; }

        inline const bool operator != (const UByte4& v) const { return _v[0]!=v._v[0] || _v[1]!=v._v[1] || _v[2]!=v._v[2] || _v[3]!=v._v[3]; }

        inline const bool operator <  (const UByte4& v) const
        {
            if (_v[0]<v._v[0]) return true;
            else if (_v[0]>v._v[0]) return false;
            else if (_v[1]<v._v[1]) return true;
            else if (_v[1]>v._v[1]) return false;
            else if (_v[2]<v._v[2]) return true;
            else if (_v[2]>v._v[2]) return false;
            else return (_v[3]<v._v[3]);
        }

        inline unsigned char* ptr() { return _v; }
        inline const unsigned char* ptr() const { return _v; }

        inline void set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
        {
            _v[0]=r; _v[1]=g; _v[2]=b; _v[3]=a;
        }

        inline unsigned char& operator [] (const int i) { return _v[i]; }
        inline unsigned char operator [] (const int i) const { return _v[i]; }

        inline unsigned char& r() { return _v[0]; }
        inline unsigned char& g() { return _v[1]; }
        inline unsigned char& b() { return _v[2]; }
        inline unsigned char& a() { return _v[3]; }

        inline unsigned char r() const { return _v[0]; }
        inline unsigned char g() const { return _v[1]; }
        inline unsigned char b() const { return _v[2]; }
        inline unsigned char a() const { return _v[3]; }

        /// multiply by scalar
        inline UByte4 operator * (const float rhs) const
        {
            UByte4 col(*this);
            col *= rhs;
            return col;
        }

        /// unary multiply by scalar
        inline UByte4& operator *= (const float rhs)
        {
            _v[0]=(unsigned char)((float)_v[0]*rhs);
            _v[1]=(unsigned char)((float)_v[1]*rhs);
            _v[2]=(unsigned char)((float)_v[2]*rhs);
            _v[3]=(unsigned char)((float)_v[3]*rhs);
            return *this;
        }

        /// divide by scalar
        inline UByte4 operator / (const float rhs) const
        {
            UByte4 col(*this);
            col /= rhs;
            return col;
        }

        /// unary divide by scalar
        inline UByte4& operator /= (const float rhs)
        {
            float div = 1.0f/rhs;
            *this *= div;
            return *this;
        }

        /// binary vector add
        inline UByte4 operator + (const UByte4& rhs) const
        {
            return UByte4(_v[0]+rhs._v[0], _v[1]+rhs._v[1],
		        _v[2]+rhs._v[2], _v[3]+rhs._v[3]);
        }

        /** unary vector add.  Slightly more efficient because no temporary
            intermediate object*/
        inline UByte4& operator += (const UByte4& rhs)
        {
            _v[0] += rhs._v[0];
            _v[1] += rhs._v[1];
            _v[2] += rhs._v[2];
            _v[3] += rhs._v[3];
            return *this;
        }

        /// binary vector subtract
        inline UByte4 operator - (const UByte4& rhs) const
        {
            return UByte4(_v[0]-rhs._v[0], _v[1]-rhs._v[1],
		        _v[2]-rhs._v[2], _v[3]-rhs._v[3] );
        }

        /// unary vector subtract
        inline UByte4& operator -= (const UByte4& rhs)
        {
            _v[0]-=rhs._v[0];
            _v[1]-=rhs._v[1];
            _v[2]-=rhs._v[2];
            _v[3]-=rhs._v[3];
            return *this;
        }

        friend inline std::ostream& operator << (std::ostream& output, const UByte4& vec)
        {
	    output << vec._v[0] << " "
                   << vec._v[1] << " "
                   << vec._v[2] << " "
                   << vec._v[3];
	    return output; 	// to enable cascading
	}

};	// end of class UByte4



}	// end of namespace osg

#endif
