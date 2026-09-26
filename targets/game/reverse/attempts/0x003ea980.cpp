// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
// partial score=0.65 date=2026-09-11
// cl: /DNDEBUG /MD /EHsc

typedef int Int;
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

class BfmeOverridable
{
public:
	void *m_vtable;
	BfmeOverridable *m_next;
	char m_padding08[0xc4];
	unsigned int m_kindOf;

	const BfmeOverridable *getFinalOverride() const;
};

class Thing
{
public:
	void *m_vtable;

	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	BfmeOverridable *m_template;

	int getLayer() const;
};

class Weapon
{
public:
	bool isClearGoalFiringLineOfSightTerrain(const Object *attacker,
		const Coord3D &attackerPos, const Object *victim) const;
	bool isClearGoalFiringLineOfSightTerrain(const Object *attacker,
		const Coord3D &attackerPos, const Coord3D &victimPos) const;
};

class AssistedTargetingObjectShim
{
public:
	void *find(int slot);
};

struct ViewAttackBlockedStruct
{
	const Object *obj;
	const Object *victim;
	const PathfindCell *victimCell;
	Int skipCount;
};

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *attacker,
		const Coord3D &attackerPos, const Object *victim,
		const Coord3D &victimPos);
	PathfindCell *getCell(PathfindLayerEnum layer, const Coord3D *position);
	Int iterateCellsAlongLine(const Coord3D &start, const Coord3D &end,
		PathfindLayerEnum layer, ViewAttackBlockedStruct *info);
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

// The retail address, the named caller, and the matched line-walk helpers
// identify this four-argument Pathfinder attack visibility test.
Bool Pathfinder::isAttackViewBlockedByObstacle(const Object *attacker,
	const Coord3D &attackerPos, const Object *victim,
	const Coord3D &victimPos)
{
	ViewAttackBlockedStruct info;
	if (!TheAI->getAiData()->m_attackUsesLineOfSight)
		return false;

	const BfmeOverridable *objectTemplate = attacker->m_template;
	if (objectTemplate == 0 || objectTemplate->m_next == 0)
		return false;
	objectTemplate = objectTemplate->m_next->getFinalOverride();
	if ((objectTemplate->m_kindOf & 0x04000000) == 0)
		return false;

	AssistedTargetingObjectShim *weaponSource =
		(AssistedTargetingObjectShim *)(Object *)attacker;
	Weapon *weapon = (Weapon *)weaponSource->find(0);
	if (attacker->isKindOf(KINDOF_IMMOBILE))
		weapon = 0;
	if (weapon != 0)
	{
		Bool viewBlocked;
		if (victim != 0)
			viewBlocked = !weapon->isClearGoalFiringLineOfSightTerrain(
				attacker, attackerPos, victim);
		else
			viewBlocked = !weapon->isClearGoalFiringLineOfSightTerrain(
				attacker, attackerPos, victimPos);
		if (viewBlocked)
			return true;
	}

	int attackerLayer = attacker->getLayer();
	int victimLayer = LAYER_GROUND;
	if (victim != 0)
	{
		victimLayer = victim->getLayer();
		if (attackerLayer == victimLayer)
			return false;
		if (attackerLayer < 2 || attackerLayer > 15 ||
			victimLayer < 2 || victimLayer > 15)
			return false;
	}

	info.obj = attacker;
	info.victim = victim;
	info.victimCell = getCell((PathfindLayerEnum)victimLayer, &victimPos);
	info.skipCount = 0;
	if (attackerLayer != LAYER_GROUND)
	{
		info.skipCount = 3;
		if (victimLayer == LAYER_GROUND)
			victimLayer = attackerLayer;
	}

	Int ret = iterateCellsAlongLine(attackerPos, victimPos,
		(PathfindLayerEnum)victimLayer,
		&info);
	return ret != 0;
}
