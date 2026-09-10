// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z
// partial score=0.82 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: the AIGroup orders that walk the member list and forward one
// command to each member's own AICommandInterface.
//
//   ?groupTightenToPosition@         0x00155720, 295 bytes
//   ?groupFollowWaypointPathAsTeam@  0x00155A80,  85 bytes
//   ?groupHunt@                      0x00156270,  53 bytes
//   ?groupEvacuate@                  0x00156690, 260 bytes
//   ?groupGuardPosition@             0x00156840,  77 bytes
//   ?groupBfmeCommand44@             0x001569C0,  85 bytes
//   ?groupStealthIdle@               0x00156B10, 173 bytes
//
// One walk, seven commands. The member list is the node pointer at AIGroup+0x04,
// walked as an STLport sentinel ring -- next is begin, the node itself is end --
// with the member object at node+0x08, its AI at object+0x204 and the command
// interface at AI+0x20. Four files each drew that chain of four structs out in
// full; it is one chain and it is drawn once here.
//
// Around the walk they differ in the guard and in what they do with the member:
// groupHunt has none, groupGuardPosition and groupBfmeCommand44 drop out on a
// null argument, groupFollowWaypointPathAsTeam asks isReady() first and runs a
// group prep, groupStealthIdle skips any member without a StealthUpdate module,
// groupEvacuate splits three ways on what the member is,
// and groupTightenToPosition does not forward from the walk at all -- it uses the
// walk only to fill a heap SimpleObjectIterator with each member's squared
// distance to the target, sorts NEAR_TO_FAR, and forwards from THAT, which is
// what the extra 200 bytes buy. (It never deletes the iterator.)
//
// The member class had two names and one layout. Four of the seven called it
// BfmeGroupMember and described it as `char m_bfmeHead[0x204]` with the AI
// pointer behind it; the other three called it Object and named fields inside
// that head -- a vptr at +0x00, the template at +0x04, the position at +0x38,
// the status byte at +0x90, the disabled mask at +0x1A4, the contain module at
// +0x1FC -- all of which the opaque head simply swallowed, and no two of the
// three named the same subset. One class, named Object, below. Two of its fields
// are corroborated from outside this lane: the contain module at +0x1FC is what
// AIUpdateInterface::privateExitInstantly reads, and the status at +0x90 is what
// bfmeCurrentWeaponTemplateFlag4 tests.
//
// groupGuardPosition is the one that could not simply share an enum with its
// three neighbours, and this is the reason the file has two of each. Its
// decorated name is
//   ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
// -- the `@1@` says BOTH enums are nested inside AIGroup -- while groupHunt is
//   ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
// with the same-named enum at file scope, and the callees on the far side of
// every one of these calls take the file-scope spelling too. So AIGroup carries
// its own nested GuardMode and CommandSourceType for the one method whose
// mangled name demands them, the other three qualify their parameter as
// `::CommandSourceType`, and groupGuardPosition casts across at the call. Two
// types with one name is not a mistake here; it is what the retail symbols say.
//
// this is spilled to the frame and reloaded after every call in
// groupGuardPosition, and the end of the list is re-read from it each trip,
// because a guard order can change the membership underneath the walk.

#include <math.h>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

typedef float Real;

extern const float BfmeZeroRange;
extern const float g_bfmeDefaultBU;

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride(void) const;	// ILT 0x000022BB

	Overridable *m_nextOverride;				// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

#pragma comment(linker, "/alternatename:?removeGoal@Pathfinder@@QAEXPAVObject@@@Z=?j_00015d02@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
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
	unsigned char m_bfmeGap[0x1cc - 0x21];
	void *m_curLocomotor;					// +0x1cc, AIUpdateInterface view
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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
	void recompute(void);

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

