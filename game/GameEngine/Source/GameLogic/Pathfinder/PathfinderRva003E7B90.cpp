// cl: /DNDEBUG /MD /Igame/Libraries/Include/Lib
// Evidence: targets/game/reverse/identity_evidence/003e7b90-coordinate-lifetime.md
// Address-named Pathfinder movement predicate with visible radius calculation.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char Bool;
typedef float Real;

#include "Coord3D.h"

struct Rva003E7B90CoordCopy : Coord3D
{
	// ??0Rva003E7B90CoordCopy@@QAE@ABUCoord3D@@@Z absent-from-retail
	Rva003E7B90CoordCopy(const Coord3D &other) { x=other.x; y=other.y; z=other.z; }
	// ??0Rva003E7B90CoordCopy@@QAE@ABU0@@Z absent-from-retail
	Rva003E7B90CoordCopy(const Rva003E7B90CoordCopy &other) { x=other.x; y=other.y; z=other.z; }
	// ??1Rva003E7B90CoordCopy@@QAE@XZ absent-from-retail
	~Rva003E7B90CoordCopy() {}
};
typedef char Rva003E7B90CoordCopySize[(sizeof(Rva003E7B90CoordCopy) == 12) ? 1 : -1];

extern void j_000441cf();
extern void j_00042249();

struct ICoord2D
{
	Int x;
	Int y;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_GROUND = 1
};

struct BfmeMovementPositionInfo
{
	UnsignedInt m_surfaces;
	Bool m_allowAircraftGoal;
	Bool m_computerControlled;
	Bool m_pad06[2];
	Int m_maxLayer;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);
	// ?getNextOverride@BfmeOverridable@@QBEPAV1@XZ absent-from-retail
	BfmeOverridable *getNextOverride(void) const
	{
		return m_nextOverride;
	}

private:
	void *m_vtable;
	BfmeOverridable *m_nextOverride;
};

class BfmeThingTemplate
{
public:
	unsigned char m_opaque000[0xc8];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
	unsigned char m_pad40C[0x444 - 0x40c];
	Int m_pathfindMaxLayer;
	unsigned char m_opaque448[0x4cc - 0x448];
	Bool m_aircraftGoalFlag;
};

template <class T>
class BfmeOverride
{
public:
	// ??C?$BfmeOverride@VBfmeThingTemplate@@@@QBEPBVBfmeThingTemplate@@XZ absent-from-retail
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		BfmeOverridable *next = m_overridable->getNextOverride();
		if (next)
			return (const T *)next->friend_getFinalOverride();
		return (const T *)m_overridable;
	}

private:
	BfmeOverridable *m_overridable;
};

struct AIUpdateInterface
{
	unsigned char m_pad000[0x1b8];
	UnsignedInt m_validSurfaces;
};

class Object
{
public:
	bool bfmeIsComputerControlled(void) const;

	// ?getTemplate@Object@@QBEPBVBfmeThingTemplate@@XZ absent-from-retail
	const BfmeThingTemplate *getTemplate(void) const
	{
		return m_template.operator->();
	}

	void *m_vtable;
	BfmeOverride<BfmeThingTemplate> m_template;
	unsigned char m_pad008[0xbc - 8];
	Real m_boundingCircleRadius;
	unsigned char m_padC0[0x204 - 0xc0];
	AIUpdateInterface *m_ai;
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *object,
		const Coord3D *position);
};

extern TerrainLogic *TheTerrainLogic;

class PathfindCell
{
public:
	unsigned char m_pad00[0xc];
	UnsignedInt m_word;
};

class Pathfinder
{
protected:
	void getRadiusAndCenter(const Object *object, Int &radius, bool &centerInCell);
public:
	Bool sameCell(Object *object, Coord3D from, Coord3D to);
	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	void bfmeQuery(Object *object, Int *radius, Bool *center);
	bool worldToCell(const Coord3D *position, ICoord2D *cell);
	bool bfmeStepD4F90(void *state, PathfindCell *cell);
	Bool rva003e7b90(Object *object, const Coord3D *layerPosition,
		const Coord3D *from, const Coord3D *to);
};

extern bool rva3d5170(Int value);

