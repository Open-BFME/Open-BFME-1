// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003EA980, 501 bytes.
//
// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
// -- the four-argument attack line-of-sight test, reached through the ILT
// thunk 0x00023042 by the named Pathfinder callers (AIStates.cpp's
// ?updateInternal@AIAttackApproachTargetState and the two forwarder bodies in
// game/GameEngine/Source/GameLogic/AI/PathfinderAttackViewForwarders.cpp).
// The BFME source is GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp;
// game/GameEngine/Source/GameLogic/AI/AIPathfind.cpp holds the Zero Hour twin,
// which has no attacker-template flag test, no bridge-layer range check and
// no TerrainLogic elevation comparison, so its body cannot stand here.
//
// This body is its own TU because three of the facts it needs are BFME
// layouts the Zero Hour headers get wrong: TAiData::m_attackUsesLineOfSight
// sits at +0x67 here (ZH's AI.h puts it at +0x6b), Object::m_template is at
// +0x04, and ThingTemplate::m_kindOfFlags is at +0xCC. Reusing the shared
// header would move every sibling body that already matches under it.
//
// The class declarations below are private to this file and spell only the
// layout this body reads. Every offset is witnessed elsewhere in the tree:
//   Object::m_template +0x04, BfmeThingTemplate::m_nextOverride +0x04 and
//     m_kindOfFlags +0xCC  -- AIWanderState_update_Bfme.cpp:90-96
//   ObstacleCellStruct's seven fields  -- PathfindObstacleCallbackDebb0.cpp:114
//   TAiData::m_attackUsesLineOfSight    -- the body at 0x003EA980 itself
// The class names are upstream's (Thing/Object/Weapon/TerrainLogic/Pathfinder);
// the body only ever dereferences the offsets above, and each callee it names
// is declared with the exact mangled spelling retail's own call sites use, so
// the emitted REL32 targets are the ones the ledger already pins.  Four of
// those spellings had to match the tree's existing name for the address, not
// what this body would otherwise mangle to:
//
//   getFinalOverride     Overridable, not a BfmeThingTemplate member
//   getLayer             Object (0x0003A391), not Thing
//   getLayerForDestination  non-const (QAE), the owner at 0x001A7C20
//   ObstacleCellStruct   `struct`, because MSVC puts the class/struct tag in
//                        the mangled name (PAU vs PAV)
//
// Each of those names already resolves to a matched body in the tree, so no
// pin was added for any callee of this function.

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class PathfindCell;

// The chain walk is Overridable::getFinalOverride, the name the tree already
// owns at 0x00087A80 (game/GameEngine/Source/Common/INI/INIWater.cpp).  The
// template inherits it, so the call mangles to that spelling and links to the
// matched body instead of dangling.
class Overridable
{
public:
	void *m_vptr;
	const Overridable *getFinalOverride() const;
};

// retail tests the final override's kind-of word against 0x04000000: the
// attacker must need line of sight before this method will report a block.
class BfmeThingTemplate : public Overridable
{
public:
	BfmeThingTemplate *m_nextOverride;
	unsigned char m_pad08[0xc4];
	unsigned int m_kindOfFlags;
};

class Thing
{
public:
	void *m_vptr;

	Bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	BfmeThingTemplate *m_template;

	Int getLayer() const;
};

// BFME reaches the attacker's weapon through this shim's find(0), not through
// Object::getCurrentWeapon(); the call at +0x0050 passes the attacker itself
// with a literal 0 slot.
class AssistedTargetingObjectShim
{
public:
	void *find(Int slot);
};

class Weapon
{
public:
	Bool isClearGoalFiringLineOfSightTerrain(const Object *attacker,
		const Coord3D &attackerPos, const Object *victim) const;
	Bool isClearGoalFiringLineOfSightTerrain(const Object *attacker,
		const Coord3D &attackerPos, const Coord3D &victimPos) const;
};

// The walk payload: seven fields, written here and consumed by the matched
// ObstacleCellStruct::cellCallback at 0x003DEBB0.  Spelled `struct` because
// the tree's 0x003E7E60 forwarder declares it that way, and MSVC puts the
// class/struct tag in the mangled name (PAU vs PAV).
struct ObstacleCellStruct
{
public:
	Bool cellCallback(PathfindCell *previousCell, PathfindCell *currentCell,
		Int currentCellX, Int currentCellY);

	const Object *m_obj;			// 0x00
	const Object *m_other;			// 0x04
	PathfindCell *m_cell;			// 0x08
	Int m_skip;						// 0x0c
	Bool m_hitLayer;				// 0x10
	Int m_layerCount;				// 0x14
	Int m_runLength;				// 0x18
};

class AIData
{
public:
	char m_padding00[0x67];
	unsigned char m_attackUsesLineOfSight;
};

