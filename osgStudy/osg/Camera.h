//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_CAMERA
#define OSG_CAMERA 1

#include <osg/Export.h>
#include <osg/ref_ptr.h>
#include <osg/Referenced.h>
#include <osg/Matrix.h>
#include <osg/Quat.h>
#include <osg/Viewport.h>
#include <osg/DisplaySettings.h>

namespace osg {

/** Camera class for encapsulating the view position and orientation and
  * projection (lens) used.  Creates a projection and modelview matrices
  * which can be used to set OpenGL's PROJECTION and MODELVIEW matrices
  * respectively.
  */
class SG_EXPORT Camera: public osg::Referenced
{

    public:

        Camera(DisplaySettings* ds=NULL);
        
        Camera(const Camera&);
        Camera& operator=(const Camera&);
        virtual ~Camera();

        /** Range of projection types.
          * ORTHO2D is a special case of ORTHO where the near and far planes
          * are equal to -1 and 1 respectively.
          * PERSPECTIVE is a special case of FRUSTUM where the left & right
          * and bottom and top and symmetrical.*/
        enum ProjectionType
        {
            ORTHO,
            ORTHO2D,
            FRUSTUM,
            PERSPECTIVE
        };

        /** Get the projection type set by setOtho,setOtho2D,setFrustum,
          * and set perspective methods.*/
        const ProjectionType getProjectionType() const { return _projectionType; }

        /** Set a orthographic projection. See glOrtho for further details.*/
        void setOrtho(const double left, const double right,
                      const double bottom, const double top,
                      const double zNear, const double zFar);
                      
        /** Set a 2D orthographic projection. See gluOrtho2D for further details.*/
        void setOrtho2D(const double left, const double right,
                        const double bottom, const double top);

        /** Set a perspective projection. See glFrustum for further details.*/
        void setFrustum(const double left, const double right,
                        const double bottom, const double top,
                        const double zNear, const double zFar);

        /** Set a symmetrical perspective projection, See gluPerspective for further details.
          * Aspect ratio is defined as width/height.*/
        void setPerspective(const double fovy,const double aspectRatio,
                            const double zNear, const double zFar);

        /** Set a sysmmetical perspective projection using field of view.*/
        void setFOV(const double fovx,const double fovy,
                            const double zNear, const double zFar);
        
        /** Set the near and far clipping planes.*/
        void setNearFar(const double zNear, const double zFar);

        /** Use in combination with adjustAspectRatio, to control
          * the change in frustum clipping planes to account for
          * changes in windows aspect ratio,*/
        enum AdjustAspectRatioMode
        {
            ADJUST_VERTICAL,
            ADJUST_HORIZONTAL,
            ADJUST_NONE
        };
        
        /** Set the way that the vertical or horizontal dimensions of the window
          * are adjusted on a resize. */
        void setAdjustAspectRatioMode(const AdjustAspectRatioMode aam) { _adjustAspectRatioMode = aam; }
        
        /** Get the way that the vertical or horizontal dimensions of the window
          * are adjusted on a resize. */
        const AdjustAspectRatioMode getAdjustAspectRatioMode() const { return _adjustAspectRatioMode; }

        /** Adjust the clipping planes to account for a new window aspect ratio.
          * Typically used after resizing a window. Aspect ratio is defined as
          * width/height.*/
        void adjustAspectRatio(const double newAspectRatio)
        {
            adjustAspectRatio(newAspectRatio,_adjustAspectRatioMode);
        }

        /** Adjust the clipping planes to account for a new window aspect ratio.
          * Typicall used after resizeing a window. Aspect ratio is defined as
          * width/height.*/
        void adjustAspectRatio(const double newAspectRatio, const AdjustAspectRatioMode aa);

        const double left() const { return _left; }
        const double right() const { return _right; }
        const double bottom() const { return _bottom; }
        const double top() const { return _top; }
        const double zNear() const { return _zNear; }
        const double zFar() const { return _zFar; }

        /** Calculate and return the equivalent fovx for the current project setting.
          * This value is only valid for when a symmetric perspective projection exists.
          * i.e. getProjectionType()==PERSPECTIVE.*/
        const double calc_fovy() const;

        /** Calculate and return the equivalent fovy for the current project setting.
          * This value is only valid for when a symmetric perspective projection exists.
          * i.e. getProjectionType()==PERSPECTIVE.*/
        const double calc_fovx() const;
        
        /** Calculate and return the projection aspect ratio.
          * Aspect ratio is defined as width/height.*/
        const double calc_aspectRatio() const;






        enum LookAtType
        {
            USE_HOME_POSITON,
            USE_EYE_AND_QUATERNION,
            USE_EYE_CENTER_AND_UP
        };
        
        const LookAtType getLookAtType() const { return _lookAtType; }

        /**
         * hardwired home view for now, looking straight down the
         * Z axis at the origin, with 'up' being the y axis.
         */
        void home();

        /**
          * Set the View, the up vector should be orthogonal to the look vector.
          * setView is now mapped to setLookAt(eye,center,up), and is only
          * kept for backwards compatibility.
          */
        void setView(const Vec3& eyePoint,
	             const Vec3& lookPoint,
	             const Vec3& upVector);
        
        /** set the position and orientation of the camera, using the same convention as
          * gluLookAt.
          */
        void setLookAt(const Vec3& eye,
                       const Vec3& center,
                       const Vec3& up);
        
