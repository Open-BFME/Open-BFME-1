// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// AIGroup::groupScatter (retail 0x00155490, 525 B, ret 4 at +0x20A). The member
// walk, sort and per-member move order follow AIGroupForwardedOrders.cpp's views;
// this unit needs STLport static-lib settings that file does not use.
#include <math.h>
#include <vector>
// stlport

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef float Real;

extern const float BfmeBoundaryZero3D;
extern const float g_bfmeDefaultBU;

// class-gate: allow Coord2D ZH's inline length()/normalize() (absent from the canonical header) are inlined into retail's scatter delta
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
		if (len != BfmeBoundaryZero3D)
		{
			x *= g_bfmeDefaultBU / len;
			y *= g_bfmeDefaultBU / len;
		}
	}
};

class Object;
class Waypoint;
class PolygonTrigger;

enum GuardMode { BFME_GUARD_MODE_NORMAL };

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum IterOrderType
{
	ITER_FASTEST = 0,
	ITER_SORTED_NEAR_TO_FAR = 1,
	ITER_SORTED_FAR_TO_NEAR = 2
};
enum KindOfType { KINDOF_IMMOBILE = 2, KINDOF_STRUCTURE = 7, KINDOF_AIRCRAFT = 12 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };

extern const float g_01076C24;
extern const float g_bfmeK1266B;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);		// ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;			// 0x012ED600

#define NAMEKEY(x) (TheNameKeyGenerator->nameToKey(x))

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	// ILT 0x000022BB

	Overridable *m_nextOverride;				// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType t) const
	{
		return (m_kindof[(unsigned int)t >> 5] & (1u << ((unsigned int)t & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	unsigned int m_kindof[3];				// +0xC8
};

class ContainModuleInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void orderAllPassengersToExit(CommandSourceType cmdSource);	// vtable +0x6C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual float getLayerHeight(float x, float y, PathfindLayerEnum layer,
			Coord3D *normal, bool clip);

	PathfindLayerEnum getHighestLayerForDestination(const Coord3D *pos, bool onlyHealthy);
};

extern TerrainLogic *TheTerrainLogic;

class StealthUpdate
{
public:
	void update002AD250();					// ILT 0x000272AF -> 0x002AD250; RVA-derived
};

class SimpleObjectIterator
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual Object *first();
	virtual Object *next();
	void insert(Object *obj, float numeric);
	void sort(IterOrderType order);

private:
	char m_bfmePad[12];
};

class Pathfinder
{
public:
	void removeGoal(Object *obj);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return m_pathfinder;
	}

private:
	char m_bfmePad[0x0c];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h

class Team;
class CommandButton;
class Path;
enum AICommandType { AICMD_MOVE_TO_POSITION=0 };
struct DamageInfo
{
	char m_bfme_body[0x5C];					// sizeof(DamageInfo)
};

// upstream layout: inputs/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParms
{
public:
	AICommandParms( AICommandType cmd, CommandSourceType commandSource );	// ILT 0x00030EA4

	AICommandType m_cmd;					// +0x00
	CommandSourceType m_cmdSource;			// +0x04
	Coord3D m_pos;							// +0x08
	Object *m_obj;							// +0x14
	Object *m_otherObj;						// +0x18
	const Team *m_team;						// +0x1C
	std::vector<Coord3D> m_coords;			// +0x20
	const Waypoint *m_waypoint;				// +0x2C
	const PolygonTrigger *m_polygon;		// +0x30
	int m_intValue;							// +0x34
	DamageInfo m_damage;					// +0x38
	const CommandButton *m_commandButton;	// +0x94
	Path *m_path;							// +0x98
};


class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowWaypointPathAsTeam(const Waypoint *way, CommandSourceType cmdSource);
	void aiHunt(CommandSourceType cmdSource);
	void aiIdle(CommandSourceType cmdSource);			// ILT 0x00024D70
	void aiTightenToPosition(const Coord3D *pos, CommandSourceType cmdSource);
	void aiFollowPathAppend(const Coord3D *pos, CommandSourceType cmdSource);
	void aiMoveToAndEvacuate(const Coord3D *pos, CommandSourceType cmdSource);	// ILT 0x00027903 -> 0x001528E0
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType cmdSource);		// ILT 0x000344C3 -> 0x000D8AC0
	void aiGuardPosition(const Coord3D *pos, ::GuardMode mode,
			::CommandSourceType cmdSource);			// ILT 0x0000A033
	void aiBfmeCommand44(const PolygonTrigger *poly, int value,
			CommandSourceType cmdSource, const Coord3D *pos);
};

class BfmeGroupAI
{
public:
	char m_bfmeHead[0x20];
	AICommandInterface m_bfmeCommands;			// +0x20
	unsigned char m_bfmeGap[0x1cc - 0x24];
	void *m_curLocomotor;					// +0x1cc, AIUpdateInterface view
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
		return getTemplate()->isKindOf(t);
	}

	float getPosX(void) const { return m_position.x; }
	float getPosY(void) const { return m_position.y; }
	float getPosZ(void) const { return m_position.z; }
	const Coord3D *getPosition(void) const { return &m_position; }
	BfmeGroupAI *getAI(void) { return m_ai; }
	unsigned char getDisabledMask(void) const { return m_disabledMask; }
	bool isDisabledByType(int type) const
	{
		return (m_disabledMask & (1 << type)) != 0;
	}
	bool isAirborneTarget(void) const { return (m_status90 & 0x40) != 0; }
	ContainModuleInterface *getContain(void) { return m_contain; }
	float getBoundingCircleRadius(void) const
	{
		return *(const float *)((const char *)this + 0xbc);
	}

	StealthUpdate *findUpdateModule(NameKeyType key);	// ILT 0x0002AE23
	void leaveGroup();

	virtual ~Object();
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;					// +0x38
	unsigned char m_unreconstructed_44[0x90 - 0x44];
	unsigned char m_status90;				// +0x90
	unsigned char m_unreconstructed_91[0x1A4 - 0x91];
	volatile unsigned char m_disabledMask;				// +0x1A4
	unsigned char m_unreconstructed_1A5[0x1FC - 0x1A5];
	ContainModuleInterface *m_contain;			// +0x1FC
	unsigned char m_unreconstructed_200[0x204 - 0x200];
	BfmeGroupAI *m_ai;					// +0x204
};

