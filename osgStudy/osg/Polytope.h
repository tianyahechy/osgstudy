//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_POLYTOPE
#define OSG_POLYTOPE 1

#include <osg/Plane>
#include <osg/fast_back_stack>

namespace osg {


/** A Polytope class for representing convex clipping volumes made up.
  * When adding planes, their normals should point inwards (into the volume) */
class SG_EXPORT Polytope
{

    public:

        inline Polytope() {setupMask();}

        inline Polytope(const Polytope& cv) : 
            _maskStack(cv._maskStack),
            _resultMask(cv._resultMask),
            _planeList(cv._planeList),
            _referenceVertexList(cv._referenceVertexList) {}
        
        inline Polytope(const PlaneList& pl) : _planeList(pl) {setupMask();}

        inline ~Polytope() {}

        inline void clear() { _planeList.clear(); setupMask(); }

        inline Polytope& operator = (const Polytope& cv)
        {
            if (&cv==this) return *this;
            _maskStack = cv._maskStack;
            _resultMask = cv._resultMask;
            _planeList = cv._planeList;
            _referenceVertexList = cv._referenceVertexList;
            return *this;
        }
        
        /** Create a Polytope with is cube, centered at 0,0,0, with sides of 2 units.*/
        void setToUnitFrustum(bool withNear=true, bool withFar=true)
        {
            _planeList.erase(_planeList.begin(),_planeList.end());
            _planeList.push_back(Plane(1.0f,0.0f,0.0f,1.0f)); // left plane.
            _planeList.push_back(Plane(-1.0f,0.0f,0.0f,1.0f)); // right plane.
            _planeList.push_back(Plane(0.0f,1.0f,0.0f,1.0f)); // bottom plane.
            _planeList.push_back(Plane(0.0f,-1.0f,0.0f,1.0f)); // top plane.
            if (withNear) _planeList.push_back(Plane(0.0f,0.0f,-1.0f,1.0f)); // near plane
            if (withFar) _planeList.push_back(Plane(0.0f,0.0f,1.0f,1.0f)); // far plane
            setupMask();
        }

        inline void set(const PlaneList& pl) { _planeList = pl; setupMask(); }
        
        inline void add(const osg::Plane& pl) { _planeList.push_back(pl); setupMask(); }

        /** flip/reverse the orientation of all the planes.*/
        inline void flip()
        {
            for(PlaneList::iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                itr->flip();
            }
        }


        inline PlaneList& getPlaneList() { return _planeList; }

        inline const PlaneList& getPlaneList() const { return _planeList; }


        inline void setReferenceVertexList(VertexList& vertices) { _referenceVertexList=vertices; }

        inline VertexList& getReferenceVertexList() { return _referenceVertexList; }
        
        inline const VertexList& getReferenceVertexList() const { return _referenceVertexList; }


        inline void setupMask()
        {
            _resultMask = 0;
            for(unsigned int i=0;i<_planeList.size();++i)
            {
                _resultMask = (_resultMask<<1) | 1;
            }
            _maskStack.back() = _resultMask;
        }

        inline ClippingMask& getCurrentMask() { return _maskStack.back(); }

        inline ClippingMask getCurrentMask() const { return _maskStack.back(); }

        inline void setResultMask(ClippingMask mask) { _resultMask=mask; }

        inline ClippingMask getResultMask() const { return _resultMask; }
        
        MaskStack& getMaskStack() { return _maskStack; }
        
        const MaskStack& getMaskStack() const { return _maskStack; }
        
        
        inline void pushCurrentMask()
        {
            _maskStack.push_back(_resultMask);
        }

        inline void popCurrentMask()
        {
            _maskStack.pop_back();
        }

        /** Check whether a vertex is contained with clipping set.*/
        inline const bool contains(const osg::Vec3& v) const
        {
            if (!_maskStack.back()) return true;
            
            unsigned int selector_mask = 0x1;
            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if ((_maskStack.back()&selector_mask) && (itr->distance(v)<0.0f)) return false;
                selector_mask <<= 1;
            }
            return true;
        }

