//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_TEXMAT
#define OSG_TEXMAT 1

#include <osg/StateAttribute.h>
#include <osg/Matrix.h>

namespace osg {

/** Texture Matrix state class for encapsulating OpenGL texture matrix functionality.*/
class SG_EXPORT TexMat : public StateAttribute
{
    public :

        TexMat();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        TexMat(const TexMat& texmat,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(texmat,copyop),
            _matrix(texmat._matrix) {}

        META_StateAttribute(osg, TexMat, TEXMAT);
        
        virtual bool isTextureAttribute() const { return true; }

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(TexMat,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_matrix)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        /** Set the texture matrix */
        inline void setMatrix(const Matrix& matrix) { _matrix = matrix; }

        /** Get the texture matrix */
        inline Matrix& getMatrix() { return _matrix; }

        /** Get the const texture matrix */
        inline const Matrix& getMatrix() const { return _matrix; }

        /** apply as OpenGL texture matrix.*/
        virtual void apply(State& state) const;

    protected:

        virtual ~TexMat( void );

        Matrix _matrix;

};

}


#endif