struct BfmeListNodeBase
{
	BfmeListNodeBase *m_bfmeNext;				// +0x00
	BfmeListNodeBase *m_bfmePrev;				// +0x04
};

struct BfmeMemberNode : public BfmeListNodeBase
{
	Object *m_bfmeValue;					// +0x08
};

struct BfmeMemberListIterator
{
	BfmeListNodeBase *m_node;

	Object *operator*(void) const
	{
		return ((BfmeMemberNode *)m_node)->m_bfmeValue;
	}

	BfmeMemberListIterator &operator++(void)
	{
		m_node = m_node->m_bfmeNext;
		return *this;
	}

	bool operator!=(const BfmeMemberListIterator &other) const
	{
		return m_node != other.m_node;
	}
};

struct BfmeMemberList
{
	BfmeListNodeBase *m_head;

	BfmeMemberListIterator begin(void) const
	{
		BfmeMemberListIterator i = { m_head->m_bfmeNext };
		return i;
	}

	BfmeMemberListIterator end(void) const
	{
		BfmeMemberListIterator i = { m_head };
		return i;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	// Nested for groupGuardPosition alone -- see the note at the top of this file.
	enum GuardMode { BFME_AIGROUP_GUARD_MODE };
	enum CommandSourceType { BFME_AIGROUP_COMMAND_SOURCE };

	void groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
			::CommandSourceType cmdSource);
	void groupFollowWaypointPathAsTeam(const Waypoint *way, ::CommandSourceType cmdSource);
	void groupHunt(::CommandSourceType cmdSource);
	void groupEvacuate(::CommandSourceType cmdSource);
	void groupGuardPosition(const Coord3D *pos, GuardMode mode,
			CommandSourceType cmdSource);
	void groupBfmeCommand44(const PolygonTrigger *poly, int value,
			::CommandSourceType cmdSource, const Coord3D *pos);
	void groupStealthIdle();
	void groupScatter(::CommandSourceType cmdSource);
	bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
private:
	void recompute(void);
public:

	char isReady();								// ILT 0x000104B0
	void prepFollow(::CommandSourceType cmdSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	union
	{
		BfmeListNodeBase *m_bfmeMembers;			// +0x04
		BfmeMemberList m_memberList;
	};
	char m_bfmeFields08[0x10 - 0x08];
	bool m_dirty;							// +0x10
};


__declspec(noinline) inline void AICommandInterface::aiMoveToPosition( const Coord3D *position, CommandSourceType commandSource )
{
	AICommandParms parms( AICMD_MOVE_TO_POSITION, commandSource );
	parms.m_pos = *position;
	aiDoCommand( &parms );
}


//-------------------------------------------------------------------------------------------------
// AI Command Interface implementation for AIGroup
//

/**
 * Scatter
 */
void AIGroup::groupScatter(::CommandSourceType cmdSource)
{
	if (m_dirty)
		recompute();

	// compute current centroid of the team
	Coord3D center;
	{
		Coord2D min;
		Coord2D max;
		getMinMaxAndCenter(&min, &max, &center);
	}

	// Move.
	SimpleObjectIterator *iter = new SimpleObjectIterator;

	BfmeMemberListIterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;

		if (obj->isDisabledByType(3))
			continue; // don't bother telling the occupants to move.
		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getAI() == 0)
			continue;

		Coord3D unitPos;
		unitPos.x = obj->getPosX();
		unitPos.y = obj->getPosY();
		TheAI->pathfinder()->removeGoal(obj);
		float dx = unitPos.x - center.x;
		float dy = unitPos.y - center.y;
		iter->insert(*i, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_FAR_TO_NEAR);

	for (Object *theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		Coord3D unitPos;
		// Retail copies x then y through one register: one temp, volatile reads and stores.
		unsigned t = *(const volatile unsigned *)&theUnit->m_position.x;
		*(volatile unsigned *)&unitPos.x = t;
		t = *(const volatile unsigned *)&theUnit->m_position.y;
		*(volatile unsigned *)&unitPos.y = t;
		center.x -= g_01076C24;
		unitPos.z = theUnit->getPosZ();
		BfmeGroupAI *ai = theUnit->getAI();
		Coord3D dest;
		Coord2D delta;
		dest = unitPos;
		delta.x = unitPos.x - center.x;
		delta.y = unitPos.y - center.y;
		delta.normalize();
		dest.x += delta.x * 4 * theUnit->getBoundingCircleRadius();
		dest.y += delta.y * 4 * theUnit->getBoundingCircleRadius();
		ai->m_bfmeCommands.aiMoveToPosition(&dest, cmdSource);
	}
}
