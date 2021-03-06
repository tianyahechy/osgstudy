#include <osg/ColorMatrix.h>
#include <osg/GL.h>
#include <osg/GLExtensions.h>

using namespace osg;

ColorMatrix::ColorMatrix()
{
}


ColorMatrix::~ColorMatrix()
{
}

void ColorMatrix::apply(State&) const
{
//    std::cout<<"applying matrix"<<_matrix<<std::endl;
    static bool s_ARB_imaging = isGLExtensionSupported("GL_ARB_imaging");
    if (s_ARB_imaging)
    {
        glMatrixMode( GL_COLOR );
        glLoadMatrixf( _matrix.ptr() );
        glMatrixMode( GL_MODELVIEW );
    }
}
