//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_MATRIX
#define OSG_MATRIX 1

#include <osg/Object.h>
#include <osg/Vec3.h>
#include <osg/Vec4.h>

#include <string.h>

#include <iostream>
#include <algorithm>

namespace osg {

class Quat;

class SG_EXPORT Matrix : public Object
{

    public:

        Matrix();
        Matrix( const Matrix& other);
        explicit Matrix( float const * const def );
        Matrix( float a00, float a01, float a02, float a03,
            float a10, float a11, float a12, float a13,
            float a20, float a21, float a22, float a23,
            float a30, float a31, float a32, float a33);

        virtual Object* cloneType() const { return osgNew Matrix(); } \
        virtual Object* clone(const CopyOp&) const { return osgNew Matrix(*this); } \
        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Matrix*>(obj)!=NULL; } \
        virtual const char* libraryName() const { return "osg"; }
        virtual const char* className() const { return "Matrix"; }

        virtual ~Matrix() {}



        int compare(const Matrix& m) const { return memcmp(_mat,m._mat,sizeof(_mat)); }

        bool operator < (const Matrix& m) const { return compare(m)<0; }
        bool operator == (const Matrix& m) const { return compare(m)==0; }
        bool operator != (const Matrix& m) const { return compare(m)!=0; }

        inline float& operator()(int row, int col) { return _mat[row][col]; }
        inline float operator()(int row, int col) const { return _mat[row][col]; }

        inline const bool valid() const { return !isNaN(); }
        inline const bool isNaN() const { return osg::isNaN(_mat[0][0]) || osg::isNaN(_mat[0][1]) || osg::isNaN(_mat[0][2]) || osg::isNaN(_mat[0][3]) ||
                                                 osg::isNaN(_mat[1][0]) || osg::isNaN(_mat[1][1]) || osg::isNaN(_mat[1][2]) || osg::isNaN(_mat[1][3]) ||
                                                 osg::isNaN(_mat[2][0]) || osg::isNaN(_mat[2][1]) || osg::isNaN(_mat[2][2]) || osg::isNaN(_mat[2][3]) ||
                                                 osg::isNaN(_mat[3][0]) || osg::isNaN(_mat[3][1]) || osg::isNaN(_mat[3][2]) || osg::isNaN(_mat[3][3]); }



        inline Matrix& operator = (const Matrix& other)
        {
            if( &other == this ) return *this;
            std::copy((const float*)other._mat,(const float*)other._mat+16,(float*)(_mat));
            return *this;
        }
        
        inline void set(const Matrix& other)
        {
            std::copy((const float*)other._mat,(const float*)other._mat+16,(float*)(_mat));
        }
        
        inline void set(float const * const ptr)
        {
            std::copy(ptr,ptr+16,(float*)(_mat));
        }
        
        void set( float a00, float a01, float a02, float a03,
                  float a10, float a11, float a12, float a13,
                  float a20, float a21, float a22, float a23,
                  float a30, float a31, float a32, float a33);
                  
        float * ptr() { return (float *)_mat; }
        const float * ptr() const { return (const float *)_mat; }

        void makeIdentity();
        
        void makeScale( const Vec3& );
        void makeScale( float, float, float );
        
        void makeTranslate( const Vec3& );
        void makeTranslate( float, float, float );
        
        void makeRotate( const Vec3& from, const Vec3& to );
        void makeRotate( float angle, const Vec3& axis );
        void makeRotate( float angle, float x, float y, float z );
        void makeRotate( const Quat& );

        /** make a rotation Matrix from euler angles.
          * assume Z up, Y north, X east and euler convention
          * as per Open Flight & Performer.
          * Applies a positive rotation about Y axis for roll,
          * then applies a positive roation about X for pitch,
          * and finally a negative rotation about the Z axis.*/
        void makeRotate( float heading, float pitch, float roll); //Euler angles
        
        
        /** Set to a orthographic projection. See glOrtho for further details.*/
        void makeOrtho(const double left, const double right,
                       const double bottom, const double top,
                       const double zNear, const double zFar);