        /** Check whether any part of vertex list is contained with clipping set.*/
        inline const bool contains(const std::vector<Vec3>& vertices)
        {
            if (!_maskStack.back()) return true;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;

            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(vertices);
                    if (res<0) return false; // outside clipping set.
                    else if (res>0) _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }

        /** Check whether any part of a bounding sphere is contained within clipping set.
            Using a mask to determine which planes should be used for the check, and
            modifying the mask to turn off planes which wouldn't contribute to clipping
            of any internal objects.  This feature is used in osgUtil::CullVisitor
            to prevent redundant plane checking.*/
        inline const bool contains(const osg::BoundingSphere& bs)
        {
            if (!_maskStack.back()) return true;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;

            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(bs);
                    if (res<0) return false; // outside clipping set.
                    else if (res>0) _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }
        
        /** Check whether any part of a bounding box is contained within clipping set.
            Using a mask to determine which planes should be used for the check, and
            modifying the mask to turn off planes which wouldn't contribute to clipping
            of any internal objects.  This feature is used in osgUtil::CullVisitor
            to prevent redundant plane checking.*/
        inline const bool contains(const osg::BoundingBox& bb)
        {
            if (!_maskStack.back()) return true;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;

            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(bb);
                    if (res<0) return false; // outside clipping set.
                    else if (res>0) _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }

        /** Check whether all of vertex list is contained with clipping set.*/
        inline const bool containsAllOf(const std::vector<Vec3>& vertices)
        {
            if (!_maskStack.back()) return false;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;

            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(vertices);
                    if (res<1) return false;  // intersects, or is below plane.
                    _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }

        /** Check whether the entire bounding sphere is contained within clipping set.*/
        inline const bool containsAllOf(const osg::BoundingSphere& bs)
        {
            if (!_maskStack.back()) return false;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;
            
            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(bs);
                    if (res<1) return false;  // intersects, or is below plane.
                    _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }
        
        /** Check whether the entire bounding box is contained within clipping set.*/
        inline const bool containsAllOf(const osg::BoundingBox& bb)
        {
            if (!_maskStack.back()) return false;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;

            for(PlaneList::const_iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    int res=itr->intersect(bb);
                    if (res<1) return false;  // intersects, or is below plane.
                    _resultMask ^= selector_mask; // subsequent checks against this plane not required.
                }
                selector_mask <<= 1; 
            }
            return true;
        }

        
        /** Transform the clipping set by matrix.  Note, this operations carries out
          * the calculation of the inverse of the matrix since to transforms
          * planes must be multiplied my the inverse transposed. This
          * make this operation expensive.  If the inverse has been already
          * calculated elsewhere then use transformProvidingInverse() instead.
          * See http://www.worldserver.com/turk/computergraphics/NormalTransformations.pdf*/
        inline void transform(const osg::Matrix& matrix)
        {
            osg::Matrix inverse;
            inverse.invert(matrix);
            transformProvidingInverse(inverse);
        }
        
        /** Transform the clipping set by provide a pre inverted matrix.
          * see transform for details. */
        inline void transformProvidingInverse(const osg::Matrix& matrix)
        {
            if (!_maskStack.back()) return;

            _resultMask = _maskStack.back();
            ClippingMask selector_mask = 0x1;
            for(PlaneList::iterator itr=_planeList.begin();
                itr!=_planeList.end();
                ++itr)
            {
                if (_resultMask&selector_mask)
                {
                    itr->transformProvidingInverse(matrix);
                    selector_mask <<= 1; 
                }
            }
        }
        
    protected:


        MaskStack                           _maskStack;
        ClippingMask                        _resultMask;
        PlaneList                           _planeList;
        VertexList                          _referenceVertexList;

};

}	// end of namespace

#endif 
