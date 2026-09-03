// ?bfmeBuildTurnArc@Path@@QAE_NPAVRva001BDFF0@@PAVPathNode@@PBUCoord3D@@PAUBfmeArcFlags@@HMH@Z
// partial score=0.31 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Path::bfmeBuildTurnArc — retail 0x003FFB50, 2139 bytes.
//
// Identity: Path thiscall, ret 0x1c, 7 stack args, bool. PathNode at arg2
// (waypoint id +0x20 == 0x7fffffff and m_nextOpti at +8). Sibling
// Path::appendNode(PathNode*) at 0x003FE250, Path dtor at 0x003FEB80.
//
// Callees (ILT): Inv_Sqrt 0x27a43, bfmeUnitAngle 0x22c6e (->0x3FD650 acos
// of unit-vector dot), Path::appendNode(PathNode*) 0x2b48b, appendNode
// (Coord3D*,layer) 0x3833e, validMovementPosition 0x3b359, isLinePassable
// 0x3d334, PathNode ctor 0x2c633, Coord3D::Add 0x2f66c, bfmeScaledCount
// 0x14015, operator new/delete, Rva001BDFF0::get 0x4582c,
// getSecondFloat 0x1eabf, Path::bfmeFinishTurnArc 0x21bf2 (->0x3FEBB0).
// TheAI 0x012EF214 +0xc pathfinder.
//
// Constants: 0.5, 0.0, +-PI/2, 2PI, PI/16, 3PI/2, -1.0.
// Prologue wall: retail sub esp,0x80; push ebp; push esi; esi=node; eax=next;
// ebp=this. Ours still 0x94 / edi=node / this spilled. Next session: force
// ebp=this and esi=node (definition order + don't sink next across the
// waypoint compare). Inline x87 of the first distance/normalize before
// adding more geometry.

#include <math.h>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3DBase
{
	Real x;
	Real y;
	Real z;
};

struct Coord3D : public Coord3DBase
{
	Coord3D &Add(const Coord3DBase &that);
};

class PathNode
{
public:
	PathNode(const Coord3D *pos, PathfindLayerEnum layer);

	PathNode *m_next;
	PathNode *m_prev;
	PathNode *m_nextOpti;
	Coord3D m_pos;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_waypointID;
};

class Object;
class Pathfinder
{
public:
	Bool validMovementPosition(const Coord3D *pos, PathfindLayerEnum layer,
		UnsignedInt surfaces, Object *obj);
	Int isLinePassable(Object *obj, Int zone, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end, Int a, Int b, Int c);
};

class AI
{
public:
	Pathfinder *pathfinder(void) const { return m_pathfinder; }

private:
	unsigned char m_unknown[0x0c];
	Pathfinder *m_pathfinder;
};

extern "C" AI *TheAIParseDefinitionAI;

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float a);
};

class Rva001B59FloatView
{
public:
	float getSecondFloat(void) const;
};

class Rva001BDFF0
{
public:
	int get(void);
};

struct BfmeArcFlags
{
	Bool useChecks;
	Bool flip;
	char pad[2];
	Real maxRadius;
	Bool skipNewNode;
};

int __stdcall bfmeScaledCount(Real first, Real second);
Real __cdecl bfmeUnitAngle(const Coord3D *a, const Coord3D *b);

static const Real kHalf = 0.5f;
static const Real kZero = 0.0f;
static const Real kPi = 3.14159274f;
static const Real kTwoPi = 6.28318548f;
static const Real kPiOver2 = 1.57079637f;
static const Real kNegPiOver2 = -1.57079637f;
static const Real kPiOver16 = 0.196349546f;
static const Real kThreePiOver2 = 4.712389f;
static const Int kInvalidWaypoint = 0x7fffffff;

class Path
{
public:
	Bool bfmeBuildTurnArc(Rva001BDFF0 *obj, PathNode *node, const Coord3D *facing,
		BfmeArcFlags *flags, Int surfaces, Real signLimit, Int extra);
	void appendNode(const PathNode *source);
	void appendNode(const Coord3D *pos, PathfindLayerEnum layer);
	void bfmeFinishTurnArc(PathNode *created, PathNode *node, PathNode *next, Real radius);

private:
	void *m_vtable;
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
};

#define BFME_NORMALIZE(v) \
	do { \
		Real _len2 = (v).x * (v).x + (v).y * (v).y + (v).z * (v).z; \
		if (_len2 != kZero) { \
			Real _inv = WWMath::Inv_Sqrt(_len2); \
			(v).x *= _inv; \
			(v).y *= _inv; \
			(v).z *= _inv; \
		} \
	} while (0)

