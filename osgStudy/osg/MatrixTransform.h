//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_MATRIXTRANSFORM
#define OSG_MATRIXTRANSFORM 1

#include <osg/Transform.h>

namespace osg {

/** Transform - is group which all children are transformed by the the Transform's osg::Matrix.  
  * Typical uses
  * of the Transform is for positioning objects within a scene or 
  * producing trackball functionality or for animation.
  * The Transform node can be customized via the ComputeTransfromCallback which can be
  * attached to the node, this might be used to convert internal representations of the transformation
  * into generic osg::Matrix'c which are used during scene grpah traversal, such as CullTraversal and IntersectionTraversal.
  * Note, if the transformation matrix scales the subgraph then the
  * normals of the underlying geometry will need to be renormalized to
  * be unit vectors once more.  One can done transparently through OpenGL's 
  * use of either GL_NORMALIZE and GL_SCALE_NORMALIZE modes.  Further
  * background reading see the glNormalize documentation in the OpenGL Reference 
  * Guide (the blue book). To enable it in the OSG, you simple need to
  * attach a local osg::StateSet to the osg::Transform, and set the appropriate
  * mode to on via stateset->setMode(GL_NORMALIZE,osg::StateAttribute::ON);.
*/
class SG_EXPORT MatrixTransform : public Transform
{
    public :


        MatrixTransform();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        MatrixTransform(const MatrixTransform&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        MatrixTransform(const Matrix& matix);

        META_Node(osg, MatrixTransform);

        /** Set the transform's matrix.*/
        void setMatrix(const Matrix& mat) { (*_matrix) = mat; _inverseDirty=true; computeInverse(); dirtyBound(); }
        
        /** Get the transform's matrix. */
        inline const Matrix& getMatrix() const { return *_matrix; }

        /** preMult transform.*/
        void preMult(const Matrix& mat) { _matrix->preMult(mat); _inverseDirty=true; computeInverse(); dirtyBound(); }
        
        /** postMult transform.*/
        void postMult(const Matrix& mat)  { _matrix->postMult(mat); _inverseDirty=true; computeInverse(); dirtyBound(); }
    
        virtual const bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_PARENTS)
            {
                matrix.preMult(*_matrix);
            }
            else // absolute
            {
                matrix = *_matrix;
            }
            return true;
        }

        virtual const bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_PARENTS)
            {
                matrix.postMult(*_inverse);
            }
            else // absolute
            {
                matrix = *_inverse;
            }
            return true;
        }

    protected :
    
        virtual ~MatrixTransform();
        
        inline void computeInverse() const
        {
            if (_inverseDirty)
            {
                _inverse->invert(*_matrix);
                _inverseDirty = false;
            }
        }

        ref_ptr<Matrix>                     _matrix;
        mutable ref_ptr<Matrix>             _inverse;
        mutable bool                        _inverseDirty;        

};

}

#endif