        /** Set to a 2D orthographic projection. See glOrtho2D for further details.*/
        inline void makeOrtho2D(const double left, const double right,
                                const double bottom, const double top)
        {
            makeOrtho(left,right,bottom,top,-1.0,1.0);
        }

        /** Set to a perspective projection. See glFrustum for further details.*/
        void makeFrustum(const double left, const double right,
                         const double bottom, const double top,
                         const double zNear, const double zFar);

        /** Set to a symmetrical perspective projection, See gluPerspective for further details.
          * Aspect ratio is defined as width/height.*/
        void makePerspective(const double fovy,const double aspectRatio,
                             const double zNear, const double zFar);

        /** Set to the position and orientation as per a camera, using the same convention as gluLookAt. */
        void makeLookAt(const Vec3& eye,const Vec3& center,const Vec3& up);
        

        bool invert( const Matrix& );

        //basic utility functions to create new matrices
	inline static Matrix identity( void );
        inline static Matrix scale( const Vec3& sv);
        inline static Matrix scale( float sx, float sy, float sz);
        inline static Matrix translate( const Vec3& dv);
        inline static Matrix translate( float x, float y, float z);
        inline static Matrix rotate( const Vec3& from, const Vec3& to);
        inline static Matrix rotate( float angle, float x, float y, float z);        
        inline static Matrix rotate( float angle, const Vec3& axis);
        /** construct rotation matrix from euler angles, for conventions see makeRotate().*/
        inline static Matrix rotate( float heading, float pitch, float roll);
        inline static Matrix rotate( const Quat& quat);
        inline static Matrix inverse( const Matrix& matrix);
        
        /** Create a orthographic projection. See glOrtho for further details.*/
        inline static Matrix ortho(const double left, const double right,
                                   const double bottom, const double top,
                                   const double zNear, const double zFar);

        /** Create a 2D orthographic projection. See glOrtho for further details.*/
        inline static Matrix ortho2D(const double left, const double right,
                                     const double bottom, const double top);

        /** Create a perspective projection. See glFrustum for further details.*/
        inline static Matrix frustum(const double left, const double right,
                                     const double bottom, const double top,
                                     const double zNear, const double zFar);

        /** Create a symmetrical perspective projection, See gluPerspective for further details.
          * Aspect ratio is defined as width/height.*/
        inline static Matrix perspective(const double fovy,const double aspectRatio,
                                         const double zNear, const double zFar);

        /** Create the position and orientation as per a camera, using the same convention as gluLookAt. */
        inline static Matrix lookAt(const Vec3& eye,const Vec3& center,const Vec3& up);


        inline Vec3 preMult( const Vec3& v ) const;
        inline Vec3 postMult( const Vec3& v ) const;
        inline Vec3 operator* ( const Vec3& v ) const;
        inline Vec4 preMult( const Vec4& v ) const;
        inline Vec4 postMult( const Vec4& v ) const;
        inline Vec4 operator* ( const Vec4& v ) const;

        void setTrans( float tx, float ty, float tz );
	void setTrans( const Vec3& v );
        inline Vec3 getTrans() const { return Vec3(_mat[3][0],_mat[3][1],_mat[3][2]); } 
        
        inline Vec3 getScale() const { return Vec3(_mat[0][0],_mat[1][1],_mat[2][2]); }
        
    	/** apply apply an 3x3 transform of v*M[0..2,0..2]  */
    	inline static Vec3 transform3x3(const Vec3& v,const Matrix& m);
    	/** apply apply an 3x3 transform of M[0..2,0..2]*v  */
    	inline static Vec3 transform3x3(const Matrix& m,const Vec3& v);


        // basic Matrix multiplication, our workhorse methods.
        void mult( const Matrix&, const Matrix& );
        void preMult( const Matrix& );
        void postMult( const Matrix& );

