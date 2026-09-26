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
enum IterOrderType { ITER_FASTEST = 0, ITER_SORTED_NEAR_TO_FAR = 1 };
enum KindOfType { KINDOF_IMMOBILE = 2, KINDOF_STRUCTURE = 7, KINDOF_AIRCRAFT = 12 };
enum PathfindLayerEnum { LAYER_GROUND = 1 };

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
	virtual void orderAllPassengersToExit(CommandSourceType commandSource);	// vtable +0x6C
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
	void insert(Object *object, float distanceSquared);
	void sort(IterOrderType order);

private:
	char m_bfmePad[12];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	void aiFollowWaypointPathAsTeam(const Waypoint *waypoint, CommandSourceType commandSource);
	void aiHunt(CommandSourceType commandSource);
	void aiIdle(CommandSourceType commandSource);			// ILT 0x00024D70
	void aiTightenToPosition(const Coord3D *position, CommandSourceType commandSource);
	void aiFollowPathAppend(const Coord3D *position, CommandSourceType commandSource);
	void aiMoveToAndEvacuate(const Coord3D *position, CommandSourceType commandSource);	// ILT 0x00027903 -> 0x001528E0
	void aiEvacuate(bool exposeStealthUnits, CommandSourceType commandSource);		// ILT 0x000344C3 -> 0x000D8AC0
	void aiGuardPosition(const Coord3D *position, ::GuardMode mode,
			::CommandSourceType commandSource);			// ILT 0x0000A033
	void aiBfmeCommand44(const PolygonTrigger *polygon, int value,
			CommandSourceType commandSource, const Coord3D *position);
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
	const Coord3D *getPosition(void) const { return &m_position; }
	BfmeGroupAI *getAI(void) { return m_ai; }
	unsigned char getDisabledMask(void) const { return m_disabledMask; }
	bool isAirborneTarget(void) const { return (m_status & 0x40) != 0; }
	ContainModuleInterface *getContain(void) { return m_contain; }

	StealthUpdate *findUpdateModule(NameKeyType key);	// ILT 0x0002AE23
	void leaveGroup();

	virtual ~Object();
	const ThingTemplate *m_template;			// +0x04
	unsigned char m_unreconstructed_08[0x38 - 0x08];
	Coord3D m_position;					// +0x38
	unsigned char m_unreconstructed_44[0x90 - 0x44];
	unsigned char m_status;				// +0x90
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	// Nested for groupGuardPosition alone -- see the note at the top of this file.
	enum GuardMode { BFME_AIGROUP_GUARD_MODE };
	enum CommandSourceType { BFME_AIGROUP_COMMAND_SOURCE };

	void groupTightenToPosition(const Coord3D *position, bool addWaypoint,
			::CommandSourceType commandSource);
	void groupFollowWaypointPathAsTeam(const Waypoint *waypoint, ::CommandSourceType commandSource);
	void groupHunt(::CommandSourceType commandSource);
	void groupEvacuate(::CommandSourceType commandSource);
	void groupGuardPosition(const Coord3D *position, GuardMode mode,
			CommandSourceType commandSource);
	void groupBfmeCommand44(const PolygonTrigger *polygon, int value,
			::CommandSourceType commandSource, const Coord3D *position);
	void groupStealthIdle();

	char isReady();								// ILT 0x000104B0
	void prepFollow(::CommandSourceType commandSource, int unused);	// ILT 0x0002E636

private:
	char m_bfmeHead[0x04];
	BfmeListNodeBase *m_memberList;			// +0x04
};

