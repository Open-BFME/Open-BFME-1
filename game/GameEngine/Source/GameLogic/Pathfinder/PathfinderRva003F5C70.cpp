// ?rva003f5c70@Pathfinder@@QAE_NPAVObject@@PAXPAUCoord3D@@@Z
// Retail 0x003F5C70 (335 bytes): the Pathfinder predicate that snaps a movement
// destination to a valid cell.  It refreshes the object's template override,
// shortcuts templates flagged 0x02000000, derives the search radius and
// centring from the object's template, converts the (possibly nudged)
// destination to a cell, then runs the radius-200 neighbour scan at 0x003F55E0
// over a 0x003E6200 info record carrying the destination layer height; on a hit
// (or an in-range fallback) it rewrites *dest through adjustCoordToCell.
//
// Identity is address-derived: the native spelling of this Pathfinder entry
// point is unknown, so it lands as Pathfinder::rva003f5c70.
// cl: /DWIN32 /D_WINDOWS /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /DNDEBUG /MD /EHsc /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath
// BANK ONLY: 003F5C70, 335 bytes exact modulo 12 relocation slots.
// Native coord.h POD and Object header plus visible native radius helper fix
// the historical EBX/EBP swap. No production or strict link claim is made.
// Remaining ABI debt: 003E6200 currently has an Int final parameter; retail
// supplies getLayerHeight's float directly, requiring independent callee audit.
// 003F55E0 is currently named as a free stdcall helper. Retail explicitly sets
// ECX to this at 003F5D52 before calling it; changing to that free declaration
// removes two bytes and fails. Do not add aliases to hide either mismatch.
// Actual RET12 is at 003F5DBC, followed by INT3 at 003F5DBF.
// This is the opaque three-argument method, not the old four-argument guess.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

extern "C" __declspec(dllimport) double __cdecl floor(double);

#include "coord.h"
#define BFME_HAVE_COORD3D



enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

// Retail 0x01075C74 is ?g_bfmeDirectionWeight1285@@3MB (data_rows.csv,
// AI/PathfinderDirectionWeight1285.cpp); g_pathfindCellSize was only a pin.
extern const float g_bfmeDirectionWeight1285;
#define g_pathfindCellSize g_bfmeDirectionWeight1285
// Retail 0x010977E0 is ?g_Rva010977E0@@3MB (data_rows.csv,
// AI/PathfinderCellConstants.cpp); g_pathfindDoubleCellSize was only a pin.
extern const float g_Rva010977E0;
#define g_pathfindDoubleCellSize g_Rva010977E0
extern const float g_rva01075350;
// Retail 0x01095F98 is ?g_Rva01095F98@@3MA (data_rows.csv,
// AI/PathfinderCellConstants.cpp); g_pathfindCellCenterBias was only a pin.
extern float g_Rva01095F98;
#define g_pathfindCellCenterBias g_Rva01095F98

// Template view read by getRadiusAndCenter (PathfindGetRadiusAndCenterE30.cpp).
class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride( void );

	BfmeOverridable *getFinalOverride( void )
	{
		if (m_override == 0) return this;
		return m_override->friend_getFinalOverride();
	}

	Int m_unknown00;
	BfmeOverridable *m_override;
	unsigned char m_pad08[0xc8 - 0x08];
	Int m_flagsC8;
	unsigned char m_padCC[0xd4 - 0xcc];
	Int m_flagsD4;
	unsigned char m_padD8[0x408 - 0xd8];
	Real m_level;
};


#define BFME_HAVE_OBJECTID
#define OBJECT_TU_MEMBERS ObjectID getID() const { return m_id; } Int getLayer() const;
#include "object.h"

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;

	PathfindLayerEnum getLayerForDestination(Object *obj,
		const Coord3D *pos);
};

extern TerrainLogic *TheTerrainLogic;

class Rva003F55E0
{
public:
	Bool call(const ICoord2D *center, Int radius, ICoord2D *found,
		void *userData);
};

class Rva003E6200Info
{
public:
	Rva003E6200Info(class Pathfinder *pathfinder, Object *obj, void *arg3,
		const Coord3D *pos, Real arg5);

	class Pathfinder * volatile m_pathfinder;
	Object * volatile m_obj;
	void * volatile m_arg3;
	Bool m_notComputer;
	Bool m_center;
	Int m_radius;
	PathfindLayerEnum m_layer;
	Int volatile m_arg5;
	Int m_pad1c;
	Int m_pad20;
	Int volatile m_zero24;
	volatile Coord3D m_pos;
};

