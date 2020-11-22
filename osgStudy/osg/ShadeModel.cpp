#include "ShadeModel.h"
#include "GL.h"

using namespace osg;

osg::ShadeModel::~ShadeModel()
{
}

osg::ShadeModel::ShadeModel()
{
	_mode = SMOOTH;
}

void osg::ShadeModel::apply(State & state) const
{
	glShadeModel((GLenum)_mode);
}