// ?bfmeBuildTurnArc@Path@@QAE_NPAVRva001BDFF0@@PAVPathNode@@PBUCoord3D@@PAUBfmeArcFlags@@HMH@Z
Bool Path::bfmeBuildTurnArc(Rva001BDFF0 *obj, PathNode *inNode, const Coord3D *facing,
	BfmeArcFlags *flags, Int surfaces, Real signLimit, Int extra)
{
	PathNode *node = inNode;
	PathNode *next = node->m_nextOpti;
	Path *self = this;
	if (node->m_waypointID == kInvalidWaypoint && next != 0)
	{
		Coord3D *nodePos = &node->m_pos;
		Real radius = flags->maxRadius;
		Coord3D dest = next->m_pos;

		Real dx = dest.x - nodePos->x;
		Real dy = dest.y - nodePos->y;
		Real dz = dest.z - nodePos->z;
		Real dist = (Real)sqrt(dx * dx + dy * dy + dz * dz) * kHalf;
		if (dist < radius)
			radius = dist;

		Coord3D face;
		face.x = facing->x;
		face.y = facing->y;
		face.z = facing->z;
		BFME_NORMALIZE(face);

		Coord3D delta;
		delta.x = dest.x - nodePos->x;
		delta.y = dest.y - nodePos->y;
		delta.z = dest.z - nodePos->z;
		BFME_NORMALIZE(delta);

		Int sign = 1;
		Real cross = delta.y * face.x - face.y * delta.x;
		if (cross <= kZero)
			sign = -1;
		Real signFloat = (Real)sign;

		Real ang = bfmeUnitAngle(&face, &delta);
		if (ang < kPiOver16 || signFloat > signLimit)
		{
			if (!flags->useChecks)
				self->appendNode(node);
			return true;
		}

		Bool keepPos = true;
		if (flags->flip)
		{
			if (sign > 0)
			{
				flags->flip = false;
				if (flags->useChecks)
					return false;
			}
			else
			{
				signFloat = -signFloat;
			}
		}

		Real turn = kPiOver2;
		if (signFloat < kZero)
		{
			keepPos = false;
			turn = kNegPiOver2;
		}

		if (!flags->useChecks)
			self->appendNode(node);

		Real s = (Real)sin(turn);
		Real c = (Real)cos(turn);
		Coord3D perp;
		perp.x = face.x * c - face.y * s;
		perp.y = face.y * c + face.x * s;
		perp.x *= radius;
		perp.y *= radius;

		Coord3D pivot;
		pivot.x = nodePos->x + perp.x;
		pivot.y = nodePos->y + perp.y;
		pivot.z = kZero;

		Coord3D toDest;
		toDest.x = dest.x - pivot.x;
		toDest.y = dest.y - pivot.y;
		toDest.z = dest.z;

		Real negTurn = -turn;
		Real s2 = (Real)sin(negTurn);
		Real c2 = (Real)cos(negTurn);
		Coord3D rot;
		rot.x = toDest.x * c2 - toDest.y * s2;
		rot.y = toDest.y * c2 + toDest.x * s2;
		rot.z = toDest.z;
		BFME_NORMALIZE(rot);

		rot.x *= radius;
		rot.y *= radius;

		Coord3D farPt;
		farPt.x = rot.x + pivot.x;
		farPt.y = rot.y + pivot.y;
		farPt.z = kZero;

		Coord3D side = perp;
		side.x *= -1.0f;
		side.y *= -1.0f;
		BFME_NORMALIZE(side);

		Coord3D face2 = rot;
		BFME_NORMALIZE(face2);

		Real ang2 = bfmeUnitAngle(&face2, &side);
		if (ang2 == signFloat)
			turn = kTwoPi - turn;

		Coord3D fromFar;
		fromFar.x = dest.x - farPt.x;
		fromFar.y = dest.y - farPt.y;
		fromFar.z = kZero;
		BFME_NORMALIZE(fromFar);

		Real ang3 = bfmeUnitAngle(&face2, &fromFar);
		ang = ang + ang3;
		if (flags->flip)
			ang = kTwoPi - ang;

		if (ang > kThreePiOver2)
		{
			ang = ang - kTwoPi;
			if (ang < kZero)
				ang = kZero;
		}

		Int count = bfmeScaledCount(ang, radius);
		if (count >= 2)
		{
			if (!keepPos)
				ang = -ang;
			Real step = ang / (Real)count;
			Int i = 1;
			Object *objPtr = (Object *)obj;
			do
			{
				Real a = (Real)i * step;
				Real sa = (Real)sin(a);
				Real ca = (Real)cos(a);
				Coord3D p;
				p.x = perp.x * ca - perp.y * sa + pivot.x;
				p.y = perp.y * ca + perp.x * sa + pivot.y;
				p.z = nodePos->z;

				if (flags->useChecks)
				{
					if (!TheAIParseDefinitionAI->pathfinder()->validMovementPosition(
							&p, node->m_layer, (UnsignedInt)surfaces, objPtr))
						return false;
					if (i == count)
					{
						if (!TheAIParseDefinitionAI->pathfinder()->isLinePassable(
								objPtr, surfaces, node->m_layer, &p, &dest, extra, 0, 0))
							return false;
					}
				}
				else
				{
					self->appendNode(&p, node->m_layer);
					nodePos->x = p.x;
					nodePos->y = p.y;
					nodePos->z = p.z;
				}
				++i;
			} while (i <= count);
		}

		if (!flags->useChecks && !flags->skipNewNode)
		{
			PathNode *created = (PathNode *)operator new(0x24);
			if (created)
				created->PathNode::PathNode(nodePos, LAYER_GROUND);
			dest.Add(*nodePos);
			dest.x *= kHalf;
			dest.y *= kHalf;
			dest.z *= kHalf;
			nodePos->x = dest.x;
			nodePos->y = dest.y;
			nodePos->z = dest.z;

			int view = obj->get();
			if (view)
				radius = ((Rva001B59FloatView *)view)->getSecondFloat();

			self->bfmeFinishTurnArc(created, node, next, radius);
			if (created)
				operator delete(created);
		}
		return true;
	}

	if (!flags->useChecks)
		self->appendNode(node);
	return true;
}
