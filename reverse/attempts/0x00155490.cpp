// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z
// partial score=0.52 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: AIGroup::groupScatter, retail RVA 0x00155490, 525 bytes.
//
// Identity is the named GameLogic::logicMessageDispatcher MSG_DO_SCATTER call
// at 0x00398F0A through ILT 0x00038EE2.  The call lands at the full retail
// boundary 0x00155490..0x0015569D (the old 509-byte inventory stopped before
// the SEH epilogue).  The reference AIGroup::groupScatter has the same
// centroid, immobile/held filtering, pathfinder goal removal, far-to-near
// iterator sort, and radial AI movement sequence.

#define _STLP_NO_EXCEPTIONS 1
#include <math.h>

typedef bool Bool;
typedef float Real;

// These are the retail float objects used by the BFME Coord2D and scatter
// expressions.  The addresses are image VAs, as in the existing focused TUs.
#define BfmeZeroRange (*(const Real *)0x01075350)
#define g_bfmeDefaultBU (*(const Real *)0x01075334)
#define g_bfmeK1266B (*(const Real *)0x01075340)
#define g_01076C24 (*(const Real *)0x01076C24)

struct Coord2D
{
	Real x;
	Real y;

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y);
	}

	void normalize(void)
	{
		Real len = length();
		if (len != BfmeZeroRange)
		{
			x /= len;
			y /= len;
		}
	}
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1,
	ITER_SORTED_FAR_TO_NEAR = 2
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;

	Overridable *m_nextOverride;                         // +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] &
			(1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_008[0xC8 - 0x08];
	unsigned char m_kindof[12];                          // +0xC8
};

class AICommandInterface
{
public:
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
};

// BFME's AI update exposes the command interface at +0x20.  Keeping it as a
// typed secondary base makes the compiler emit the retail `lea ecx,[ai+20]`
// adjustment at the call site.
class AIUpdateInterfacePrefix
{
public:
	unsigned char m_unreconstructed_000[0x20];
};

class AIUpdateInterface : public AIUpdateInterfacePrefix,
	public AICommandInterface
{
};

class GeometryInfo
{
public:
	Real getBoundingCircleRadius(void) const { return m_boundingCircleRadius; }

private:
	Real m_boundingCircleRadius;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const ThingTemplate *getTemplate(void) const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	bool isKindOf(KindOfType t) const
	{
		const ThingTemplate *tmpl = getTemplate();
		if (tmpl == 0)
			return false;
		return tmpl->isKindOf(t);
	}

	unsigned char getDisabledMask(void) const { return m_disabledMask; }
	const Coord3D *getPosition(void) const { return &m_position; }
	Real getPosX(void) const { return m_position.x; }
	Real getPosY(void) const { return m_position.y; }
	Real getPosZ(void) const { return m_position.z; }
	AIUpdateInterface *getAI(void) { return m_ai; }
	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }
	const GeometryInfo &getGeometryInfo(void) const { return m_geometryInfo; }

private:
	unsigned char m_unreconstructed_000[0x04];
	ThingTemplate *m_template;                            // +0x04
	unsigned char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;                                   // +0x38
	unsigned char m_unreconstructed_044[0xbc - 0x44];
	GeometryInfo m_geometryInfo;                          // +0xBC
	unsigned char m_unreconstructed_0c0[0x1a4 - 0xc0];
	unsigned char m_disabledMask;                         // +0x1A4
	unsigned char m_unreconstructed_1a5[0x204 - 0x1a5];
	AIUpdateInterface *m_ai;                              // +0x204
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_unreconstructed_000[0x0c];
	Pathfinder *m_pathfinder;                             // +0x0C
};

extern AI *TheAI;

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_next;
	BfmeListNodeBase *m_prev;
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_value;
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, Real numeric);
	void sort(IterOrderType order);

private:
	unsigned char m_unreconstructed_004[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	void recompute(void);
	Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	void groupScatter(CommandSourceType cmdSource);

private:
	virtual ~AIGroup();
	BfmeListNodeBase *m_memberList;                         // +0x04
	unsigned int m_memberListSize;                        // +0x08
	void *m_groundPath;                                    // +0x0C
	Bool m_dirty;                                          // +0x10
};

// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z
void AIGroup::groupScatter(CommandSourceType cmdSource)
{
	if (m_dirty)
		recompute();

	SimpleObjectIterator *iter;
	Coord3D center;

	{
		Coord2D min;
		Coord2D max;
		getMinMaxAndCenter(&min, &max, &center);
	}

	iter = new SimpleObjectIterator;
	for (BfmeListNodeBase *i = m_memberList->m_next;
		i != m_memberList; i = i->m_next)
	{
		Real dx, dy;
		Object *obj = ((BfmeMemberNode *)i)->m_value;
		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getAI() == 0)
			continue;

		Coord2D unitPos = *((const Coord2D *)obj->getPosition());
		TheAI->pathfinder()->removeGoal(obj);
		dx = unitPos.x - center.x;
		dy = unitPos.y - center.y;
		iter->insert(obj, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);
	Object *theUnit;
	for (theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		center.x -= g_01076C24;
		AIUpdateInterface *ai = theUnit->getAIUpdateInterface();
		Coord3D unitPos = *((theUnit)->getPosition());
		Coord2D delta;
		Coord3D dest;
		dest = unitPos;
		delta.x = unitPos.x - center.x;
		delta.y = unitPos.y - center.y;
		delta.normalize();
		dest.x += delta.x * 4 *
			theUnit->getGeometryInfo().getBoundingCircleRadius();
		dest.y += delta.y * 4 *
			theUnit->getGeometryInfo().getBoundingCircleRadius();
		ai->aiMoveToPosition(&dest, cmdSource);
	}
}
