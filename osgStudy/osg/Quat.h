//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_QUAT
#define OSG_QUAT 1

#include <osg/Vec3.h>
#include <osg/Vec4.h>
#include <osg/Matrix.h>

namespace osg {

/** A quaternion class. It can be used to represent an orientation in 3D space.*/
class SG_EXPORT Quat
{

    public:

     /* ----------------------------------------------------------
				DATA MEMBERS
        The only data member is a
	Vec4 which holds the elements

	In other words, osg:Quat is composed of an osg::Vec4
	The osg::Quat aggregates an osg::Vec4

	These seem to be different jargon for the same thing :-)
	---------------------------------------------------------- */
	Vec4 _fv;	// a four-vector

	Quat(): _fv(0.0f,0.0f,0.0f,1.0f) {}
	Quat( float x, float y, float z, float w ):  _fv(x,y,z,w) {}
	Quat( const Vec4& v ): _fv(v) {}

     /* ----------------------------------
	   Methods to access data members
	---------------------------------- */
	inline Vec4& asVec4()
	{
	    return _fv;
	}

	inline const Vec4& asVec4() const
	{
	    return _fv;
	}

	inline const Vec3 asVec3() const
	{
	    return Vec3(_fv[0], _fv[1], _fv[2]);
	}

        inline void set(const float x, const float y, const float z, const float w)
        {
            _fv.set(x,y,z,w);
        }
        
        inline void set(const osg::Vec4& v)
        {
            _fv = v;
        }


     /* ------------------------------------------------------------- 
	 		  BASIC ARITHMETIC METHODS		    
	Implemented in terms of Vec4s.  Some Vec4 operators, e.g.
	operator* are not appropriate for quaternions (as
	mathematical objects) so they are implemented differently.
	Also define methods for conjugate and the multiplicative inverse.		    
	------------------------------------------------------------- */
	/// Multiply by scalar 
        inline const Quat operator * (const float rhs) const
        {
            return Quat(_fv*rhs);
        }

	/// Unary multiply by scalar 
        inline Quat& operator *= (const float rhs)
        {
            _fv*=rhs;
            return *this;		// enable nesting
        }

	/// Binary multiply 
	inline const Quat operator*(const Quat& rhs) const
	{
	    return Quat( _fv[3]*rhs._fv[0] + _fv[0]*rhs._fv[3] + _fv[1]*rhs._fv[2] - _fv[2]*rhs._fv[1],
			 _fv[3]*rhs._fv[1] - _fv[0]*rhs._fv[2] + _fv[1]*rhs._fv[3] + _fv[2]*rhs._fv[0],
			 _fv[3]*rhs._fv[2] + _fv[0]*rhs._fv[1] - _fv[1]*rhs._fv[0] + _fv[2]*rhs._fv[3],
			 _fv[3]*rhs._fv[3] - _fv[0]*rhs._fv[0] - _fv[1]*rhs._fv[1] - _fv[2]*rhs._fv[2] );
	}

	/// Unary multiply 
	inline Quat& operator*=(const Quat& rhs)
	{
	    float x = _fv[3]*rhs._fv[0] + _fv[0]*rhs._fv[3] + _fv[1]*rhs._fv[2] - _fv[2]*rhs._fv[1];
	    float y = _fv[3]*rhs._fv[1] - _fv[0]*rhs._fv[2] + _fv[1]*rhs._fv[3] + _fv[2]*rhs._fv[0];
	    float z = _fv[3]*rhs._fv[2] + _fv[0]*rhs._fv[1] - _fv[1]*rhs._fv[0] + _fv[2]*rhs._fv[3];
	    _fv[3]   = _fv[3]*rhs._fv[3] - _fv[0]*rhs._fv[0] - _fv[1]*rhs._fv[1] - _fv[2]*rhs._fv[2];

	    _fv[2] = z;
	    _fv[1] = y;
	    _fv[0] = x;

	    return (*this);			// enable nesting
	}

	/// Divide by scalar 
        inline const Quat operator / (const float& rhs) const
        {
            return Quat(_fv/rhs);
        }