class Pathfinder
{
public:
	Bool rva003f5c70(Object *obj, void *arg3, Coord3D *dest);
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);

protected:
	void getRadiusAndCenter(const Object *obj, Int &radius, Bool &center);
};

// Retail reaches adjustCoordToCell through the incremental-link thunk at RVA
// 0x000411D2 (the matched j_000411d2 row), not through the body at RVA
// 0x003D6040, so the call site encodes the raw thunk address and dispatches
// thiscall through a member-pointer union -- the same shape the sibling
// PathfinderCheckForTargetBfme.cpp uses for the identical call.
extern void j_000411d2(void);

class Rva003F5C70AdjustReceiver
{
};

typedef void (Rva003F5C70AdjustReceiver::*Rva003F5C70AdjustCall)(Int, Int, Bool,
	Coord3D &, PathfindLayerEnum);

static __forceinline void adjustCoordToCell(Pathfinder *self, Int x, Int y,
	Bool center, Coord3D &dest, PathfindLayerEnum layer)
{
	union
	{
		void (*raw)(void);
		Rva003F5C70AdjustCall member;
	} call;
	call.raw = j_000411d2;
	(reinterpret_cast<Rva003F5C70AdjustReceiver *>(self)->*call.member)(
		x, y, center, dest, layer);
}

Bool Pathfinder::rva003f5c70(Object *obj, void *arg3, Coord3D *dest)
{
	Object *object = obj;
	BfmeOverridable *objectTemplate = (BfmeOverridable *)object->m_template;
	if (objectTemplate && objectTemplate->m_override)
		objectTemplate = objectTemplate->getFinalOverride();
	if (objectTemplate->m_flagsC8 & 0x02000000)
		return true;

	Bool center;
	ICoord2D cell;
	{
		Coord3D adjusted;
		getRadiusAndCenter(object, (Int &)adjusted.x, center);
		adjusted.set(dest);
		if (!center)
		{
			adjusted.x += 5.0f;
			adjusted.y += 5.0f;
		}
		worldToCell(&adjusted, &cell);
	}

	Rva003E6200Info info(this, object, arg3, dest,
		TheTerrainLogic->getLayerHeight(dest->x, dest->y,
			TheTerrainLogic->getLayerForDestination(object, dest), 0, true));
	{
		ICoord2D found;
		if (((Rva003F55E0 *)this)->call(&cell, 200, &found, &info))
		{
			adjustCoordToCell(this, found.x, found.y, center, *dest,
				(PathfindLayerEnum)info.m_layer);
			return true;
		}
	}
	if (info.m_zero24)
	{
		adjustCoordToCell(this, info.m_pad1c, info.m_pad20, center, *dest,
			(PathfindLayerEnum)info.m_layer);
		return true;
	}
	return false;
}

__declspec(noinline) void Pathfinder::getRadiusAndCenter( const Object *object, Int &radius, Bool &centerInCell )
{
	Real diameter;
	Int maxRadius = 2;
	BfmeOverridable *t1 = ((BfmeOverridable *)object->m_template);
	if ((t1 == 0 ? t1 : t1->getFinalOverride())->m_flagsC8 & 0x400) {
		maxRadius = 4;
	} else {
		BfmeOverridable *t2 = ((BfmeOverridable *)object->m_template);
		if ((t2 == 0 ? t2 : t2->getFinalOverride())->m_flagsD4 & 0x1000) {
			maxRadius = 4;
		}
	}

	diameter = (*(const Real *)&object->m_geometryInfo[4]) * 2.0f;
	if (diameter > g_pathfindCellSize && diameter < g_pathfindDoubleCellSize) {
		diameter = 20.0f;
	}

	if ((((BfmeOverridable *)object->m_template) == 0 ? ((BfmeOverridable *)object->m_template) :
		((BfmeOverridable *)object->m_template)->getFinalOverride())->m_level > g_rva01075350) {
		diameter = (((BfmeOverridable *)object->m_template) == 0 ? ((BfmeOverridable *)object->m_template) :
		((BfmeOverridable *)object->m_template)->getFinalOverride())->m_level;
	}

	radius = REAL_TO_INT_FLOOR( diameter / 10.0f + g_pathfindCellCenterBias );
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

