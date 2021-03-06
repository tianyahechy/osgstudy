//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_VIEWPORT
#define OSG_VIEWPORT 1

#include <osg/StateAttribute.h>
#include <osg/Types.h>
#include <osg/Matrix.h>

namespace osg {

/** Encapsulte OpenGL glViewport.
*/     
class SG_EXPORT Viewport : public StateAttribute
{
    public :
    
    
        Viewport();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Viewport(const Viewport& vp,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(vp,copyop),
            _x(vp._x),
            _y(vp._y),
            _width(vp._width),
            _height(vp._height) {}

        META_StateAttribute(osg, Viewport,VIEWPORT);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Viewport,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_x)
            COMPARE_StateAttribute_Parameter(_y)
            COMPARE_StateAttribute_Parameter(_width)
            COMPARE_StateAttribute_Parameter(_height)
            
            return 0; // passed all the above comparison macro's, must be equal.
        }

        inline void setViewport(const int x,const int y,const int width,const int height)
        {
            _x = x;
            _y = y;
            _width = width;
            _height = height;
        }
        
        void getViewport(int& x,int& y,int& width,int& height) const
        {
            x = _x;
            y = _y;
            width = _width;
            height = _height;
        }

        inline const int x() const { return _x; }
        inline const int y() const { return _y; }
        inline const int width() const { return _width; }
        inline const int height() const { return _height; }

        inline const bool valid() const { return _width!=0 && _height!=0; }

        /** Return the aspcetRatio of the viewport, which is equal to width/height.
          * If height is zero, the potental division by zero is avoid by simply returning 1.0f.*/
        inline const float aspectRatio() const { if (_height!=0) return (float)_width/(float)_height; else return 1.0f; }
        
        /** Compute the Window Matrix which takes projected coords into Window coordinates.
          * To converted local coodinates into window coordinates use v_window = v_local * MVPW matrix, 
          * where the MVPW matrix is ModelViewMatrix * ProjectionMatrix * WindowMatrix, the later supplied by 
          * viewport::computeWindowMatrix(), the ModelView and Projection Matrix can either be sourced from the
          * current osg::State object, via osgUtil::SceneView or CullVisitor.*/
        inline const osg::Matrix computeWindowMatrix() const
        {
            return osg::Matrix::translate(1.0f,1.0f,1.0f)*osg::Matrix::scale(0.5f*width(),0.5f*height(),0.5f);
        }

        virtual void apply(State& state) const;

    protected:
    
        virtual ~Viewport();

        int _x;
        int _y;
        int _width;
        int _height;

};

}

#endif