	/// Unary divide by scalar 
        inline Quat& operator /= (const float& rhs)
        {
            _fv/=rhs;
            return *this;
        }

	/// Binary divide 
	inline const Quat operator/(const Quat& denom) const
	{
	    return ( (*this) * denom.inverse() );
	}

	/// Unary divide 
	inline Quat& operator/=(const Quat& denom)
	{
	    (*this) = (*this) * denom.inverse();
	    return (*this);			// enable nesting
	}

	/// Binary addition 
        inline const Quat operator + (const Quat& rhs) const
        {
            return Quat( _fv + rhs._fv );
        }

	/// Unary addition
        inline Quat& operator += (const Quat& rhs)
        {
            _fv += rhs._fv;
            return *this;			// enable nesting
        }

        /// Binary subtraction 
        inline const Quat operator - (const Quat& rhs) const
        {
            return Quat( _fv - rhs._fv );
        }

        /// Unary subtraction 
        inline Quat& operator -= (const Quat& rhs)
        {
            _fv-=rhs._fv;
            return *this;			// enable nesting
        }

        /** Negation operator - returns the negative of the quaternion.
	    Basically just calls operator - () on the Vec4 */
        inline const Quat operator - () const
        {
            return Quat ( -_fv );
        }

        /// Length of the quaternion = sqrt( vec . vec )
        const float length() const
        {
            return _fv.length();
        }

        /// Length of the quaternion = vec . vec
        const float length2() const
        {
            return _fv.length2();
        }

        /// Conjugate 
        inline const Quat conj () const
        { 
             return Quat( -_fv[0], -_fv[1], -_fv[2], _fv[3] );
        }

        /// Multiplicative inverse method: q^(-1) = q^*/(q.q^*)
        inline const Quat inverse () const
        {
             return conj() / length2();
         }

      /* -------------------------------------------------------- 
	 		  METHODS RELATED TO ROTATIONS
	Set a quaternion which will perform a rotation of an
	angle around the axis given by the vector (x,y,z).
	Should be written to also accept an angle and a Vec3?

	Define Spherical Linear interpolation method also

	Not inlined - see the Quat.cpp file for implementation
	-------------------------------------------------------- */
        void makeRotate ( const float angle, 
                          const float x, const float y, const float z );
        void makeRotate ( const float angle, const Vec3& vec );

        /** Make a rotation Quat which will rotate vec1 to vec2.
            Generally take adot product to get the angle between these
            and then use a cross product to get the rotation axis
            Watch out for the two special cases of when the vectors
            are co-incident or opposite in direction.*/
        void makeRotate( const Vec3& vec1, const Vec3& vec2 );

        /** make a rotation Quat from euler angles.
          * assume Z up, Y north, X east and euler convention
          * as per Open Flight & Performer.
          * Applies a positive rotation about Y axis for roll,
          * then applies a positive roation about X for pitch,
          * and finally a negative rotation about the Z axis.*/
        void makeRotate( float heading, float pitch, float roll);
    
    
            /** Return the angle and vector components represented by the quaternion.*/
        void getRotate ( float& angle, float& x, float& y, float& z ) const;
        /** Return the angle and vector represented by the quaternion.*/
        void getRotate ( float& angle, Vec3& vec ) const;

        /** Spherical Linear Interpolation.
	    As t goes from 0 to 1, the Quat object goes from "from" to "to". */
        void slerp   ( const float t, const Quat& from, const Quat& to);
        
        /** Set quaternion to be equivalent to specified matrix.*/
        void set( const Matrix& m );

        /** Get the equivalent matrix for this quaternion.*/
        void get( Matrix& m ) const;

        /** Get the equivalent matrix for this quaternion.*/
        Matrix getMatrix() const
        {
            Matrix matrix;
            get(matrix);
            return matrix;
        }


        friend inline std::ostream& operator << (std::ostream& output, const Quat& vec);

};	// end of class prototype

inline std::ostream& operator << (std::ostream& output, const Quat& vec)
{
    output << vec._fv[0] << " "
	   << vec._fv[1] << " "
	   << vec._fv[2] << " "
	   << vec._fv[3];
    return output; 	// to enable cascading
}

}	// end of namespace

#endif 
