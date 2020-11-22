#pragma once
#include <osg/Matrix.h>
#include <osg/Quat.h>
#include <osg/Transform.h>

#include <map>

namespace osg
{
	class SG_EXPORT AnimationPath : public Transform::ComputeTransformCallback
	{
	public:
		struct Key
		{
			osg::Vec3 _position;
			osg::Quat _rotation;
			osg::Vec3 _scale;
			Key(const osg::Vec3& position, const osg::Quat& rotation, const osg::Vec3& scale)
			{
				_position = position;
				_rotation = rotation;
				_scale = scale;
			}

			inline void interpolate(const float ratio, const Key& first, const Key& second)
			{
				float one_minus_ratio = 1.0f - ratio;
				_position = first._position * one_minus_ratio + second._position * ratio;
				_rotation.slerp(ratio, first._rotation, second._rotation);
				_scale = first._scale * one_minus_ratio + second._scale * ratio;
			}

			inline void getMatrix(Matrix& matrix) const
			{
				matrix.makeScale(_scale);
				matrix.postMult(_rotation.getMatrix());
				matrix.postMult(osg::Matrix::translate(_position));
			}

			inline void getInverse(Matrix& matrix) const
			{
				matrix.makeScale(1.0f / _scale.x(), 1.0f / _scale.y(), 1.0f / _scale.z() );
				matrix.postMult(_rotation.inverse.getMatrix());
				matrix.postMult(osg::Matrix::translate(-_position));
			}
		};
	protected:
		virtual ~AnimationPath() {}
		typedef std::map<double, Key> TimeKeyMap;
		TimeKeyMap _timeKeyMap;
	public:
		AnimationPath() {}
		virtual bool getMatrix(double time, Matrix& matrix) const;
		virtual bool getInverse(double time, Matrix& matrix) const;
		virtual const bool computeLocalToWorldMatrix(Matrix& matrix, const Transform* transform, NodeVisitor* nv) const;
		virtual const bool computeWorldToLocalMatrix(Matrix& matrix, const Transform* transform, NodeVisitor* nv) const;

		void insert(double time, const Key& key);
	};
}