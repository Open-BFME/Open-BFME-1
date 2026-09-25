// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// AIGroup::checkSpecial at 0x00154F00 (966 bytes) is identified by the
// matched tryGroupSpecial caller via ILT 0x0002D565. Native C++ only.
// Callee ABI: ILT 0x00048C57 takes Object*, from*, to*, radius (not the
// older two-coordinate ledger declaration). ILT 0x0003F990 receives TheAI
// in ECX here and in independent caller 0x00177915. Both are address views.
// Full instruction and layout witnesses: build/unclaimed_map/astra_E/LAYOUTS.md.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

#include "Lib/BaseType.h"

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AbleToAttackType
{
	ATTACK_NEW_TARGET = 0
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 2,
	ATTACKRESULT_POSSIBLE = 3
};

class Object;

struct BfmeListNodeBase
{
	BfmeListNodeBase *next;
	BfmeListNodeBase *prev;
};

struct BfmeObjectNode : public BfmeListNodeBase
{
	Object *value;
};

struct ContainedItemsList
{
	BfmeListNodeBase *head;
};

class SpawnBehaviorInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C();
	virtual void orderSlavesToAttackPosition(const Coord3D *, Int, CommandSourceType);
};

class ContainModuleInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual Bool isPassengerAllowedToFire();
	virtual void slotA4(); virtual void slotA8(); virtual void slotAC(); virtual void slotB0();
	virtual void slotB4(); virtual void slotB8(); virtual void slotBC(); virtual void slotC0();
	virtual void slotC4(); virtual void slotC8(); virtual void slotCC(); virtual void slotD0();
	virtual void slotD4(); virtual void slotD8(); virtual void slotDC(); virtual void slotE0();
	virtual void slotE4(); virtual void slotE8(); virtual void slotEC(); virtual void slotF0();
	virtual void slotF4(); virtual void slotF8(); virtual void slotFC(); virtual void slot100();
	virtual const ContainedItemsList *getContainedItemsList();
};

class AICommandInterface
{
public:
	void aiAttackPosition(const Coord3D *, Int, CommandSourceType);
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
	const Overridable *getFinalOverride(void) const {if(m_nextOverride)return m_nextOverride->getFinalOverride();return this;}

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
		return (const ThingTemplate*)tmpl->getFinalOverride();
	}
	Bool isKindOf(KindOfType type) const;

protected:
	ThingTemplate *m_template;
};

class AIUpdateInterface
{
public:
	unsigned char m_unmodelled_000[0x20];
 AICommandInterface m_commands;
 unsigned char m_unmodelled_021[0x1B8-0x21];
	UnsignedInt m_validLocomotorSurfaces;
};

typedef AIUpdateInterface BfmeAIUpdateInterface;

class Object : public Thing
{
public:
 virtual ~Object();
 SpawnBehaviorInterface *getSpawnBehaviorInterface() const;
 CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,const Object *,CommandSourceType,WeaponSlotType) const;
 ContainModuleInterface *getContain() const {return m_contain;}
	const Coord3D *getPosition(void) const { return &m_position; }
	UnsignedInt getDisabledMask(void) const { return m_disabledMask; }
	AIUpdateInterface *getAIUpdateInterface(void) { return m_ai; }
	Int getLayer(void) const;

public:
	unsigned char m_unmodelled_008[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unmodelled_044[0x1A4 - 0x44];
	UnsignedInt m_disabledMask;
	unsigned char m_unmodelled_1A8[0x1FC - 0x1A8];
 ContainModuleInterface *m_contain;
 unsigned char m_unmodelled_200[4];
	AIUpdateInterface *m_ai;
};

class PathNode
{
public:
	unsigned char m_unmodelled_000[8];
	PathNode *m_nextOpti;
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
	void removeGoal003E3D20(Object *obj);
	Int lineBlocked(Object *obj, Int value, PathfindLayerEnum layer,
		const Coord3D *start, const Coord3D *end);
	Path *rva003F2160(Object *,const Coord3D *,const Coord3D *,Int);
};


