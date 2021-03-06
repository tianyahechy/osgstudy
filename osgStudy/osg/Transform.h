//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_TRANSFORM
#define OSG_TRANSFORM 1

#include <osg/Group.h>
#include <osg/Matrix.h>

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
class SG_EXPORT Transform : public Group
{
    public :


        Transform();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Transform(const Transform&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

#ifdef USE_DEPRECATED_API
        Transform(const Matrix& matix);
#endif
        META_Node(osg, Transform);

        enum ReferenceFrame
        {
            RELATIVE_TO_PARENTS,
            RELATIVE_TO_ABSOLUTE
        };
        
        /** Set the transform's ReferenceFrame, either to be realtive to its parent reference frame, 
          * or relative to an absolute coordinate frame. RELATIVE_TO_PARENTS is the default.
          * Note,  setting the RefrenceFrame to be RELATIVE_TO_ABSOLUTE will also set the CullingActive flag on the
          * transform, and hence all its parents, to false, therby disabling culling of it and all its
          * parents.  This is neccessary to prevent inappropriate culling, but may impact of cull times
          * if the absolute transform is deep in the scene graph, it is therefore recommend to only use
          * abolsoute Transforms at the top of the scene, for such things as headlight LightSource's or
          * Head up displays.*/
        void setReferenceFrame(ReferenceFrame rf);
        
        const ReferenceFrame getReferenceFrame() const { return _referenceFrame; }

        
        /** Callback attached to an Transform to specifiy how to compute the modelview transformation
          * for the transform below the Transform node.*/
        struct ComputeTransformCallback : public osg::Referenced
        {
            /** Get the transformation matrix which moves from local coords to world coords.*/
            virtual const bool computeLocalToWorldMatrix(Matrix& matrix,const Transform* transform, NodeVisitor* nv) const = 0;

            /** Get the transformation matrix which moves from world coords to local coords.*/
            virtual const bool computeWorldToLocalMatrix(Matrix& matrix,const Transform* transform, NodeVisitor* nv) const = 0;
        };

        /** Set the ComputerTransfromCallback which allows users to attach custom computation of the local transformation as 
          * seen by cull traversers and alike.*/
        void setComputeTransformCallback(ComputeTransformCallback* ctc) { _computeTransformCallback=ctc; dirtyBound(); }
        
        /** Get the non const ComputerTransfromCallback.*/
        ComputeTransformCallback* getComputeTransformCallback() { return _computeTransformCallback.get(); }
        
        /** Get the const ComputerTransfromCallback.*/
        const ComputeTransformCallback* getComputeTransformCallback() const { return _computeTransformCallback.get(); }



        /** Get the transformation matrix which moves from local coords to world coords.
          * Return true if Matrix passed in has been modified and */
        inline const bool getLocalToWorldMatrix(Matrix& matrix,NodeVisitor* nv) const
        {
            if (_computeTransformCallback.valid())
                return _computeTransformCallback->computeLocalToWorldMatrix(matrix,this,nv);
            else
                return computeLocalToWorldMatrix(matrix,nv);
        }
        

        /** Get the transformation matrix which moves from world coords to local coords.
          * Return true if Matrix passed in has been modified and */
        inline const bool getWorldToLocalMatrix(Matrix& matrix,NodeVisitor* nv) const
        {
            if (_computeTransformCallback.valid())
                return _computeTransformCallback->computeWorldToLocalMatrix(matrix,this,nv);
            else
                return computeWorldToLocalMatrix(matrix,nv);
        }
        

#ifndef USE_DEPRECATED_API

        virtual const bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_ABSOLUTE)
            {
                return false;
            }
            else // absolute
            {
                matrix.makeIdentity();
                return true;
            }
        }
        
        virtual const bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_ABSOLUTE)
            {
                return false;
            }
            else // absolute
            {
                matrix.makeIdentity();
                return true;
            }
        }

#else

        /** Set the transform's matrix.*/
        void setMatrix(const Matrix& mat) { (*_deprecated_matrix) = mat; _deprecated_inverseDirty=true; computeInverse(); dirtyBound(); }
        
        /** Get the transform's matrix. */
        inline const Matrix& getMatrix() const { return *_deprecated_matrix; }

        /** preMult transform.*/
        void preMult(const Matrix& mat) { _deprecated_matrix->preMult(mat); _deprecated_inverseDirty=true; computeInverse(); dirtyBound(); }
        
        /** postMult transform.*/
        void postMult(const Matrix& mat)  { _deprecated_matrix->postMult(mat); _deprecated_inverseDirty=true; computeInverse(); dirtyBound(); }
    
        virtual const bool computeLocalToWorldMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_PARENTS)
            {
                matrix.preMult(*_deprecated_matrix);
            }
            else // absolute
            {
                matrix = *_deprecated_matrix;
            }
            return true;
        }

        virtual const bool computeWorldToLocalMatrix(Matrix& matrix,NodeVisitor*) const
        {
            if (_referenceFrame==RELATIVE_TO_PARENTS)
            {
                matrix.postMult(*_deprecated_inverse);
            }
            else // absolute
            {
                matrix = *_deprecated_inverse;
            }
            return true;
        }
#endif


    protected :
    
        virtual ~Transform();
        
        /** Override's Group's computeBound. 
          * There is no need to override in subclasses from osg::Transform since this computeBound() uses 
          * the underlying matrix (calling computeMatrix if required.) */
        virtual const bool computeBound() const;
        
        


        ref_ptr<ComputeTransformCallback>   _computeTransformCallback;

        ReferenceFrame                      _referenceFrame;

#ifdef USE_DEPRECATED_API
        inline void computeInverse() const
        {
            if (_deprecated_inverseDirty)
            {
                _deprecated_inverse->invert(*_deprecated_matrix);
                _deprecated_inverseDirty = false;
            }
        }

        ref_ptr<Matrix>                     _deprecated_matrix;
        mutable ref_ptr<Matrix>             _deprecated_inverse;
        mutable bool                        _deprecated_inverseDirty;        
#endif

};

}

#endif