// ?groupTightenToPosition@AIGroup@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
// The one that does not forward from the walk. Identity is the matched
// aiTightenToPosition callee (ILT 0x000438C9 -> 0x001527C0); the addWaypoint arm
// is aiFollowPathAppend (ILT 0x0000BAC8 -> 0x00153480).
void AIGroup::groupTightenToPosition(const Coord3D *pos, bool addWaypoint,
		::CommandSourceType cmdSource)
{
	SimpleObjectIterator *iter = new SimpleObjectIterator;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		Coord3D unitPos;
		unitPos.x = obj->getPosX();
		unitPos.y = obj->getPosY();

		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (obj->getAI() == 0)
			continue;

		float dx = unitPos.x - pos->x;
		float dy = unitPos.y - pos->y;
		iter->insert(obj, dx * dx + dy * dy);
	}

	iter->sort(ITER_SORTED_NEAR_TO_FAR);

	for (Object *theUnit = iter->first(); theUnit; theUnit = iter->next())
	{
		BfmeGroupAI *ai = theUnit->getAI();
		if (!addWaypoint)
			ai->m_bfmeCommands.aiTightenToPosition(pos, cmdSource);
		else
			ai->m_bfmeCommands.aiFollowPathAppend(pos, cmdSource);
	}
}

// ?groupFollowWaypointPathAsTeam@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z
// The only one of the four with anything before the walk: a Bool gate at
// ILT 0x000104B0 and a group prep at ILT 0x0002E636 -> 0x0015AB50.
void AIGroup::groupFollowWaypointPathAsTeam(const Waypoint *way, ::CommandSourceType cmdSource)
{
	if (!isReady())
		return;

	prepFollow(cmdSource, 0);

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiFollowWaypointPathAsTeam(way, cmdSource);
	}
}

// ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
// The bare walk, and at 53 bytes the price of the walk itself. Identity is the
// matched aiHunt callee, ILT 0x0001C882 -> 0x000D88D0.
void AIGroup::groupHunt(::CommandSourceType cmdSource)
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiHunt(cmdSource);
	}
}

// ?groupEvacuate@AIGroup@@QAEXW4CommandSourceType@@@Z
// The three-way split Zero Hour also has: an airborne aircraft is dropped to the
// terrain layer height first, anything else with an AI is told to evacuate, and
// a structure without an AI orders its passengers out through the contain module.
void AIGroup::groupEvacuate(::CommandSourceType cmdSource)
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		BfmeGroupAI *ai = obj->getAI();
		if (ai)
		{
			if (obj->isKindOf(KINDOF_AIRCRAFT) && obj->isAirborneTarget())
			{
				Coord3D pos;
				pos.set(((BfmeMemberNode *)it)->m_bfmeValue->getPosition());
				PathfindLayerEnum layerAtDest =
						TheTerrainLogic->getHighestLayerForDestination(&pos, false);
				pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, layerAtDest, 0, true);
				ai->m_bfmeCommands.aiMoveToAndEvacuate(&pos, cmdSource);
			}
			else
			{
				ai->m_bfmeCommands.aiEvacuate(false, cmdSource);
			}
		}
		else if (obj->isKindOf(KINDOF_STRUCTURE))
		{
			ContainModuleInterface *contain = obj->getContain();
			if (contain)
				contain->orderAllPassengersToExit(cmdSource);
		}
	}
}

// ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
void AIGroup::groupGuardPosition(const Coord3D *pos, GuardMode mode,
		CommandSourceType cmdSource)
{
	if (!pos)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiGuardPosition(pos, (::GuardMode)mode,
					(::CommandSourceType)cmdSource);
	}
}

// ?groupBfmeCommand44@AIGroup@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@PBUCoord3D@@@Z
// The callee is the matched 0x44 command builder at 0x001549A0, which
// AICommandInterfaceGuardCommands.cpp reads as a guard-area order carrying an
// extra position.
void AIGroup::groupBfmeCommand44(const PolygonTrigger *poly, int value,
		::CommandSourceType cmdSource, const Coord3D *pos)
{
	if (!poly)
		return;

	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		BfmeGroupAI *ai = ((BfmeMemberNode *)it)->m_bfmeValue->m_ai;

		if (ai)
			ai->m_bfmeCommands.aiBfmeCommand44(poly, value, cmdSource, pos);
	}
}

