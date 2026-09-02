// ?insertY@W3DRoadBufferInsertYShim@@QAE_NVVector2@@HM@Z
// partial score=0.86 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWDebug
#include "vector2.h"
#include "wwmath.h"
#include <math.h>

#define PI WWMATH_PI

typedef int Int;
typedef float Real;
typedef bool Bool;

struct TRoadPt
{
	Vector2 loc;
	Vector2 top;
	Vector2 bottom;
	Int count;
	Bool last;
	Bool multi;
	Bool isAngled;
	Bool isJoin;
};

enum TCorner
{
	SEGMENT,
	CURVE,
	TEE,
	FOUR_WAY,
	THREE_WAY_Y,
	THREE_WAY_H,
	THREE_WAY_H_FLIP,
	ALPHA_JOIN,
	NUM_JOINS
};

struct RoadSegment
{
	TRoadPt m_pt1;
	TRoadPt m_pt2;
	Real m_curveRadius;
	TCorner m_type;
	Real m_scale;
	Real m_widthInTexture;
	Int m_uniqueID;
	unsigned char m_pad[0xBC - 0x54];
};

class W3DRoadBuffer
{
public:
	void offsetY(TRoadPt *pc1, TRoadPt *pc2, TRoadPt *pc3, Vector2 loc, Vector2 upVector, Real widthInTexture);
};

static Int xpSign(const Vector2 &v1, const Vector2 &v2)
{
	Real xpdct = v1.X * v2.Y - v1.Y * v2.X;
	if (xpdct < 0)
		return -1;
	if (xpdct > 0)
		return 1;
	return 0;
}

class W3DRoadBufferInsertYShim
{
public:
	Bool insertY(Vector2 loc, Int index1, Real scale);

	void *m_roadTypes;
	RoadSegment *m_roads;
	Int m_numRoads;
	Bool m_initialized;
	unsigned char m_pad[0x38 - 0x0D];
	Int m_maxRoadSegments;
};