class TAiData
{
public:
	unsigned char m_unmodelled_000[0x6C];
	Real m_minDistanceForGroup;
 Real rva070;
};

class AI
{
public:
	unsigned char m_unmodelled_000[0x0C];
	Pathfinder *m_pathfinder;

	unsigned char m_unmodelled_010[4];
	TAiData *m_aiData;


	Object *rva0014d120(Object *obj, Real range, Int a, Int b, Int c);
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
	void groupAttackPosition(const Coord3D *, Int, CommandSourceType);
 UnsignedInt getID(void);
 Bool getMinMaxAndCenter(Coord2D *min, Coord2D *max, Coord3D *center);
	void recompute(void);
	Bool checkSpecial(const Coord3D *pos, Int a);

private:
 unsigned char m_unmodelled_000[4];
	_STL::list<Object *> m_memberList;
	UnsignedInt m_memberListSize;
	unsigned char m_layout[4];
	Bool m_dirty;
	unsigned char m_unmodelled_011[3];
	UnsignedInt m_id;
	Path *m_groundPath;
	Coord3D rva01c;
	Coord3D rva028;
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;



Bool AIGroup::checkSpecial(const Coord3D *pos, Int a)
{
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, pos);
	if (layer != LAYER_GROUND)
		return false;
	if (TheTerrainLogic->slot47(pos))
		return false;

	if (m_dirty)
		recompute();

	Coord3D center;
	Coord2D min;
	Coord2D max;
	getMinMaxAndCenter(&min, &max, &center);

	Real distance = TheAI->m_aiData->m_minDistanceForGroup * 4.0f;
	distance *= distance;
	rva01c = center;
	rva028 = *pos;
	Real centerDistance = distance * 10.0f;

	Object *closest = 0;
	Object *kind8 = 0;
	Object *kind9Or11 = 0;
	Object *kind10 = 0;
	_STL::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		Object *obj = *i;
		TheAI->m_pathfinder->removeGoal003E3D20(obj);
		if (obj->getDisabledMask() & 8)
			continue;
		if (obj->getAIUpdateInterface() == 0)
			continue;
		const ThingTemplate *tmpl = obj->getTemplate();
		if ((tmpl->m_kindof[0] & 0x1000) != 0)
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
		obj = *i;
		const Coord3D *unitPos = obj->getPosition();
		Real x = unitPos->x, y = unitPos->y;
		Real dx = x - pos->x;
		Real dy = y - pos->y;
		if (dx * dx + dy * dy < distance)
			distance = dx * dx + dy * dy;
		dx = x - center.x;
		dy = y - center.y;
		if (closest == 0 || dx * dx + dy * dy < centerDistance)
		{
			closest = obj;
			centerDistance = dx * dx + dy * dy;
		}
	}

	if (closest == 0)
		return false;
	AIUpdateInterface *closestAI = closest->getAIUpdateInterface();
	Int surfaces = closestAI->m_validLocomotorSurfaces;
	Pathfinder *pf = TheAI->m_pathfinder;
	const Coord3D *closestPos = closest->getPosition();
	if ((unsigned char)pf->lineBlocked(closest, surfaces,
		(PathfindLayerEnum)closest->getLayer(), closestPos, &center))
		center = *closestPos;

	Real dx = max.x - min.x, dy = max.y - min.y;
	TAiData *data = TheAI->m_aiData;
	Real width = data->m_minDistanceForGroup * 4.0f;
	Real chosen = dx * dx + dy * dy;
	if (!(chosen > width * width))
		chosen = distance;
	if (chosen < data->m_minDistanceForGroup * data->m_minDistanceForGroup)
		return false;

	Object *selected = kind8;
	if (kind9Or11 != 0)
		selected = kind9Or11;
	if (kind10 != 0)
		selected = kind10;
	if (selected == 0)
		return false;
	Real range = data->rva070;
	if (TheAI->rva0014d120(selected, range, 0xE4, 0, 0) != 0)
		return false;

	reinterpret_cast<Rva00150700Owner *>(this)->reset();
	pf = TheAI->m_pathfinder;
	Path *path = pf->rva003F2160(selected, &center, pos, 4);
	rva01c = center;
	m_groundPath = path;
	rva028 = *pos;
	if (m_groundPath != 0)
	{
		PathNode *node = m_groundPath->m_head;
		if (node != 0)
		{
			if (node->m_nextOpti)
			{
				rva01c = node->m_position;
				rva028 = node->m_nextOpti->m_position;
			}
			while (node)
			{
				if (TheTerrainLogic->slot47(&node->m_position))
				{
					reinterpret_cast<Rva00150700Owner *>(this)->reset();
					return false;
				}
				node = node->m_nextOpti;
			}
		}
	}
	return m_groundPath;
}

