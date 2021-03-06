//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_TEXGEN
#define OSG_TEXGEN 1

#include <osg/Vec4.h>
#include <osg/StateAttribute.h>

namespace osg {

#ifndef GL_NORMAL_MAP_ARB
#define GL_NORMAL_MAP_ARB                   0x8511
#endif

#ifndef GL_REFLECTION_MAP_ARB
#define GL_REFLECTION_MAP_ARB               0x8512
#endif

/** TexGen - encapsulates the OpenGL glTexGen (texture coordinate generation) state.*/
class SG_EXPORT TexGen : public StateAttribute
{
    public :
    
        TexGen();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        TexGen(const TexGen& texgen,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(texgen,copyop),
            _mode(texgen._mode),
            _plane_s(texgen._plane_s),
            _plane_t(texgen._plane_t),
            _plane_r(texgen._plane_r),
            _plane_q(texgen._plane_q) {}

        META_StateAttribute(osg, TexGen, TEXGEN);
        
        virtual bool isTextureAttribute() const { return true; }

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(TexGen,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_mode)
            COMPARE_StateAttribute_Parameter(_plane_s)
            COMPARE_StateAttribute_Parameter(_plane_s)
            COMPARE_StateAttribute_Parameter(_plane_r)
            COMPARE_StateAttribute_Parameter(_plane_q)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_TEXTURE_GEN_S);
            modes.push_back(GL_TEXTURE_GEN_T);

            // Not happy with turning all tex gen paramters on
            // as the OSG currently only supports 2D textures and therefore
            // only S and T will only be required, R&Q would be redundant...
            // So commenting out the following until OSG supports 3D textures.
            // I plan to revamp the OpenGL state management later so will
            // tidy up then.  Robert Osfield. Jan 2001.
            
            // The tidy up is now happening, but will have a think before
            // resolving the below parameters.

            modes.push_back(GL_TEXTURE_GEN_R);
            modes.push_back(GL_TEXTURE_GEN_Q);
        }

        virtual void apply(State& state) const;

        enum Mode {
            OBJECT_LINEAR  = GL_OBJECT_LINEAR,
            EYE_LINEAR     = GL_EYE_LINEAR,
            SPHERE_MAP     = GL_SPHERE_MAP,
            NORMAL_MAP     = GL_NORMAL_MAP_ARB,
            REFLECTION_MAP = GL_REFLECTION_MAP_ARB
        };

        inline void setMode( const Mode mode ) { _mode = mode; }

        const Mode getMode() const { return _mode; }

        enum Coord {
	  S, T, R, Q
        };

        void setPlane(const Coord which, const Vec4& plane);

        const Vec4& getPlane(const Coord which) const;

    protected :

        virtual ~TexGen( void );

        Mode _mode;

        /// additional texgen coefficents for GL_OBJECT_PLANE or GL_EYE_PLANE,
        Vec4 _plane_s, _plane_t, _plane_r, _plane_q;

};

}

#endif