// ?groupStealthIdle@AIGroup@@QAEXXZ
// Descriptive name: identity is the group walk plus the "StealthUpdate" string.
// It is not Zero Hour's groupIdle, which takes a CommandSourceType.
void AIGroup::groupStealthIdle()
{
	for (BfmeListNodeBase *it = m_bfmeMembers->m_bfmeNext;
			it != m_bfmeMembers;
			it = it->m_bfmeNext)
	{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		if (!obj)
			continue;

		BfmeGroupAI *ai = obj->m_ai;
		static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
		StealthUpdate *stealth = obj->findUpdateModule(key_StealthUpdate);
		if (!stealth)
			continue;

		if (ai)
			ai->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		stealth->update002AD250();
	}
}

// ?groupScatter@AIGroup@@QAEXW4CommandSourceType@@@Z
// Named GameLogic::logicMessageDispatcher MSG_DO_SCATTER caller and the
// vendored AIGroup::groupScatter body establish the identity.  BFME keeps the
// same member walk but stores its list as the intrusive sentinel at +0x04.
void AIGroup::groupScatter(::CommandSourceType cmdSource)
{
	if (m_dirty)
		recompute();

	Coord3D center;
	{
		Coord2D min;
		Coord2D max;
		getMinMaxAndCenter(&min, &max, &center);
	}

	SimpleObjectIterator *iter = new SimpleObjectIterator;

	BfmeMemberListIterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;

		if (obj->isDisabledByType(3))
			continue;
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
		center.x -= g_01076C24;
		BfmeGroupAI *ai = theUnit->getAI();
		Coord3D dest;
		Coord3D unitPos = *theUnit->getPosition();
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

// ?isReady@AIGroup@@QAEDXZ
// The group-ready gate is reached by the matched
// groupFollowWaypointPathAsTeam body through ILT 0x000104B0.  A member with
// disabled bit 8, no AI or locomotor, or an immobile final override template
// is removed when the group has more than one member.  A one-member group
// containing one of those units is not ready; all other paths return true.
char AIGroup::isReady()
{
	BfmeListNodeBase *head = m_bfmeMembers;
	BfmeListNodeBase *it = head->m_bfmeNext;
	if (it != head)
	{
		for (;;)
		{
		Object *obj = ((BfmeMemberNode *)it)->m_bfmeValue;
		unsigned char disabled = obj->getDisabledMask();
		char remove = 0;
		if (disabled & 8)
			remove = 1;
		BfmeGroupAI *ai = obj->m_ai;
		if (ai == 0 || ai->m_curLocomotor == 0)
			remove = 1;
		else
		{
			const ThingTemplate *tmpl = obj->m_template;
			const ThingTemplate *finalTemplate = tmpl;
			if (tmpl != 0 && tmpl->m_nextOverride != 0)
				finalTemplate =
					(const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
			if (finalTemplate->isKindOf(KINDOF_IMMOBILE))
				remove = true;
		}

		it = it->m_bfmeNext;
		if (!remove)
		{
			if (it == head)
				break;
			continue;
		}

		BfmeListNodeBase *countIt = m_bfmeMembers->m_bfmeNext;
		int count = 0;
		if (countIt != m_bfmeMembers)
		{
			do
			{
				countIt = countIt->m_bfmeNext;
				++count;
			} while (countIt != m_bfmeMembers);
		}
		if (count == 1)
			return 0;

		obj->leaveGroup();
		head = m_bfmeMembers;
		it = head->m_bfmeNext;
		if (it == head)
			break;
		}
	}
	return 1;
}
