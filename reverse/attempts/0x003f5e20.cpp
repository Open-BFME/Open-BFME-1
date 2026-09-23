// ?Rva003F5E20@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@PAVWeapon@@_N@Z
// partial score=0.28 date=2026-09-23
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/terrainlogic /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// ?Rva003F5E20@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@PAVWeapon@@_N@Z
#include "../../../Include/GameLogic/TerrainLogic.h"

class Object;
class AIUpdateInterface;
class LocomotorSet;
class Pathfinder;
class WeaponTemplate;

struct Rva001E1770ByteField
{
	char m_lead[0x4ed];
	unsigned char m_value;
	unsigned char get() const;
};

class Weapon
{
public:
	float getAttackRange(const Object *source, float heightDifference) const;
	char m_fields[4];
	WeaponTemplate *m_template;
};

struct BfmeMovementPositionInfo
{
	int m_surfaces;
	unsigned char m_field04;
	unsigned char m_allowAircraftGoal;
	unsigned char m_pad06[2];
	int m_maxLayer;
};

struct Rva003F1CA0Struct
{
	Pathfinder *m_pathfinder;
	Object *m_object;
	LocomotorSet *m_locomotorSet;
	BfmeMovementPositionInfo m_info;
	unsigned char m_found;
	unsigned char m_field19;
	unsigned char m_stepFailed;
	unsigned char m_field1B;
	unsigned char m_field1C;
};

class Pathfinder
{
public:
	bool Rva003F5E20(Object *source, const Coord3D *target, Weapon *weapon,
		bool option);
	bool worldToCell(const Coord3D *world, ICoord2D *cell);
	int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003F1CA0Struct *userData);
};

extern void j_0001536b();
extern void j_00027c2d();
extern void j_00028f74();

template<class Receiver, class Member>
__forceinline Member Rva003F5E20Member(void (*raw)())
{
	union { void (*raw)(); Member member; } function;
	function.raw = raw;
	return function.member;
}

#define CALL(Receiver, Member, object, function) \
	(((Receiver *)(object))->*Rva003F5E20Member<Receiver, Member>(function))

typedef float (Weapon::*Rva003F5E20GetAttackRange)(const Object *, float) const;
typedef unsigned char (Rva001E1770ByteField::*Rva003F5E20GetByte)() const;
typedef void (Rva003F1CA0Struct::*Rva003DB760Initialize)(Pathfinder *, Object *,
	LocomotorSet *, bool, bool);

bool Pathfinder::Rva003F5E20(Object *source, const Coord3D *target,
	Weapon *weapon, bool option)
{
	AIUpdateInterface *ai = *(AIUpdateInterface **)((char *)source + 0x204);
	if (ai)
	{
	float range = 150.0f;
	volatile unsigned char rangeFlag = 0;
	if (weapon)
	{
		float weaponRange = CALL(Weapon, Rva003F5E20GetAttackRange, weapon,
			j_0001536b)(source, 0.0f);
		if (*(const float *)0x0109A028 < weaponRange)
			range = weaponRange;
		rangeFlag = CALL(Rva001E1770ByteField, Rva003F5E20GetByte,
			weapon->m_template, j_00028f74)();
	}

	int x;
	int y;
	ICoord2D sampleCell;
	ICoord2D targetCell;
	Coord3D sample;
	Rva003F1CA0Struct info;
	LocomotorSet *locomotorSet = (LocomotorSet *)((char *)ai + 0x1a8);
	CALL(Rva003F1CA0Struct, Rva003DB760Initialize, &info, j_00027c2d)(
		this, source, locomotorSet, rangeFlag, option);

	x = -1;
	do
	{
		y = -1;
		do
		{
			if (x != 0 || y != 0)
			{
				sample.x = target->x + x * range;
				sample.y = target->y + y * range;
				sample.z = target->z;
				PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(
					0, target);
				worldToCell(target, &targetCell);
				worldToCell(&sample, &sampleCell);
				iterateCellsAlongLine(targetCell, sampleCell, layer, &info);
				if (info.m_found)
					return true;
			}
			++y;
		} while (y < 2);
		++x;
	} while (x < 2);
	}
	return false;
}
