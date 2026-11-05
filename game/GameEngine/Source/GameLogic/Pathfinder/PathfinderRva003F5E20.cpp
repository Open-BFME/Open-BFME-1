// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc- /Igame/Libraries/Include /Igame/GameEngine/Source/GameLogic/Object
// Retail 0x003F5E20 (345 B, ret 0x10), reached through ILT 0x00032B46 from
// the attack-approach and move-to states with (Object*, goal Coord3D*,
// Weapon*, Bool). It builds the 0x003DB760 movement context for the object's
// locomotor set (AIUpdateInterface+0x1A8), then walks the cell line from the
// goal to each of its eight neighbours at attack range (at least 150) and
// reports whether any walk set the context's found flag. No Zero Hour twin;
// the method keeps an address-derived name.
typedef float Real;
typedef int Int;
typedef bool Bool;

#include "Lib/Coord3D.h"

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1 };

class LocomotorSet;
class Pathfinder;

#include "object.h"

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

class Rva001E1770ByteField
{
public:
	unsigned char get() const;
};

class WeaponTemplate;

class Weapon
{
public:
	Real getAttackRange(const Object *source, Real heightDifference) const;
	char m_fields[4];
	WeaponTemplate *m_template;
};

class Rva003DB760Config;

class Rva003DB760Context
{
public:
	Rva003DB760Context(void *a, Object *o, Rva003DB760Config *c, char d, char e);

	void *m_pathfinder;
	Object *m_object;
	LocomotorSet *m_locomotorSet;
	char m_info0C[0x0c];
	char m_found;
	char m_flag19;
	char m_flag1A;
	char m_flag1B;
	char m_flag1C;
};

struct Rva003F1CA0Struct : public Rva003DB760Context
{
	Rva003F1CA0Struct(void *a, Object *o, LocomotorSet *c, char d, char e)
		: Rva003DB760Context(a, o, (Rva003DB760Config *)c, d, e) {}
};

class Pathfinder
{
public:
	Bool rva003F5E20(Object *obj, const Coord3D *pos, Weapon *weapon, Bool option);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003F1CA0Struct *callbackInfo);
};

// ?rva003F5E20@Pathfinder@@QAE_NPAVObject@@PBUCoord3D@@PAVWeapon@@_N@Z
Bool Pathfinder::rva003F5E20(Object *obj, const Coord3D *pos, Weapon *weapon, Bool option)
{
	AIUpdateInterface *ai = obj->m_ai;
	if (ai == 0)
		return false;

	Real range = 150.0f;
	char flag = 0;
	if (weapon)
	{
		Real weaponRange = weapon->getAttackRange(obj, 0.0f);
		if (150.0f < weaponRange)
			range = weaponRange;
		flag = ((const Rva001E1770ByteField *)weapon->m_template)->get();
	}

	LocomotorSet *locomotorSet = (LocomotorSet *)((char *)ai + 0x1a8);
	Rva003F1CA0Struct info(this, obj, locomotorSet, flag, option);
	for (Int i = -1; i < 2; i++)
	{
		for (Int j = -1; j < 2; j++)
		{
			if (i == 0 && j == 0)
				continue;
			Coord3D samplePos;
			samplePos.x = pos->x;
			samplePos.y = pos->y;
			samplePos.z = pos->z;
			samplePos.x += i * range;
			samplePos.y += j * range;
			info.m_flag1A = 1;
			info.m_flag1B = 0;
			PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(0, pos);
			ICoord2D startCell;
			ICoord2D endCell;
			worldToCell(pos, &startCell);
			worldToCell(&samplePos, &endCell);
			iterateCellsAlongLine(startCell, endCell, layer, &info);
			if (info.m_found)
				return true;
		}
	}
	return false;
}
