// ?checkSpecial@AIGroup@@QAE_NPBUCoord3D@@H@Z
// partial score=0.36 date=2026-09-22
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::checkSpecial, retail 0x00154F00, 966 bytes.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct Coord2D
{
	Real x;
	Real y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

enum KindOfType
{
	KINDOF_08 = 8,
	KINDOF_09 = 9,
	KINDOF_10 = 10,
	KINDOF_11 = 11
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const;

	unsigned char m_unmodelled_000[4];
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

class Thing
{
public:
	virtual ~Thing();
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}
	Bool isKindOf(KindOfType type) const;

protected:
	ThingTemplate *m_template;
};

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x1B8];
	UnsignedInt m_validLocomotorSurfaces;
};

class Object : public Thing
{
public:
	const Coord3D *getPosition(void) const { return &m_position; }
	UnsignedInt getDisabledMask(void) const { return m_disabledMask; }
	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }
	Int getLayer(void) const;

private:
	unsigned char m_unmodelled_008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unmodelled_044[0x1A4 - 0x44];
	UnsignedInt m_disabledMask;
	unsigned char m_unmodelled_1A8[0x204 - 0x1A8];
	AIUpdateInterface *m_ai;
};

class PathNode
{
public:
	unsigned char m_unmodelled_000[8];
	PathNode *m_next;
	Coord3D m_position;
};

class Path
{
public:
	unsigned char m_unmodelled_000[4];
	PathNode *m_head;
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
	Bool lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
	Path *findGroundPath(const Coord3D *from, const Coord3D *to,
		Int pathRadius, Int crusher);
};

#pragma comment(linker, "/alternatename:?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0HH@Z=?findGroundPath@Pathfinder@@QAEPAVPath@@PBUCoord3D@@0H_N@Z")

class TAiData
{
public:
	unsigned char m_unmodelled_000[0x6C];
	Real m_minDistanceForGroup;
};

class AI
{
public:
	unsigned char m_unmodelled_000[0x0C];
	Pathfinder *m_pathfinder;

	unsigned char m_unmodelled_010[4];
	TAiData *m_aiData;

	unsigned char m_unmodelled_018[0x70 - 0x18];
	Real m_field70;

	Object *findEnemyNear(Object *obj, Real range, Int a, Int b, Int c);
};

class Rva00150700Owner
{
public:
	unsigned char m_unmodelled_000[0x18];
	Path *m_groundPath;
	void reset(void);
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual Bool slot47(const Coord3D *pos) = 0;
};

class AIGroup
{
public:
	Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	void recompute(void);
	Bool checkSpecial(const Coord3D *pos, Int a);

private:
	unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;
	UnsignedInt m_memberListSize;
	Real m_speed;
	Bool m_dirty;
	unsigned char m_unmodelled_011[3];
	UnsignedInt m_id;
	Path *m_groundPath;
	Coord3D m_center;
	Coord3D m_destination;
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;
extern const Real g_bfmeK1266B;
extern const Real g_bfmeDirectionWeight1285;

Bool AIGroup::checkSpecial(const Coord3D *pos, Int a)
{
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, pos);
	if (layer == LAYER_GROUND && TheTerrainLogic->slot47(pos))
		return false;

	if (m_dirty)
		recompute();

	Coord3D center;
	Coord2D min;
	Coord2D max;
	getMinMaxAndCenter(&min, &max, &center);

	Real distance = TheAI->m_aiData->m_minDistanceForGroup * g_bfmeK1266B;
	distance *= distance;
	m_center = center;
	m_destination = *pos;
	Real centerDistance = distance * g_bfmeDirectionWeight1285;

	Object *volatile closest = 0;
	Object *kind8 = 0;
	Object *kind9Or11 = 0;
	Object *kind10 = 0;
	_STL::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		TheAI->m_pathfinder->removeGoal(obj);
		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->getAIUpdateInterface() == 0)
			continue;
		const ThingTemplate *tmpl = obj->getTemplate();
		if (tmpl != 0 && (tmpl->m_kindof[0] & 0x1000) != 0)
			continue;
		if (obj->isKindOf(KINDOF_08))
		{
			kind8 = obj;
			goto measure;
		}
		if (obj->isKindOf(KINDOF_10))
		{
			kind10 = obj;
			goto measure;
		}
		if (!obj->isKindOf(KINDOF_09) && !obj->isKindOf(KINDOF_11))
			goto measure;
		kind9Or11 = obj;

	measure:
		const Coord3D *unitPos = obj->getPosition();
		Real dx = unitPos->x - pos->x;
		Real dy = unitPos->y - pos->y;
		if (dx * dx + dy * dy < distance)
			distance = dx * dx + dy * dy;
		dx = unitPos->x - center.x;
		dy = unitPos->y - center.y;
		if (closest == 0 || dx * dx + dy * dy < centerDistance)
		{
			closest = obj;
			centerDistance = dx * dx + dy * dy;
		}
	}

	if (closest == 0)
		return false;
	AIUpdateInterface *closestAI = closest->getAIUpdateInterface();
	const Coord3D *closestPos = closest->getPosition();
	PathfindLayerEnum closestLayer = (PathfindLayerEnum)closest->getLayer();
	if (TheAI->m_pathfinder->lineBlocked(closest,
		closestAI->m_validLocomotorSurfaces, closestLayer, closestPos, &center))
		center = *closestPos;

	if (distance > (TheAI->m_aiData->m_minDistanceForGroup * g_bfmeK1266B) *
		(TheAI->m_aiData->m_minDistanceForGroup * g_bfmeK1266B))
		return false;

	Object *selected = kind8;
	if (kind9Or11 != 0)
		selected = kind9Or11;
	if (kind10 != 0)
		selected = kind10;
	if (selected == 0)
		return false;
	if (TheAI->findEnemyNear(selected, TheAI->m_field70, 0xE4, 0, 0) != 0)
		return false;

	reinterpret_cast<Rva00150700Owner *>(this)->reset();
	Path *path = TheAI->m_pathfinder->findGroundPath(
		selected->getPosition(), &center, (Int)pos, 4);
	m_center = center;
	m_groundPath = path;
	m_destination = *pos;
	if (m_groundPath != 0)
	{
		PathNode *node = m_groundPath->m_head;
		if (node != 0)
		{
			while (node->m_next != 0)
			{
				m_center = node->m_position;
				m_destination = node->m_next->m_position;
				if (TheTerrainLogic->slot47(&node->m_position))
				{
					reinterpret_cast<Rva00150700Owner *>(this)->reset();
					return false;
				}
				node = node->m_next;
			}
		}
	}
	return m_groundPath != 0;
}