// Typed views of existing ILT addresses; the names make no semantic claim.
// 003F2160 consumes Object*, from*, to*, radius and returns with ret 16.
extern void j_00048c57(void);
// ?rva003F2160@Pathfinder@@QAEPAVPath@@PAVObject@@PBUCoord3D@@0H_N@Z absent-from-retail
__forceinline Path *Pathfinder::rva003F2160(Object *object,
	const Coord3D *from, const Coord3D *to, Int radius)
{
	typedef Path *(Pathfinder::*Call)(Object *, const Coord3D *, const Coord3D *, Int);
	union { void (*function)(void); Call member; } target;
	target.function = j_00048c57;
	return (this->*target.member)(object, from, to, radius);
}

// Independent caller 00177915 supplies TheAI in ECX before ILT 0003F990.
extern void j_0003f990(void);
// ?rva0014d120@AI@@QAEPAVObject@@PAV1@MHHH@Z absent-from-retail
__forceinline Object *AI::rva0014d120(Object *object, Real range, Int a, Int b, Int c)
{
	typedef Object *(AI::*Call)(Object *, Real, Int, Int, Int);
	union { void (*function)(void); Call member; } target;
	target.function = j_0003f990;
	return (this->*target.member)(object, range, a, b, c);
}

UnsignedInt AIGroup::getID( void )
{
	return m_id;
}

void AIGroup::groupAttackPosition(const Coord3D *pos, Int maxShotsToFire,
	CommandSourceType commandSource)
{
	Coord3D attackPos;
	if (pos)
		attackPos = *pos;

	std::list<Object *>::iterator i;
	for (i = m_memberList.begin(); i != m_memberList.end(); ++i)
	{
		if (!pos)
			attackPos.set((*i)->getPosition());

		ContainModuleInterface *contain = (*i)->getContain();
		if (contain && contain->isPassengerAllowedToFire())
		{
			const ContainedItemsList *items = contain->getContainedItemsList();
			if (items)
			{
				for (BfmeListNodeBase *it = items->head->next;
					it != items->head; it = it->next)
				{
					Object *garrisonedMember = ((BfmeObjectNode *)it)->value;
					CanAttackResult result =
						garrisonedMember->getAbleToAttackSpecificObject(
							ATTACK_NEW_TARGET, 0,
							(CommandSourceType)(unsigned int)&attackPos,
							(WeaponSlotType)commandSource);
					if (result == ATTACKRESULT_POSSIBLE
						|| result == ATTACKRESULT_POSSIBLE_AFTER_MOVING)
					{
						BfmeAIUpdateInterface *memberAI = garrisonedMember->m_ai;
						if (memberAI)
							memberAI->m_commands.aiAttackPosition(
								&attackPos, maxShotsToFire, commandSource);
					}
				}
			}
		}

		SpawnBehaviorInterface *spawnInterface =
			(*i)->getSpawnBehaviorInterface();
		if (spawnInterface)
			spawnInterface->orderSlavesToAttackPosition(
				&attackPos, maxShotsToFire, commandSource);

		BfmeAIUpdateInterface *ai = (*i)->m_ai;
		if (ai)
			ai->m_commands.aiAttackPosition(&attackPos, maxShotsToFire,
				commandSource);
	}
}
