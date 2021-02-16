#pragma once
#include <osg/NodeVisitor.h>
#include <osg/LineSegment.h>
#include <osg/Geode.h>
#include <osg/Matrix.h>

#include "Export.h"
#include <map>
#include <set>
#include <vector>

namespace osgUtil
{
	class OSGUTIL_EXPORT Hit
	{
	public:
		typedef std::vector<int> vecIndexList;
		float _ratio;
		osg::ref_ptr<osg::LineSegment> _originalLineSegment;
		osg::ref_ptr<osg::LineSegment> _localLineSegment;
		osg::NodePath _nodePath;
		osg::ref_ptr<osg::Geode> _geode;
		osg::ref_ptr<osg::Drawable> _drawable;
		osg::ref_ptr<osg::Matrix> _matrix;
		osg::ref_ptr < osg::Matrix> _inverse;
		vecIndexList _vecIndexList;
		int _primitiveIndex;
		osg::Vec3 _intersectPoint;
		osg::Vec3 _intersectNormal;


		Hit();
		Hit(const Hit& hit);
		~Hit();

		Hit& operator = (const Hit& hit);
		bool operator < (const Hit& hit) const
		{
			if (_originalLineSegment < hit._originalLineSegment)
			{
				return true;
			}

			if (_originalLineSegment > hit._originalLineSegment)
			{
				return false;
			}
			return _ratio < hit._ratio;
		}

		const osg::Vec3& getLocalIntersectPoint() const
		{
			return _intersectPoint;
		}
		const osg::Vec3& getLocalIntersectNormal() const
		{
			return _intersectNormal;
		}
		const osg::Vec3 getWorldIntersectPoint() const
		{
			if (_matrix.valid())
			{
				return _intersectPoint * (*_matrix);
			}
			return _intersectPoint;
		}
		const osg::Vec3 getWorldIntersectNormal() const;
	};

	class OSGUTIL_EXPORT IntersectVisitor : public osg::NodeVisitor
	{
	public:
		IntersectVisitor();
		virtual ~IntersectVisitor();
		void reset();

		void addLineSegment(osg::LineSegment * seg);
		enum HitReportingMode
		{
			ONLY_NEAREST_HIT,
			ALL_HITS
		};
		HitReportingMode _hitReportingMode;
		void setHitReportingMode(HitReportingMode hrm)
		{
			_hitReportingMode = hrm;
		}
		HitReportingMode getHitReportingMode()
		{
			return _hitReportingMode;
		}
		typedef std::vector<Hit> HitList;
		typedef std::map<osg::LineSegment*, HitList> LineSegmentHitListMap;
		LineSegmentHitListMap _segHitList;
		HitList& getHitList(osg::LineSegment* seg)
		{
			return _segHitList[seg];
		}
		int getNumHits(osg::LineSegment* seg)
		{
			return _segHitList[seg].size();
		}
		bool hits();
		virtual void apply(osg::Node&);
		virtual void apply(osg::Geode& node);
		virtual void apply(osg::Billboard& node);

		virtual void apply(osg::Group& node);
		virtual void apply(osg::Transform& node);
		virtual void apply(osg::Switch& node);
		virtual void apply(osg::LOD& node);

	protected:
		class IntersectState : public osg::Referenced
		{
		public:
			IntersectState();
			osg::ref_ptr<osg::Matrix> _matrix;
			osg::ref_ptr<osg::Matrix> _inverse;
			typedef std::pair<osg::ref_ptr<osg::LineSegment>, osg::ref_ptr<osg::LineSegment>> LineSegmentPair;
			typedef std::vector<LineSegmentPair> LineSegmentList;
			LineSegmentList _segList;

			typedef unsigned int LineSegmentmentMask;
			typedef std::vector<LineSegmentmentMask> LineSegmentmentMaskStack;
			LineSegmentmentMaskStack _segmentMaskStack;
			
			bool isCulled(const osg::BoundingSphere& bs, LineSegmentmentMask& segMaskOut);
			bool isCulled(const osg::BoundingBox& bb, LineSegmentmentMask& segMaskOut);

			void addLineSegmentPair(osg::LineSegment* first, osg::LineSegment* second)
			{
				_segList.push_back(LineSegmentPair(first, second));
			}
		protected:
			~IntersectState();

		};

		bool intersect(osg::Drawable& gset);
		void pushMatrix(const osg::Matrix& matrix);
		void popMatrix();

		bool enterNode(osg::Node& node);
		void leaveNode();

		typedef std::vector<osg::ref_ptr<IntersectState>> IntersectStateStack;
		IntersectStateStack _intersectStateStack;
		osg::NodePath _nodePath;
	};
}

