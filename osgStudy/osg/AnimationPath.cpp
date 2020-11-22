#include "AnimationPath.h"
#include "NodeVisitor.h"

bool osg::AnimationPath::getMatrix(double time, Matrix & matrix) const
{
	if (_timeKeyMap.empty())
	{
		return false;
	}
	TimeKeyMap::const_iterator theIter = _timeKeyMap.lower_bound(time);
	if (theIter == _timeKeyMap.begin())
	{
		theIter->second.getMatrix(matrix);
	}
	else if (theIter != _timeKeyMap.end())
	{
		TimeKeyMap::const_iterator it = theIter;
		--it;
		double delta_time = theIter->first - it->first;
		if (delta_time == 0.0)
		{
			it->second.getMatrix(matrix);
		}
		else
		{
			Key theKey;
			theKey.interpolate((time - it->first) / delta_time, it->second, theIter->second);
			theKey.getMatrix(matrix);
		}
	}
	else
	{
		_timeKeyMap.rbegin().base()->second.getMatrix(matrix);
	}
	return true;

}

bool osg::AnimationPath::getInverse(double time, Matrix & matrix) const
{
	if (_timeKeyMap.empty())
	{
		return false;
	}
	TimeKeyMap::const_iterator theIter = _timeKeyMap.lower_bound(time);
	if (theIter == _timeKeyMap.begin())
	{
		theIter->second.getInverse(matrix);
	}
	else if (theIter != _timeKeyMap.end())
	{
		TimeKeyMap::const_iterator it = theIter;
		--it;
		double delta_time = theIter->first - it->first;
		if (delta_time == 0.0)
		{
			it->second.getInverse(matrix);
		}
		else
		{
			Key theKey;
			theKey.interpolate((time - it->first) / delta_time, it->second, theIter->second);
			theKey.getInverse(matrix);
		}
	}
	else
	{
		_timeKeyMap.rbegin().base()->second.getInverse(matrix);
	}
	return true;
}

const bool osg::AnimationPath::computeLocalToWorldMatrix(Matrix & matrix, const Transform * transform, NodeVisitor * nv) const
{
	if (nv)
	{
		const osg::FrameStamp* fs = nv->getFrameStamp();
		if (fs)
		{
			osg::Matrix localMatrix;
			getMatrix(fs->getReferenceTime(), localMatrix);
			matrix.preMult(localMatrix);
			return true;
		}
	}
	return false;
}

const bool osg::AnimationPath::computeWorldToLocalMatrix(Matrix & matrix, const Transform * transform, NodeVisitor * nv) const
{
	if (nv)
	{
		const osg::FrameStamp* fs = nv->getFrameStamp();
		if (fs)
		{
			osg::Matrix localInverse;
			getMatrix(fs->getReferenceTime(), localInverse);
			matrix.postMult(localInverse);
			return true;
		}
	}
	return false;
}

void osg::AnimationPath::insert(double time, const Key & key)
{
	_timeKeyMap[time] = key;
}
