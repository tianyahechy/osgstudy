#include <osg/GL.h>
#include <osg/LineWidth.h>
#include <osg/Notify.h>

using namespace osg;


LineWidth::LineWidth()
{
    _width = 1.0f;
}


LineWidth::~LineWidth()
{
}

void LineWidth::setWidth( const float width )
{
    _width = width;
}

void LineWidth::apply(State&) const
{
    glLineWidth(_width);
}

