//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_ALPHAFUNC
#define OSG_ALPHAFUNC 1

#include <osg/StateAttribute.h>

namespace osg {

	/** Encapsulate OpenGL glAlphaFunc.
	*/
	class SG_EXPORT AlphaFunc : public StateAttribute
	{
	public:


		AlphaFunc();

		/** Copy constructor using CopyOp to manage deep vs shallow copy.*/
		AlphaFunc(const AlphaFunc& af, const CopyOp& copyop = CopyOp::SHALLOW_COPY) :
			StateAttribute(af, copyop),
			_comparisonFunc(af._comparisonFunc),
			_referenceValue(af._referenceValue) {}

		META_StateAttribute(osg, AlphaFunc, ALPHAFUNC);

		/** return -1 if *this < *rhs, 0 if *this==*rhs, 1 if *this>*rhs.*/
		virtual int compare(const StateAttribute& sa) const
		{
			// check the types are equal and then create the rhs variable
			// used by the COMPARE_StateAttribute_Paramter macro's below.
			COMPARE_StateAttribute_Types(AlphaFunc, sa)

				// compare each paramter in turn against the rhs.
				COMPARE_StateAttribute_Parameter(_comparisonFunc)
				COMPARE_StateAttribute_Parameter(_referenceValue)

				return 0; // passed all the above comparison macro's, must be equal.
		}

		virtual void getAssociatedModes(std::vector<GLMode>& modes) const
		{
			modes.push_back(GL_ALPHA_TEST);
		}

		enum ComparisonFunction {
			NEVER = GL_NEVER,
			LESS = GL_LESS,
			EQUAL = GL_EQUAL,
			LEQUAL = GL_LEQUAL,
			GREATER = GL_GREATER,
			NOTEQUAL = GL_NOTEQUAL,
			GEQUAL = GL_GEQUAL,
			ALWAYS = GL_ALWAYS
		};

		inline void setFunction(const ComparisonFunction func, const float ref)
		{
			_comparisonFunc = func;
			_referenceValue = ref;
		}

		inline const ComparisonFunction getFunction() const { return _comparisonFunc; }

		inline const float getReferenceValue() const { return _referenceValue; }

		virtual void apply(State& state) const;

	protected:

		virtual ~AlphaFunc();

		ComparisonFunction _comparisonFunc;
		float _referenceValue;

	};

}

#endif
#pragma once
