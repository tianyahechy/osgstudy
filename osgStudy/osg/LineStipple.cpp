#include <osg/GL.h>
#include <osg/LineStipple.h>
#include <osg/Notify.h>

using namespace osg;


LineStipple::LineStipple()
{
  _factor = 1;
  _pattern = 0xffff;
}


LineStipple::~LineStipple()
{
}

void LineStipple::setFactor(const int factor)
{
  _factor = factor;
}
  
void LineStipple::setPattern(const unsigned short pattern)
{
  _pattern = pattern;
}

void LineStipple::apply(State&) const
{
  glLineStipple(_factor, _pattern);
}