        inline void operator *= ( const Matrix& other ) 
        {    if( this == &other ) {
                Matrix temp(other);
                postMult( temp );
            }
            else postMult( other ); 
        }

        inline Matrix operator * ( const Matrix &m ) const
	{
	    osg::Matrix r;
            r.mult(*this,m);
	    return  r;
	}


// temporarily commented out while waiting for a more generic implementation
// of MatrixProduct proxy class.
//         // Helper class to optimize product expressions somewhat
//         class MatrixProduct {
//         public:
//             const Matrix& A;
//             const Matrix& B;
// 
//             MatrixProduct( const Matrix& lhs, const Matrix& rhs ) : A(lhs), B(rhs) {}
//         };
// 
//         inline MatrixProduct operator * ( const Matrix& other ) const    
//             {    return MatrixProduct(*this, other); }
// 
//         inline void operator = ( const MatrixProduct& p ) 
//             {
//                 if( this == &(p.A)) postMult(p.B);
//                 else if( this == &(p.B)) preMult(p.A);
//                 else mult( p.A, p.B );
//             }
// 
//         Matrix( const MatrixProduct& p ) //allows implicit evaluation of the product
//             {    mult( p.A, p.B ); }

    private:
        float _mat[4][4];

};

//static utility methods
inline Matrix Matrix::identity(void)
{
    Matrix m;
    m.makeIdentity();
    return m;
}

inline Matrix Matrix::scale(float sx, float sy, float sz)
{
    Matrix m;
    m.makeScale(sx,sy,sz);
    return m;
}

inline Matrix Matrix::scale(const Vec3& v )
{
    return scale(v.x(), v.y(), v.z() );
}

inline Matrix Matrix::translate(float tx, float ty, float tz)
{
    Matrix m;
    m.makeTranslate(tx,ty,tz);
    return m;
}

inline Matrix Matrix::translate(const Vec3& v )
{
    return translate(v.x(), v.y(), v.z() );
}

inline Matrix Matrix::rotate( const Quat& q )
{
    Matrix m;
    m.makeRotate( q );
    return m;
}
inline Matrix Matrix::rotate(float angle, float x, float y, float z )
{
    Matrix m;
    m.makeRotate(angle,x,y,z);
    return m;
}
inline Matrix Matrix::rotate(float angle, const Vec3& axis )
{
    Matrix m;
    m.makeRotate(angle,axis);
    return m;
}
inline Matrix Matrix::rotate(float heading, float pitch, float roll)
{
    Matrix m;
    m.makeRotate(heading,pitch,roll);
    return m;
}
inline Matrix Matrix::rotate(const Vec3& from, const Vec3& to )
{
    Matrix m;
    m.makeRotate(from,to);
    return m;
}

inline Matrix Matrix::inverse( const Matrix& matrix)
{
    Matrix m;
    m.invert(matrix);
    return m;
}

inline Matrix Matrix::ortho(const double left, const double right,
                            const double bottom, const double top,
                            const double zNear, const double zFar)
{
    Matrix m;
    m.makeOrtho(left,right,bottom,top,zNear,zFar);
    return m;
}

inline Matrix Matrix::ortho2D(const double left, const double right,
                              const double bottom, const double top)
{
    Matrix m;
    m.makeOrtho2D(left,right,bottom,top);
    return m;
}

inline Matrix Matrix::frustum(const double left, const double right,
                              const double bottom, const double top,
                              const double zNear, const double zFar)
{
    Matrix m;
    m.makeFrustum(left,right,bottom,top,zNear,zFar);
    return m;
}

inline Matrix Matrix::perspective(const double fovy,const double aspectRatio,
                                  const double zNear, const double zFar)
{
    Matrix m;
    m.makePerspective(fovy,aspectRatio,zNear,zFar);
    return m;
}

