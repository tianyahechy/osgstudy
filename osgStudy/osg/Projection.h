//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_PROJECTION
#define OSG_PROJECTION 1

#include <osg/Group.h>
#include <osg/Matrix.h>

namespace osg {

/** Projection nodes set up the frustum/orthographic projection used when rendering the scene .
*/
class SG_EXPORT Projection : public Group
{
    public :


        Projection();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Projection(const Projection&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        Projection(const Matrix& matix);

        META_Node(osg, Projection);

        /** Set the transform's matrix.*/
        void setMatrix(const Matrix& mat) { (*_matrix) = mat; }
        
        /** Get the transform's matrix. */
        inline const Matrix& getMatrix() const { return *_matrix; }

        /** preMult transform.*/
        void preMult(const Matrix& mat) { _matrix->preMult(mat); }
        
        /** postMult transform.*/
        void postMult(const Matrix& mat)  { _matrix->postMult(mat); }
    

    protected :
    
        virtual ~Projection();
                       
        ref_ptr<Matrix>                     _matrix;

};

}

#endif
