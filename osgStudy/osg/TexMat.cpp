#include <osg/GL.h>
#include <osg/TexMat.h>

using namespace osg;

TexMat::TexMat()
{
}


TexMat::~TexMat()
{
}

void TexMat::apply(State&) const
{
    glMatrixMode( GL_TEXTURE );
    glLoadMatrixf( _matrix.ptr() );
    glMatrixMode( GL_MODELVIEW ); // fix! GWM Aug 2001
}