        /** set the position and orientation of the camera, using the same convention as
          * gluLookAt.
          */
        void setLookAt(const double eyeX, const double eyeY, const double eyeZ,
                       const double centerX, const double centerY, const double centerZ,
                       const double upX, const double upY, const double upZ);
        
        /** post multiple the existing eye point and orientation by matrix.
          * note, does not affect any ModelTransforms that are applied.*/
        void transformLookAt(const Matrix& matrix);
        
        void ensureOrthogonalUpVector();        

        /** get the eye point. */
        inline const Vec3& getEyePoint() const      { return _eye; }

        /** get the center point. */
        inline const Vec3& getCenterPoint() const   { return _center; }

        /** get the up vector */
        inline const Vec3& getUpVector() const      { return _up; }

        /** calculate look vector.*/
        const Vec3 getLookVector() const;

        /** calculate side vector.*/
        const Vec3 getSideVector() const;

        /** calculate the look distance which is the distance between the eye and the center.*/
        inline float getLookDistance() const { return (_center-_eye).length(); }

        enum TransformMode
        {
            EYE_TO_MODEL,
            MODEL_TO_EYE,
            NO_ATTACHED_TRANSFORM
        };
            

        /** Attach a transform matrix which is applied after the camera look at.
          * The attached matrix can work in two ways, either as transform of the eye
          * into the model coordinates - EYE_TO_MODEL, or as a transform of the
          * model to the eye - MODEL_TO_EYE.  The former is equivalent to attaching
          * a camera internal to the scene graph.  The later is equivalent to adding 
          * a osg::Transform at root of the scene to move the scene to the eye point.
          * Typical used in conjunction with the LookAt position set to home,
          * in which case it is simply treated as a model view matrix.
          * If the same behavior as IRIS Performer's setViewMat is desired 
          * then set the LookAt to be (0,0,0),(0,1,0),(0,0,1) since Performer's
          * default direction is along the y axis, unlike OpenGL and the default OSG.
          * If modelTransfor is NULL then do not use any model transform - just use the
          * basic LookAt values.
          * note: Camera internals maintains the both EYE_TO_MODEL and MODEL_TO_EYE
          * internally and ensures that they are the inverse of one another.*/
        void attachTransform(const TransformMode mode, Matrix* modelTransform=0);

        Matrix* getTransform(const TransformMode mode);
        
        const Matrix* getTransform(const TransformMode mode) const;

        
        

        enum FusionDistanceMode
        {
            PROPORTIONAL_TO_LOOK_DISTANCE,
            PROPORTIONAL_TO_SCREEN_DISTANCE
        };
        
        /** Set the mode of the fusion distance function which in use to calculate the
          * fusion distance used in stereo rendering. Default value is
          * PROPORTIONAL_TO_LOOK_DISTANCE. Use in conjunction with setFusionDistanceRatio(float).*/
        void setFusionDistanceMode(FusionDistanceMode mode) { _fusionDistanceMode = mode; }

        /** Get the mode of the fusion distance function.*/
        FusionDistanceMode getFusionDistanceMode() const { return _fusionDistanceMode; }

        /** Set the ratio of the fusion distance function which in use to calculate the
          * fusion distance used in stereo rendering. Default value is 1.0f
          * Use in conjunction with setFusionDistanceMode(..).*/
        void setFusionDistanceRatio(float ratio) { _fusionDistanceRatio = ratio; }

        /** Get the ratio of the fusion distance function.*/
        float getFusionDistanceRatio() const { return _fusionDistanceRatio; }

        /** Calculate and return the fusion distance, using the FusionDistanceFunction.*/
        const float getFusionDistance() const;
                
                
        /** Set the physical distance between the viewers eyes and the display system.
           * Note, only used when rendering in stereo.*/
        void setScreenDistance(float screenDistance) { _screenDistance = screenDistance; }

        /** Get the physical distance between the viewers eyes and the display system.*/
        const float getScreenDistance() const { return _screenDistance; }


        
        /** Get the Projection Matrix.*/
        const Matrix getProjectionMatrix() const;

        /** Get the ModelView matrix. 
          * If a ModelTransform is supplied then the ModelView matrix is
          * created by multiplying the current LookAt by ModelTransform.
          * Otherwise it is simply created by using the current LookAt,
          * equivalent to using gluLookAt.*/
        const Matrix getModelViewMatrix() const;








    protected:

        void copy(const Camera&);

        // projection details.
        ProjectionType  _projectionType;

        // how the window dimensions should be altered during a window resize.
        AdjustAspectRatioMode _adjustAspectRatioMode;

        // note, in Frustum/Perspective mode these values are scaled
        // by the zNear from when they were initialised to ensure that
        // subsequent changes in zNear do not affect them.
        double          _left;
        double          _right;
        double          _bottom;
        double          _top;

        double          _zNear;
        double          _zFar;

        
        // look at details.
        LookAtType      _lookAtType;
        
        Vec3            _eye;
        Vec3            _center;
        Vec3            _up;
        
        TransformMode   _attachedTransformMode;
        ref_ptr<Matrix> _eyeToModelTransform;
        ref_ptr<Matrix> _modelToEyeTransform;

        float               _screenDistance;
        
        FusionDistanceMode  _fusionDistanceMode;
        float               _fusionDistanceRatio;

};

}

# endif