Bool W3DRoadBufferInsertYShim::insertY(Vector2 loc, Int index1, Real scale)
{
	if (!m_initialized)
		return false;

	TRoadPt *pr1 = NULL;
	TRoadPt *pr2 = NULL;
	TRoadPt *pr3 = NULL;
	TRoadPt *pc1 = NULL;
	TRoadPt *pc2 = NULL;
	TRoadPt *pc3 = NULL;

	if (m_roads[index1].m_pt1.loc == loc) {
		pr1 = &m_roads[index1].m_pt2;
		pc1 = &m_roads[index1].m_pt1;
	} else {
		pr1 = &m_roads[index1].m_pt1;
		pc1 = &m_roads[index1].m_pt2;
	}
	Int i;
	for (i = index1 + 1; i < m_numRoads; i++) {
		if (m_roads[i].m_pt1.loc == loc) {
			m_roads[i].m_pt1.count = -2;
			if (pr2 == NULL) {
				pr2 = &m_roads[i].m_pt2;
				pc2 = &m_roads[i].m_pt1;
			} else {
				pr3 = &m_roads[i].m_pt2;
				pc3 = &m_roads[i].m_pt1;
			}
		}
		if (m_roads[i].m_pt2.loc == loc) {
			m_roads[i].m_pt2.count = -2;
			if (pr2 == NULL) {
				pr2 = &m_roads[i].m_pt1;
				pc2 = &m_roads[i].m_pt2;
			} else {
				pr3 = &m_roads[i].m_pt1;
				pc3 = &m_roads[i].m_pt2;
			}
		}
	}
	if (pr2 == NULL || pr3 == NULL) {
		return false;
	}

	Vector2 v1 = pr1->loc - loc;
	v1.Normalize();
	Vector2 v2 = pr2->loc - loc;
	v2.Normalize();
	Vector2 v3 = pr3->loc - loc;
	v3.Normalize();

	Bool do12 = false;
	Bool do13 = false;
	Bool do32 = false;

	Real dot12 = v1.Dot_Product(v1, v2);
	Real dot13 = v1.Dot_Product(v1, v3);
	Real dot32 = v1.Dot_Product(v3, v2);
	Real score12 = 2.0f;
	Real score13 = 2.0f;
	Real score32 = 2.0f;

	const Real cos30 = 0.866f;
	const Real cos45 = 0.707f;

	if (dot12 < (-cos30))
		return false;
	if (dot13 < (-cos30))
		return false;
	if (dot32 < (-cos30))
		return false;

	Int s1 = 0;
	Int s2 = xpSign(v1, v2);
	Int s3 = xpSign(v1, v3);

	if (s2 != s3 && (s2 + s3 == 0)) {
		Vector2 v1_90(-v1.Y, v1.X);
		if (xpSign(v1_90, v2) == 1 && xpSign(v1_90, v3) == 1) {
			do32 = true;
			score32 = fabs(dot12 + cos45) + fabs(dot13 + cos45);
		}
	}

	s1 = xpSign(v3, v1);
	s2 = xpSign(v3, v2);
	if (s2 != s1 && (s2 + s1 == 0)) {
		Vector2 v3_90(-v3.Y, v3.X);
		if (xpSign(v3_90, v2) == 1 && xpSign(v3_90, v1) == 1) {
			do12 = true;
			score12 = fabs(dot13 + cos45) + fabs(dot32 + cos45);
		}
	}

	s1 = xpSign(v2, v1);
	s3 = xpSign(v2, v3);
	if (s3 != s1 && (s3 + s1 == 0)) {
		Vector2 v2_90(-v2.Y, v2.X);
		if (xpSign(v2_90, v3) == 1 && xpSign(v2_90, v1) == 1) {
			do13 = true;
			score13 = fabs(dot12 + cos45) + fabs(dot32 + cos45);
		}
	}

	if (score12 < score13) {
		do13 = false;
		if (score12 < score32) {
			do32 = false;
		} else {
			do12 = false;
		}
	} else {
		do12 = false;
		if (score13 < score32) {
			do32 = false;
		} else {
			do13 = false;
		}
	}

	Vector2 upVector;
	if (do12) {
		upVector = v3;
	} else if (do13) {
		upVector = v2;
	} else if (do32) {
		upVector = v1;
	} else {
		return false;
	}

	Real angle = -(PI / 2);
	upVector.Normalize();
	upVector *= 0.5 * scale;
	Vector2 teeVector(upVector);
	teeVector.Rotate(angle);

	if (do12) {
		Int s = xpSign(v3, v1);
		if (s == -1) {
			((W3DRoadBuffer *)this)->offsetY(pc1, pc2, pc3, loc, upVector, m_roads[index1].m_widthInTexture);
		} else {
			((W3DRoadBuffer *)this)->offsetY(pc2, pc1, pc3, loc, upVector, m_roads[index1].m_widthInTexture);
		}
	}
	if (do13) {
		Int s = xpSign(v2, v1);
		if (s == -1) {
			((W3DRoadBuffer *)this)->offsetY(pc1, pc3, pc2, loc, upVector, m_roads[index1].m_widthInTexture);
		} else {
			((W3DRoadBuffer *)this)->offsetY(pc3, pc1, pc2, loc, upVector, m_roads[index1].m_widthInTexture);
		}
	}
	if (do32) {
		Int s = xpSign(v1, v3);
		if (s == -1) {
			((W3DRoadBuffer *)this)->offsetY(pc3, pc2, pc1, loc, upVector, m_roads[index1].m_widthInTexture);
		} else {
			((W3DRoadBuffer *)this)->offsetY(pc2, pc3, pc1, loc, upVector, m_roads[index1].m_widthInTexture);
		}
	}

	pc1->last = true;
	pc1->count = 0;
	pc2->last = true;
	pc2->count = 0;
	pc3->last = true;
	pc3->count = 0;

	if (m_numRoads >= m_maxRoadSegments)
		return false;
	m_roads[m_numRoads].m_pt1.loc.Set(loc);
	m_roads[m_numRoads].m_pt2.loc.Set(loc + teeVector);
	m_roads[m_numRoads].m_pt1.last = true;
	m_roads[m_numRoads].m_pt2.last = true;
	m_roads[m_numRoads].m_scale = m_roads[index1].m_scale;
	m_roads[m_numRoads].m_widthInTexture = m_roads[index1].m_widthInTexture;
	m_roads[m_numRoads].m_pt1.count = -3;
	m_roads[m_numRoads].m_type = THREE_WAY_Y;
	m_roads[m_numRoads].m_uniqueID = m_roads[index1].m_uniqueID;
	m_numRoads++;

	return true;
}
