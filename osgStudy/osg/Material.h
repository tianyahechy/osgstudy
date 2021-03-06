//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_MATERIAL
#define OSG_MATERIAL 1

#include <osg/Vec4.h>
#include <osg/StateAttribute.h>

namespace osg {
/** Material - encapsulates OpenGL glMaterial state.*/
class SG_EXPORT Material : public StateAttribute
{

    public :


        Material();
        
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Material(const Material& mat,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(mat,copyop),
            _colorMode(mat._colorMode),
            _ambientFrontAndBack(mat._ambientFrontAndBack),
            _ambientFront(mat._ambientFront),
            _ambientBack(mat._ambientBack),
            _diffuseFrontAndBack(mat._diffuseFrontAndBack),
            _diffuseFront(mat._diffuseFront),
            _diffuseBack(mat._diffuseBack),
            _specularFrontAndBack(mat._specularFrontAndBack),
            _specularFront(mat._specularFront),
            _specularBack(mat._specularBack),
            _emissionFrontAndBack(mat._emissionFrontAndBack),
            _emissionFront(mat._emissionFront),
            _emissionBack(mat._emissionBack),
            _shininessFrontAndBack(mat._shininessFrontAndBack),
            _shininessFront(mat._shininessFront),
            _shininessBack(mat._shininessBack) {}

        META_StateAttribute(osg, Material, MATERIAL);
        
        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Material,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_colorMode)
            COMPARE_StateAttribute_Parameter(_ambientFrontAndBack)
            COMPARE_StateAttribute_Parameter(_ambientFront)
            COMPARE_StateAttribute_Parameter(_ambientBack)
            COMPARE_StateAttribute_Parameter(_diffuseFrontAndBack)
            COMPARE_StateAttribute_Parameter(_diffuseFront)
            COMPARE_StateAttribute_Parameter(_diffuseBack)
            COMPARE_StateAttribute_Parameter(_specularFrontAndBack)
            COMPARE_StateAttribute_Parameter(_specularFront)
            COMPARE_StateAttribute_Parameter(_specularBack)
            COMPARE_StateAttribute_Parameter(_emissionFrontAndBack)
            COMPARE_StateAttribute_Parameter(_emissionFront)
            COMPARE_StateAttribute_Parameter(_emissionBack)
            COMPARE_StateAttribute_Parameter(_shininessFrontAndBack)
            COMPARE_StateAttribute_Parameter(_shininessFront)
            COMPARE_StateAttribute_Parameter(_shininessBack)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            // Have to think about the role of _colorMode
            // in setting the colormaterial... also need to take the
            // color material enable/disable out of the the apply()...
            modes.push_back(GL_COLOR_MATERIAL);
        }

        virtual void apply(State& state) const;

        enum Face {
            FRONT           = GL_FRONT,
            BACK            = GL_BACK,
            FRONT_AND_BACK  = GL_FRONT_AND_BACK
        };

        enum ColorMode {
            AMBIENT = GL_AMBIENT,
            DIFFUSE = GL_DIFFUSE,
            SPECULAR = GL_SPECULAR,
            EMISSION = GL_EMISSION,
            AMBIENT_AND_DIFFUSE = GL_AMBIENT_AND_DIFFUSE,
            OFF            
        };

        inline void setColorMode(const ColorMode mode) { _colorMode = mode; }
        inline const ColorMode getColorMode() const { return _colorMode; }

        void setAmbient( const Face face, const Vec4& ambient );
        const Vec4& getAmbient(const Face face) const;
        inline const bool getAmbientFrontAndBack() const { return _ambientFrontAndBack; }

        void setDiffuse( const Face face, const Vec4& diffuse );
        const Vec4& getDiffuse(const Face face) const;
        inline const bool getDiffuseFrontAndBack() const { return _diffuseFrontAndBack; }

        /** Set specular value of specified face(s) of the material, 
          * valid specular[0..3] range is 0.0 to 1.0.*/
        void setSpecular( const Face face, const Vec4& specular );
        /** Get the specular value for specified face.*/
        const Vec4& getSpecular(const Face face) const;
        /** Get the whether specular values are equal for front and back faces.*/
        inline const bool getSpecularFrontAndBack() const { return _specularFrontAndBack; }

        /** Set emission value of specified face(s) of the material, 
          * valid emmison[0..3] range is 0.0 to 1.0.*/
        void setEmission( const Face face, const Vec4& emission );
        /** Get the emmsion value for specified face.*/
        const Vec4& getEmission(const Face face) const;
        /** Get the whether emission values are equal for front and back faces.*/
        inline const bool getEmissionFrontAndBack() const { return _emissionFrontAndBack; }

        /** Set shininess of specified face(s) of the material, valid shininess range is 0.0 to 128.0.*/
        void setShininess( const Face face, float shininess );
        /** Get the shininess value for specified face.*/
        const float getShininess(const Face face) const;
        /** Get the whether shininess values are equal for front and back faces.*/
        inline const bool getShininessFrontAndBack() const { return _shininessFrontAndBack; }
        
        /** Set the alpha value of ambient,diffuse,specular and emission colors, 
          * of specified face, to 1-transparency. Valid transparency range is 0.0 to 1.0.*/
        void setTransparency(const Face face,float trans);

        /** Set the alpha value of ambient,diffuse,specular and emission colors.
          * Valid transparency range is 0.0 to 1.0.*/
        void setAlpha(const Face face,float alpha);

    protected :

        virtual ~Material();

        ColorMode _colorMode;

        bool _ambientFrontAndBack;
        Vec4 _ambientFront;                          // r, g, b, w
        Vec4 _ambientBack;                           // r, g, b, w

        bool _diffuseFrontAndBack;
        Vec4 _diffuseFront;                          // r, g, b, w
        Vec4 _diffuseBack;                           // r, g, b, w

        bool _specularFrontAndBack;
        Vec4 _specularFront;                         // r, g, b, w
        Vec4 _specularBack;                          // r, g, b, w

        bool _emissionFrontAndBack;
        Vec4 _emissionFront;                         // r, g, b, w
        Vec4 _emissionBack;                          // r, g, b, w

        bool _shininessFrontAndBack;
        float  _shininessFront;                      // values 0 - 128.0
        float  _shininessBack;                       // values 0 - 128.0

};

}

#endif
