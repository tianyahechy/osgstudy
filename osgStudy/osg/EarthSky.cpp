#include <osg/EarthSky.h>

#include <algorithm>

using namespace osg;

/**
 * EarthSky constructor.
 */
EarthSky::EarthSky()
{
    StateSet* stateset = osgNew StateSet;
    stateset->setRenderBinDetails(-1,"RenderBin");
    setStateSet(stateset);
    
    _requiresClear = true;
    _clearColor.set(0.0f,0.0f,0.0f,1.0f);  

}

