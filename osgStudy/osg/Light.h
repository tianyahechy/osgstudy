//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_LIGHT
#define OSG_LIGHT 1

#include <osg/StateAttribute.h>
#include <osg/Vec3.h>
#include <osg/Vec4.h>

namespace osg {

/** Light state class which encapsulates OpenGL glLight() functionality.*/
class SG_EXPORT Light : public StateAttribute
{
    public :

        Light();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Light(const Light& light,const CopyOp& copyop=CopyOp::SHALLOW_COPY):
            StateAttribute(light,copyop),
            _lightnum(light._lightnum),
            _ambient(light._ambient),
            _diffuse(light._diffuse),
            _specular(light._specular),
            _position(light._position),
            _direction(light._direction),
            _constant_attenuation(light._constant_attenuation),
            _linear_attenuation(light._linear_attenuation),
            _quadratic_attenuation(light._quadratic_attenuation),
            _spot_exponent(light._spot_exponent),
            _spot_cutoff(light._spot_cutoff) {}
        
        META_StateAttribute(osg, Light, (Type)(LIGHT_0+_lightnum));

        /** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
        virtual int compare(const StateAttribute& sa) const
        {
            // check the types are equal and then create the rhs variable
            // used by the COMPARE_StateAttribute_Paramter macro's below.
            COMPARE_StateAttribute_Types(Light,sa)

            // compare each paramter in turn against the rhs.
            COMPARE_StateAttribute_Parameter(_lightnum)
            COMPARE_StateAttribute_Parameter(_ambient)
            COMPARE_StateAttribute_Parameter(_diffuse)
            COMPARE_StateAttribute_Parameter(_specular)
            COMPARE_StateAttribute_Parameter(_position)
            COMPARE_StateAttribute_Parameter(_direction)
            COMPARE_StateAttribute_Parameter(_constant_attenuation)
            COMPARE_StateAttribute_Parameter(_linear_attenuation)
            COMPARE_StateAttribute_Parameter(_quadratic_attenuation)
            COMPARE_StateAttribute_Parameter(_spot_exponent)
            COMPARE_StateAttribute_Parameter(_spot_cutoff)

            return 0; // passed all the above comparison macro's, must be equal.
        }

        virtual void getAssociatedModes(std::vector<GLMode>& modes) const 
        {
            modes.push_back(GL_LIGHT0+_lightnum);
        }

        /** Set which OpenGL light to operate on.*/
        void setLightNum(const int num) { _lightnum = num; }
        
        /** Get which OpenGL light this osg::Light operates on.*/
        const int getLightNum() const { return _lightnum; }

	/** Set the ambient component of the light. */
        inline void setAmbient( const Vec4& ambient ) { _ambient = ambient; }

	/** Get the ambient component of the light. */
        inline const Vec4& getAmbient() const { return _ambient; }

	/** Set the diffuse component of the light. */
        inline void setDiffuse( const Vec4& diffuse ) { _diffuse = diffuse; }

	/** Get the diffuse component of the light. */
        inline const Vec4& getDiffuse() const { return _diffuse; }

	/** Set the specular component of the light. */
        inline void setSpecular( const Vec4& specular ) { _specular = specular; }

	/** Get the specular component of the light. */
        inline const Vec4& getSpecular() const { return _specular; }

	/** Set the position of the light. */	
        inline void setPosition( const Vec4& position ) { _position = position; }

	/** Get the position of the light. */	
        inline const Vec4& getPosition() const { return _position; }

	/** Set the direction of the light. */	
        inline void setDirection( const Vec3& direction ) { _direction = direction; }

	/** Get the direction of the light. */	
        inline const Vec3& getDirection() const { return _direction; }

	/** Set the constant attenuation of the light. */
        inline void setConstantAttenuation( const float constant_attenuation )     { _constant_attenuation = constant_attenuation; }

	/** Get the constant attenuation of the light. */
        inline const float getConstantAttenuation() const { return _constant_attenuation; }

	/** Set the linear attenuation of the light. */
        inline void setLinearAttenuation ( const float linear_attenuation )        { _linear_attenuation = linear_attenuation; }

	/** Get the linear attenuation of the light. */
        inline const float getLinearAttenuation () const { return _linear_attenuation; }

	/** Set the quadratic attenuation of the light. */
        inline void setQuadraticAttenuation ( const float quadratic_attenuation )  { _quadratic_attenuation = quadratic_attenuation; }

	/** Get the quadratic attenuation of the light. */
        inline const float getQuadraticAttenuation()  const { return _quadratic_attenuation; }

	/** Set the spot exponent of the light. */
        inline void setSpotExponent( const float spot_exponent )                   { _spot_exponent = spot_exponent; }

	/** Get the spot exponent of the light. */
        inline const float getSpotExponent() const { return _spot_exponent; }

	/** Set the spot cutoff of the light. */
        inline void setSpotCutoff( const float spot_cutoff )                       { _spot_cutoff = spot_cutoff; }

	/** Get the spot cutoff of the light. */
        inline const float getSpotCutoff() const                                   { return _spot_cutoff; }

	/**
	 * Capture the lighting settings of the current OpenGL state
	 * and store them in this object.
	 */
        void captureLightState();

	/** Apply the light's state to the OpenGL state machine. */
        virtual void apply(State& state) const;

    protected :
    
        virtual ~Light();

	/** Initialize the light's settings with some decent defaults. */
        void init();

        int _lightnum;                           // OpenGL light number

        Vec4 _ambient;                           // r, g, b, w
        Vec4 _diffuse;                           // r, g, b, w
        Vec4 _specular;                          // r, g, b, w
        Vec4 _position;                          // x, y, z, w
        Vec3 _direction;                         // x, y, z
        float _constant_attenuation;             // constant
        float _linear_attenuation;               // linear
        float _quadratic_attenuation;            // quadratic
        float _spot_exponent;                    // exponent
        float _spot_cutoff;                      // spread
};

}

#endif