inline Matrix Matrix::lookAt(const Vec3& eye,const Vec3& center,const Vec3& up)
{
    Matrix m;
    m.makeLookAt(eye,center,up);
    return m;
}


inline Vec3 Matrix::postMult( const Vec3& v ) const
{
    float d = 1.0f/(_mat[3][0]*v.x()+_mat[3][1]*v.y()+_mat[3][2]*v.z()+_mat[3][3]) ;
    return Vec3( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3])*d,
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3])*d,
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3])*d) ;
}

inline Vec3 Matrix::preMult( const Vec3& v ) const
{
    float d = 1.0f/(_mat[0][3]*v.x()+_mat[1][3]*v.y()+_mat[2][3]*v.z()+_mat[3][3]) ;
    return Vec3( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0])*d,
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1])*d,
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2])*d);
}

inline Vec4 Matrix::postMult( const Vec4& v ) const
{
    return Vec4( (_mat[0][0]*v.x() + _mat[0][1]*v.y() + _mat[0][2]*v.z() + _mat[0][3]*v.w()),
        (_mat[1][0]*v.x() + _mat[1][1]*v.y() + _mat[1][2]*v.z() + _mat[1][3]*v.w()),
        (_mat[2][0]*v.x() + _mat[2][1]*v.y() + _mat[2][2]*v.z() + _mat[2][3]*v.w()),
        (_mat[3][0]*v.x() + _mat[3][1]*v.y() + _mat[3][2]*v.z() + _mat[3][3]*v.w())) ;
}

inline Vec4 Matrix::preMult( const Vec4& v ) const
{
    return Vec4( (_mat[0][0]*v.x() + _mat[1][0]*v.y() + _mat[2][0]*v.z() + _mat[3][0]*v.w()),
        (_mat[0][1]*v.x() + _mat[1][1]*v.y() + _mat[2][1]*v.z() + _mat[3][1]*v.w()),
        (_mat[0][2]*v.x() + _mat[1][2]*v.y() + _mat[2][2]*v.z() + _mat[3][2]*v.w()),
        (_mat[0][3]*v.x() + _mat[1][3]*v.y() + _mat[2][3]*v.z() + _mat[3][3]*v.w()));
}
inline Vec3 Matrix::transform3x3(const Vec3& v,const Matrix& m)
{
    return Vec3( (m._mat[0][0]*v.x() + m._mat[1][0]*v.y() + m._mat[2][0]*v.z()),
                 (m._mat[0][1]*v.x() + m._mat[1][1]*v.y() + m._mat[2][1]*v.z()),
                 (m._mat[0][2]*v.x() + m._mat[1][2]*v.y() + m._mat[2][2]*v.z()));
}

inline Vec3 Matrix::transform3x3(const Matrix& m,const Vec3& v)
{
    return Vec3( (m._mat[0][0]*v.x() + m._mat[0][1]*v.y() + m._mat[0][2]*v.z()),
                 (m._mat[1][0]*v.x() + m._mat[1][1]*v.y() + m._mat[1][2]*v.z()),
                 (m._mat[2][0]*v.x() + m._mat[2][1]*v.y() + m._mat[2][2]*v.z()) ) ;
}


inline Vec3 operator* (const Vec3& v, const Matrix& m )
{
	return m.preMult(v);
}
inline Vec4 operator* (const Vec4& v, const Matrix& m )
{
	return m.preMult(v);
}

inline Vec3 Matrix::operator* (const Vec3& v) const
{
	return postMult(v);
}
inline Vec4 Matrix::operator* (const Vec4& v) const
{
	return postMult(v);
}

inline std::ostream& operator<< (std::ostream& os, const Matrix& m )
{
    os << "{"<<std::endl;
    for(int row=0; row<4; ++row) {
        os << "\t";
        for(int col=0; col<4; ++col)
            os << m(row,col) << " ";
        os << std::endl;
    }
    os << "}" << std::endl;
    return os;
}


} //namespace osg


#endif
