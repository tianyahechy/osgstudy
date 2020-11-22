#pragma once
#include "GL.h"
#include "StateAttribute.h"

namespace osg
{
	class SG_EXPORT ShadeModel : public StateAttribute
	{
	public:
		enum Mode
		{
			FLAT = GL_FLAT,
			SMOOTH = GL_SMOOTH
		};

	protected:
		virtual ~ShadeModel();
		Mode _mode;

	public:
		ShadeModel();

		ShadeModel(const ShadeModel& sm, const CopyOp& copyop = CopyOp::SHALLOW_COPY) :
			StateAttribute(sm, copyop)
		{
			_mode = sm._mode;
		}
		META_StateAttribute(osg, ShadeModel, SHADEMODEL);
		virtual int compare(const StateAttribute& sa) const
		{
			COMPARE_StateAttribute_Types(ShadeModel, sa);
			COMPARE_StateAttribute_Parameter(_mode);
			return 0;
		}

		inline void setMode(const Mode mode)
		{
			_mode = mode;
		}

		inline const Mode getMode() const
		{
			return _mode;
		}
		virtual void apply(State& state) const;
	};
}