class AI
{
public:
	char m_padding00[0x14];
	AIData *m_aiData;

	AIData *getAiData() const
	{
		return m_aiData;
	}
};

extern AI *TheAI;

// The non-const spelling is the one the tree owns at 0x001A7C20
// (TerrainLogicGetLayerForDestinationObject.cpp); the const overload would
// mangle to a name nothing resolves.
class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *attacker,
		const Coord3D &attackerPos, const Object *victim, const Coord3D &victimPos);

	PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *position);
	Int iterateCellsAlongLine(const Coord3D &start, const Coord3D &end,
		PathfindLayerEnum layer, ObstacleCellStruct *userData);
};

// BFME's rewrite of the Zero Hour body. Four things changed, and each one is
// visible in the bytes:
//
//   1. the attacker's final template override must carry the line-of-sight
//      kind-of bit (+0x0035), which ZH's isKindOf() call does not;
//   2. the weapon comes from the AssistedTargetingObjectShim slot 0 and is
//      dropped outright for an immobile attacker, because it cannot move
//      around terrain (+0x0050, +0x0060);
//   3. when the two objects sit on different pathfind layers, retail asks
//      TerrainLogic which layer each end of the shot resolves to, using the
//      higher of the two elevations so a bridge does not answer for the
//      ground under it, and reports a block when both ends agree (+0x00CF on);
//   4. the elevation itself is compared with a bare fcomp, so the source
//      spells the maximum rather than calling a max() helper.
Bool Pathfinder::isAttackViewBlockedByObstacle(const Object *attacker,
	const Coord3D &attackerPos, const Object *victim, const Coord3D &victimPos)
{
	// Global switch to turn this off in case it doesn't work.
	if (!TheAI->getAiData()->m_attackUsesLineOfSight)
		return false;

	// If the attacker doesn't need line of sight, isn't blocked.
	const BfmeThingTemplate *thing = attacker->m_template;
	if (thing != 0 && thing->m_nextOverride != 0)
		thing = (const BfmeThingTemplate *)thing->m_nextOverride->getFinalOverride();
	if ((thing->m_kindOfFlags & 0x04000000) == 0)
		return false;

	// Take terrain blockage into account, but not for an immobile attacker:
	// it cannot move around what blocks it.
	Weapon *w = (Weapon *)((AssistedTargetingObjectShim *)attacker)->find(0);
	if (attacker->isKindOf(KINDOF_IMMOBILE))
		w = 0;
	if (w != 0)
	{
		Bool viewBlocked;
		if (victim != 0)
			viewBlocked = !w->isClearGoalFiringLineOfSightTerrain(attacker, attackerPos, victim);
		else
			viewBlocked = !w->isClearGoalFiringLineOfSightTerrain(attacker, attackerPos, victimPos);
		if (viewBlocked)
			return true;
	}

	Int attackerLayer = attacker->getLayer();
	PathfindLayerEnum layer = LAYER_GROUND;
	if (victim != 0)
	{
		layer = (PathfindLayerEnum)victim->getLayer();
		if (attackerLayer != layer)
		{
			// Only bridge and wall layers (2..15) can answer differently to the
			// layer the terrain reports, so anything else skips the query.
			if ((attackerLayer >= 2 && attackerLayer <= 15) || (layer >= 2 && layer <= 15))
			{
				Real z = attackerPos.z;
				if (victimPos.z > z)
					z = victimPos.z;

				Coord3D pos;
				pos.x = attackerPos.x;
				pos.y = attackerPos.y;
				pos.z = z;
				PathfindLayerEnum attackerTerrainLayer =
					TheTerrainLogic->getLayerForDestination(0, &pos);

				pos = victimPos;
				pos.z = z;
				PathfindLayerEnum victimTerrainLayer =
					TheTerrainLogic->getLayerForDestination(0, &pos);

				// Both ends resolve to the same terrain layer, so the layer
				// difference is not what separates the shot: it is blocked.
				if (attackerTerrainLayer == victimTerrainLayer)
					return true;
			}
		}
	}

	ObstacleCellStruct info;
	info.m_other = victim;
	info.m_obj = attacker;
	info.m_cell = getCell(layer, &victimPos);
	info.m_skip = 0;
	info.m_hitLayer = false;
	info.m_layerCount = 0;
	info.m_runLength = 0;

	// Someone on a bridge or a rooftop can see 3 pathfind cells out from
	// whatever they are standing on.
	Int elevated = attacker->getLayer();
	if (elevated != LAYER_GROUND && elevated < 16)
	{
		info.m_skip = 3;
		if (layer == LAYER_GROUND)
			layer = (PathfindLayerEnum)attacker->getLayer();
	}

	Int ret = iterateCellsAlongLine(attackerPos, victimPos, layer, &info);
	return ret != 0;
}