// ?groupTightenToPosition@AIGroup@@QAEXPBUCoord3D@@_NW4CommandSourceType@@@Z
// The one that does not forward from the walk. Identity is the matched
// aiTightenToPosition callee (ILT 0x000438C9 -> 0x001527C0); the addWaypoint arm
// is aiFollowPathAppend (ILT 0x0000BAC8 -> 0x00153480).
void AIGroup::groupTightenToPosition(const Coord3D *position, bool addWaypoint,
		::CommandSourceType commandSource)
{
	SimpleObjectIterator *memberDistanceIterator = new SimpleObjectIterator;

	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		Object *memberObject = ((BfmeMemberNode *)memberNode)->m_bfmeValue;
		Coord3D unitPos;
		unitPos.x = memberObject->getPosX();
		unitPos.y = memberObject->getPosY();

		if (memberObject->getDisabledMask() & 8)
			continue;
		if (memberObject->isKindOf(KINDOF_IMMOBILE))
			continue;
		if (memberObject->getAI() == 0)
			continue;

		float dx = unitPos.x - position->x;
		float dy = unitPos.y - position->y;
		memberDistanceIterator->insert(memberObject, dx * dx + dy * dy);
	}

	memberDistanceIterator->sort(ITER_SORTED_NEAR_TO_FAR);

	for (Object *orderedMember = memberDistanceIterator->first(); orderedMember; orderedMember = memberDistanceIterator->next())
	{
		BfmeGroupAI *memberAI = orderedMember->getAI();
		if (!addWaypoint)
			memberAI->m_bfmeCommands.aiTightenToPosition(position, commandSource);
		else
			memberAI->m_bfmeCommands.aiFollowPathAppend(position, commandSource);
	}
}

// ?groupFollowWaypointPathAsTeam@AIGroup@@QAEXPBVWaypoint@@W4CommandSourceType@@@Z
// The only one of the four with anything before the walk: a Bool gate at
// ILT 0x000104B0 and a group prep at ILT 0x0002E636 -> 0x0015AB50.
void AIGroup::groupFollowWaypointPathAsTeam(const Waypoint *waypoint, ::CommandSourceType commandSource)
{
	if (!isReady())
		return;

	prepFollow(commandSource, 0);

	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		BfmeGroupAI *memberAI = ((BfmeMemberNode *)memberNode)->m_bfmeValue->m_ai;

		if (memberAI)
			memberAI->m_bfmeCommands.aiFollowWaypointPathAsTeam(waypoint, commandSource);
	}
}

// ?groupHunt@AIGroup@@QAEXW4CommandSourceType@@@Z
// The bare walk, and at 53 bytes the price of the walk itself. Identity is the
// matched aiHunt callee, ILT 0x0001C882 -> 0x000D88D0.
void AIGroup::groupHunt(::CommandSourceType commandSource)
{
	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		BfmeGroupAI *memberAI = ((BfmeMemberNode *)memberNode)->m_bfmeValue->m_ai;

		if (memberAI)
			memberAI->m_bfmeCommands.aiHunt(commandSource);
	}
}

// ?groupEvacuate@AIGroup@@QAEXW4CommandSourceType@@@Z
// The three-way split Zero Hour also has: an airborne aircraft is dropped to the
// terrain layer height first, anything else with an AI is told to evacuate, and
// a structure without an AI orders its passengers out through the contain module.
void AIGroup::groupEvacuate(::CommandSourceType commandSource)
{
	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		Object *memberObject = ((BfmeMemberNode *)memberNode)->m_bfmeValue;
		BfmeGroupAI *memberAI = memberObject->getAI();
		if (memberAI)
		{
			if (memberObject->isKindOf(KINDOF_AIRCRAFT) && memberObject->isAirborneTarget())
			{
				Coord3D evacuationPosition;
				evacuationPosition.set(((BfmeMemberNode *)memberNode)->m_bfmeValue->getPosition());
				PathfindLayerEnum layerAtDest =
						TheTerrainLogic->getHighestLayerForDestination(&evacuationPosition, false);
				evacuationPosition.z = TheTerrainLogic->getLayerHeight(evacuationPosition.x, evacuationPosition.y, layerAtDest, 0, true);
				memberAI->m_bfmeCommands.aiMoveToAndEvacuate(&evacuationPosition, commandSource);
			}
			else
			{
				memberAI->m_bfmeCommands.aiEvacuate(false, commandSource);
			}
		}
		else if (memberObject->isKindOf(KINDOF_STRUCTURE))
		{
			ContainModuleInterface *containModule = memberObject->getContain();
			if (containModule)
				containModule->orderAllPassengersToExit(commandSource);
		}
	}
}

