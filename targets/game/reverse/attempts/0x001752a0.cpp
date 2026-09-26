// ?d_001752a0@@YAXXZ
// partial score=0.15 date=2026-09-23
// Retail 0x001752A0, 943 bytes. The owner remains address-derived.
// The three-argument cdecl ABI is witnessed by callers 0x00177A90 and 0x00182F70.
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include

#include <math.h>

typedef bool Bool;
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

enum KindOfType
{
	KINDOF_MELEE_HORDE_TARGET = 92
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
	void normalize();
};

class Rva001752A0Receiver {};

template<class T> __forceinline T Rva001752A0Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define CALL(T, obj, fn) (((Rva001752A0Receiver *)(obj))->*Rva001752A0Member<T>(fn))

class Module {};
class Weapon {};
class Pathfinder {};
class Object;
class TerrainLogic
{
public:
	int getLayerForDestination(Object *object, const Coord3D *position);
};
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const;
};

class AIData
{
	char m_pad000[0xd0];
public:
	float m_meleeOffset;
};

class AI
{
	char m_pad000[0x0c];
public:
	Pathfinder *m_pathfinder;
	char m_pad010[4];
	AIData *m_aiData;
};

class AIUpdateInterface
{
	char m_pad000[0x1a8];
};

class Object : public Thing
{
	char m_pad000[0x38];
public:
	Coord3D m_position;
	char m_pad044[0xbc - 0x44];
	float m_bfmeBC;
	char m_pad0c0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Module *findModule(NameKeyType key) const;
};

#define TheAI (*(AI **)0x012EF214)
#define TheTerrainLogic (*(TerrainLogic **)0x012EF4CC)
#define TheNameKeyGenerator (*(NameKeyGenerator **)0x012ED600)
#define Rva001752A0One (*(const float *)0x01075334)
#define Rva001752A0Zero (*(const float *)0x01075350)
#define Rva001752A0StepCount (*(const float *)0x010977E4)
#define Rva001752A0Twenty (*(const float *)0x010977E0)

extern void j_00048112();
extern void j_00032b46();
extern void j_0004a327();
extern void j_0007fbd();
extern void j_00011252();

typedef Bool (Rva001752A0Receiver::*ModuleIs)();
typedef Bool (Rva001752A0Receiver::*Check)(Object *, const Coord3D *, Weapon *, Bool);
typedef Bool (Rva001752A0Receiver::*SlowDoesPathExist)(Object *, const Coord3D *, const Coord3D *, int);
typedef int (Rva001752A0Receiver::*GetLayerForDestination)(Object *, const Coord3D *);
typedef int (Rva001752A0Receiver::*CellTypeFourWithFlag)(const Coord3D *, int);
typedef Bool (Rva001752A0Receiver::*AdjustDestination)(Object *, void *, Coord3D *);

bool Rva001752A0(Coord3D *destination, Object *source, Object *victim)
{
	AIUpdateInterface *sourceAI = source->m_ai;
	if (sourceAI == 0)
		return false;

	Coord3D victimPosition = *destination;
	float dx = destination->x - source->m_position.x;
	float dy = destination->y - source->m_position.y;
	float initialDistance = (float)sqrt(dx * dx + dy * dy);

	if (victim != 0)
	{
		victimPosition = victim->m_position;
		if (victim->isKindOf(KINDOF_MELEE_HORDE_TARGET))
		{
			static NameKeyType siegeDeploySpecialPowerKey =
				TheNameKeyGenerator->nameToKey("SiegeDeploySpecialPower");
			Module *module = victim->findModule(siegeDeploySpecialPowerKey);
			if (module != 0 && CALL(ModuleIs, module, j_00048112)())
				return true;
		}
	}

	Pathfinder *pathfinder = TheAI->m_pathfinder;
	Weapon *weapon = source->getCurrentWeapon(0);
	Bool pathCheck = CALL(Check, pathfinder, j_00032b46)(
		source, &victimPosition, weapon, false);
	if (pathCheck && CALL(SlowDoesPathExist, pathfinder, j_0004a327)(
		source, &source->m_position, destination, 0))
		return true;

	Coord3D step = *destination;
	Coord3D candidate = *destination;
	step.x -= source->m_position.x;
	step.y -= source->m_position.y;
	float distance = (float)sqrt(step.x * step.x + step.y * step.y);
	int limit = -1 - (int)(distance * Rva001752A0StepCount);
	float inverseDistance = Rva001752A0One / distance;
	step.x *= inverseDistance;
	step.y *= inverseDistance;
	step.z *= inverseDistance;
	step.x *= Rva001752A0Twenty;
	step.y *= Rva001752A0Twenty;
	step.z *= Rva001752A0Twenty;

	Bool specialCell = false;
	if (limit > 0)
	{
		int index = 0;
		while (index < limit)
		{
			candidate.x -= step.x;
			candidate.y -= step.y;
			candidate.z -= step.z;
			if (CALL(SlowDoesPathExist, pathfinder, j_0004a327)(
				source, &source->m_position, &candidate, 0))
				goto found;

			int layer = TheTerrainLogic->getLayerForDestination(source, &candidate);
			if (layer > 1 || CALL(CellTypeFourWithFlag, pathfinder, j_0007fbd)(
				&candidate, 1))
				specialCell = true;
			++index;
		}
	}
	return false;

found:
	Bool adjusted = false;
	if (specialCell && !pathCheck)
	{
		float offset = TheAI->m_aiData->m_meleeOffset + source->m_bfmeBC;
		step.normalize();
		step.x *= offset;
		step.y *= offset;
		step.z *= offset;
		candidate.x -= step.x;
		candidate.y -= step.y;
		candidate.z -= step.z;
		adjusted = true;
	}

	if (!adjusted)
	{
		float candidateDx = destination->x - candidate.x;
		float candidateDy = destination->y - candidate.y;
		float movedDistance = (float)sqrt(
			candidateDx * candidateDx + candidateDy * candidateDy);
		if (!(movedDistance + Rva001752A0Twenty <= initialDistance))
			return false;
	}

	CALL(AdjustDestination, pathfinder, j_00011252)(
		source, (char *)sourceAI + 0x1a8, &candidate);
	*destination = candidate;
	return true;
}
