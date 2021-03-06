//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_EARTHSKY
#define OSG_EARTHSKY 1

#include <osg/Group.h>
#include <osg/Vec4.h>

namespace osg {

/** EarthSky is a Group node which controls the clearing of the color and depth
  * buffers at the start of each frame.
  * The earth sky by default is empty and simply holds the clear color of
  * the background. However, if the uses wants to add their own clearing of
  * the color and depth buffers then the children can be added, and the
  * background clear turned off. The EarthSky by default has StateSet attached
  * to it which sets the default EarthSky bin number to -1, so that all drawables
  * below it are placed in a separate bin from the rest of the scene graph, and
  * are rendered prior to standard opaque and transparent drawables.
*/
class SG_EXPORT EarthSky : public Group
{
    public :
        
        EarthSky();

        EarthSky(const EarthSky& es, const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            Group(es,copyop),
            _requiresClear(es._requiresClear),
            _clearColor(es._clearColor) {}  


        META_Node(osg, EarthSky);

	/** Sets the flag which control whether a glClear is required at the beginning of each frame. */
        inline void setRequiresClear(const bool requiresClear) { _requiresClear = requiresClear; }

	/** Gets the flag which control whether a glClear is required at the beginning of each frame. */
        inline const bool getRequiresClear() const { return _requiresClear; }

	/** Sets the clear color. */
        inline void setClearColor(const Vec4& color) { _clearColor = color; }

	/** Returns the clear color. */
        inline const Vec4& getClearColor() const { return _clearColor; }

    protected :
    
        virtual ~EarthSky() {}
        
        bool _requiresClear;
        Vec4 _clearColor;  
};

}

#endif