// ?groupGuardPosition@AIGroup@@QAEXPBUCoord3D@@W4GuardMode@1@W4CommandSourceType@1@@Z
void AIGroup::groupGuardPosition(const Coord3D *position, GuardMode mode,
		CommandSourceType commandSource)
{
	if (!position)
		return;

	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		BfmeGroupAI *memberAI = ((BfmeMemberNode *)memberNode)->m_bfmeValue->m_ai;

		if (memberAI)
			memberAI->m_bfmeCommands.aiGuardPosition(position, (::GuardMode)mode,
					(::CommandSourceType)commandSource);
	}
}

// ?groupBfmeCommand44@AIGroup@@QAEXPBVPolygonTrigger@@HW4CommandSourceType@@PBUCoord3D@@@Z
// The callee is the matched 0x44 command builder at 0x001549A0, which
// AICommandInterfaceGuardCommands.cpp reads as a guard-area order carrying an
// extra position.
void AIGroup::groupBfmeCommand44(const PolygonTrigger *polygon, int value,
		::CommandSourceType commandSource, const Coord3D *position)
{
	if (!polygon)
		return;

	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		BfmeGroupAI *memberAI = ((BfmeMemberNode *)memberNode)->m_bfmeValue->m_ai;

		if (memberAI)
			memberAI->m_bfmeCommands.aiBfmeCommand44(polygon, value, commandSource, position);
	}
}

// ?groupStealthIdle@AIGroup@@QAEXXZ
// Descriptive name: identity is the group walk plus the "StealthUpdate" string.
// It is not Zero Hour's groupIdle, which takes a CommandSourceType.
void AIGroup::groupStealthIdle()
{
	for (BfmeListNodeBase *memberNode = m_memberList->m_bfmeNext;
			memberNode != m_memberList;
			memberNode = memberNode->m_bfmeNext)
	{
		Object *memberObject = ((BfmeMemberNode *)memberNode)->m_bfmeValue;
		if (!memberObject)
			continue;

		BfmeGroupAI *memberAI = memberObject->m_ai;
		static const NameKeyType key_StealthUpdate = NAMEKEY("StealthUpdate");
		StealthUpdate *stealthUpdate = memberObject->findUpdateModule(key_StealthUpdate);
		if (!stealthUpdate)
			continue;

		if (memberAI)
			memberAI->m_bfmeCommands.aiIdle(CMD_FROM_AI);
		stealthUpdate->update002AD250();
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
	BfmeListNodeBase *memberListHead = m_memberList;
	BfmeListNodeBase *memberNode = memberListHead->m_bfmeNext;
	if (memberNode != memberListHead)
	{
		for (;;)
		{
		Object *memberObject = ((BfmeMemberNode *)memberNode)->m_bfmeValue;
		unsigned char disabledMask = memberObject->getDisabledMask();
		char shouldRemoveMember = 0;
		if (disabledMask & 8)
			shouldRemoveMember = 1;
		BfmeGroupAI *memberAI = memberObject->m_ai;
		if (memberAI == 0 || memberAI->m_curLocomotor == 0)
			shouldRemoveMember = 1;
		else
		{
			const ThingTemplate *memberTemplate = memberObject->m_template;
			const ThingTemplate *finalTemplate = memberTemplate;
			if (memberTemplate != 0 && memberTemplate->m_nextOverride != 0)
				finalTemplate =
					(const ThingTemplate *)memberTemplate->m_nextOverride->getFinalOverride();
			if (finalTemplate->isKindOf(KINDOF_IMMOBILE))
				shouldRemoveMember = true;
		}

		memberNode = memberNode->m_bfmeNext;
		if (!shouldRemoveMember)
		{
			if (memberNode == memberListHead)
				break;
			continue;
		}

		BfmeListNodeBase *countNode = m_memberList->m_bfmeNext;
		int memberCount = 0;
		if (countNode != m_memberList)
		{
			do
			{
				countNode = countNode->m_bfmeNext;
				++memberCount;
			} while (countNode != m_memberList);
		}
		if (memberCount == 1)
			return 0;

		memberObject->leaveGroup();
		memberListHead = m_memberList;
		memberNode = memberListHead->m_bfmeNext;
		if (memberNode == memberListHead)
			break;
		}
	}
	return 1;
}
