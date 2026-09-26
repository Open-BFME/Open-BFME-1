// ?getLayerHeight@W3DTerrainLogic@@UBEMMMW4PathfindLayerEnum@@PAUCoord3D@@_N@Z
// BFME retail 0x006BE2A0 (267 bytes).
//
// The retail slot is W3DTerrainLogic's layer-height implementation (vtable
// 0x0111D090, slot 7).  The >= LAYER_WALL path delegates to the named
// Pathfinder::getLayerHeight body at 0x003D8940 through ILT 0x00029F3C.
// The lower-layer path uses W3DTerrainLogic::findBridgeLayerAt at vtable
// slot 39, Bridge::getBridgeHeight at ILT 0x0000B802, and the already matched
// bounded-value accessor at 0x003D5BF0 when no bridge is present.

typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_GROUND = 1,
	LAYER_WALL = 0x10
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Bridge
{
public:
	Real getBridgeHeight(const Coord3D *point, Coord3D *normal);
};

class Pathfinder
{
public:
	Real getLayerHeight(PathfindLayerEnum layer, const Coord3D *point,
		Coord3D *normal);
};

// The retail body at RVA 0x003D5BF0 is already tracked under this neutral
// address view.  Its owning class is not established by the layer-height
// evidence, so do not give the fallback a Pathfinder member identity.
class Gen_003D5BF0
{
public:
	Real value(int index) const;
};

class AI
{
public:
	Pathfinder *pathfinder(void) const
	{
		return *(Pathfinder **)((const unsigned char *)this + 0x0c);
	}
};

extern AI *TheAI;
extern const Real BfmeZeroRange;

// BaseHeightMapRenderObjClass::getHeightMapHeight is the retail virtual at
// +0x248.  This declaration is intentionally only a vtable slice; the TU
// never constructs it, so it does not emit a replacement vtable.
#define UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0() = 0; virtual void prefix##1() = 0; \
	virtual void prefix##2() = 0; virtual void prefix##3() = 0; \
	virtual void prefix##4() = 0; virtual void prefix##5() = 0; \
	virtual void prefix##6() = 0; virtual void prefix##7() = 0; \
	virtual void prefix##8() = 0; virtual void prefix##9() = 0; \
	virtual void prefix##a() = 0; virtual void prefix##b() = 0; \
	virtual void prefix##c() = 0; virtual void prefix##d() = 0; \
	virtual void prefix##e() = 0; virtual void prefix##f() = 0

class BaseHeightMapRenderObjClass
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	UNUSED_VIRTUALS_16(unused0c0_);
	UNUSED_VIRTUALS_16(unused100_);
	UNUSED_VIRTUALS_16(unused140_);
	UNUSED_VIRTUALS_16(unused180_);
	UNUSED_VIRTUALS_16(unused1c0_);
	UNUSED_VIRTUALS_16(unused200_);
	virtual void unused240_0() = 0;
	virtual void unused240_1() = 0;
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

// W3DTerrainLogic::findBridgeLayerAt is the retail virtual at +0x9c.  The
// other slots remain pure and declaration-only to avoid manufacturing a
// vtable in this source file.
class W3DTerrainLogic
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer,
		Coord3D *normal, Bool clip) const;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual void unused28() = 0;
	virtual void unused2c() = 0;
	virtual void unused30() = 0;
	virtual void unused34() = 0;
	virtual void unused38() = 0;
	virtual void unused3c() = 0;
	virtual void unused40() = 0;
	virtual void unused44() = 0;
	virtual void unused48() = 0;
	virtual void unused4c() = 0;
	virtual void unused50() = 0;
	virtual void unused54() = 0;
	virtual void unused58() = 0;
	virtual void unused5c() = 0;
	virtual void unused60() = 0;
	virtual void unused64() = 0;
	virtual void unused68() = 0;
	virtual void unused6c() = 0;
	virtual void unused70() = 0;
	virtual void unused74() = 0;
	virtual void unused78() = 0;
	virtual void unused7c() = 0;
	virtual void unused80() = 0;
	virtual void unused84() = 0;
	virtual void unused88() = 0;
	virtual void unused8c() = 0;
	virtual void unused90() = 0;
	virtual void unused94() = 0;
	virtual void unused98() = 0;
	virtual Bridge *findBridgeLayerAt(const Coord3D *point,
		PathfindLayerEnum layer, Bool clip) const;
};

extern void j_00029f3c(void);
extern void j_000280fb(void);

Real W3DTerrainLogic::getLayerHeight(Real x, Real y,
	PathfindLayerEnum layer, Coord3D *normal, Bool clip) const
{
	if (normal)
	{
		normal->x = 0.0f;
		normal->y = 0.0f;
		normal->z = 1.0f;
	}
	if (TheTerrainRenderObject == 0)
		return BfmeZeroRange;

	if (layer != LAYER_GROUND)
	{
		Coord3D loc;
		loc.x = x;
		loc.y = y;
		loc.z = 0.0f;

		if (layer >= LAYER_WALL)
		{
			Pathfinder *pathfinder = TheAI->pathfinder();
			typedef Real (Pathfinder::*LayerHeightThunk)(PathfindLayerEnum,
				const Coord3D *, Coord3D *);
			union
			{
				void (*function)(void);
				LayerHeightThunk member;
			} layerHeightThunk;
			layerHeightThunk.function = j_00029f3c;
			return (pathfinder->*layerHeightThunk.member)(layer, &loc, normal);
		}

		Bridge *bridge = findBridgeLayerAt(&loc, layer, clip);
		if (bridge != 0)
		{
			Real bridgeHeight = bridge->getBridgeHeight(&loc, normal);
				Real height = TheTerrainRenderObject->getHeightMapHeight(x, y, normal);
				if (bridgeHeight > height)
					return bridgeHeight;
			}
		else
		{
			Pathfinder *pathfinder = TheAI->pathfinder();
			Gen_003D5BF0 *valueTable = (Gen_003D5BF0 *)pathfinder;
			typedef Real (Gen_003D5BF0::*ValueThunk)(int) const;
			union
			{
				void (*function)(void);
				ValueThunk member;
			} thunk;
			thunk.function = j_000280fb;
			return (valueTable->*thunk.member)((int)layer);
		}
	}

	return TheTerrainRenderObject->getHeightMapHeight(x, y, normal);
}

#undef UNUSED_VIRTUALS_16