extern "C" __declspec(dllimport) double __cdecl floor( double );

// ?fast_float2long_round@@YAJM@Z absent-from-retail
__forceinline long fast_float2long_round( float value )
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

extern const float g_bfmeDirectionWeight1285;
extern const float g_Rva010977E0;
extern const float g_rva01075350;
extern float g_Rva01095F98;


// ?getRadiusAndCenter@Pathfinder@@IAEXPBVObject@@AAHAA_N@Z
inline __declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	const BfmeThingTemplate *t1 = object->getTemplate();
	if (t1->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		const BfmeThingTemplate *t2 = object->getTemplate();
		if (t2->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = object->m_boundingCircleRadius * 2.0f;
	if (diameter > g_bfmeDirectionWeight1285 && diameter < g_Rva010977E0) {
		diameter = 20.0f;
	}

	if (object->getTemplate()->m_level > g_rva01075350) {
		diameter = object->getTemplate()->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_Rva01095F98 );
	centerInCell = false;
	if (radius == 0) radius++;
	if (radius & 1) {
		centerInCell = true;
	}
	radius /= 2;
	if (radius > maxRadius) {
		radius = maxRadius;
		centerInCell = true;
	}
}

// ?rva003e7b90@Pathfinder@@QAEEPAVObject@@PBUCoord3D@@11@Z
Bool Pathfinder::rva003e7b90(Object *object,
	const Coord3D *layerPosition, const Coord3D *from,
	const Coord3D *to)
{
	Pathfinder *pathfinder = this;
	Object *obj = object;
	typedef Bool (Pathfinder::*SameCell)(Object *, Rva003E7B90CoordCopy, Rva003E7B90CoordCopy);
	union { void (*fn)(); SameCell call; } same = { j_000441cf };
	if (!(pathfinder->*same.call)(obj, Rva003E7B90CoordCopy(*from), Rva003E7B90CoordCopy(*to)))
	{
		Int maxLayer = obj->getTemplate()->m_pathfindMaxLayer;
		Bool aircraftGoal = obj->getTemplate()->m_aircraftGoalFlag;
		AIUpdateInterface *ai = obj->m_ai;
		Bool computerControlled = obj->bfmeIsComputerControlled();
		UnsignedInt surfaces = ai->m_validSurfaces;

		BfmeMovementPositionInfo info;
		info.m_surfaces = surfaces;
		info.m_allowAircraftGoal = aircraftGoal == 0;
		info.m_computerControlled = computerControlled;
		info.m_maxLayer = maxLayer - 1;

		PathfindLayerEnum layer =
			TheTerrainLogic->getLayerForDestination(obj, from);

		Int radius;
		Bool center;
		getRadiusAndCenter(obj, radius, reinterpret_cast<bool &>(center));

		Coord3D adjusted = *from;
		if (!center)
		{
			adjusted.x += 5.0f;
			adjusted.y += 5.0f;
		}

		ICoord2D cell;
		PathfindCell *pathCell;
		if (worldToCell(&adjusted, &cell))
			pathCell = 0;
		else
		{
			typedef PathfindCell *(Pathfinder::*CellLookup)(PathfindLayerEnum, Int, Int);
			union { void (*fn)(); CellLookup call; } lookup = { j_00042249 };
			pathCell = (pathfinder->*lookup.call)(layer, cell.x, cell.y);
		}

		if (!bfmeStepD4F90(&info, pathCell))
			return false;

		PathfindLayerEnum targetLayer =
			TheTerrainLogic->getLayerForDestination(obj, layerPosition);
		if (targetLayer == layer)
			goto success;

		UnsignedInt word = pathCell->m_word;
		Int connection = (word >> 12) & 0x3f;
		if (connection == 0)
			return false;
		Int cellLayer = (word >> 6) & 0x3f;
		if (cellLayer == targetLayer && connection != layer)
			return false;
		if (connection == targetLayer && cellLayer != layer)
			return false;

		if (targetLayer != 1)
		{
			if (targetLayer == 0x10)
				goto success;
			if (!rva3d5170(targetLayer))
				goto success;
		}
		if (layer == 0x10)
			goto success;
		return false;
	}

success:
	return true;
}
