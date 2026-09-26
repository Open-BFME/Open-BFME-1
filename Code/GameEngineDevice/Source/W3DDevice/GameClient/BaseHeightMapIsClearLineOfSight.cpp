// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME retail 0x006C63C0 (1082 bytes): BaseHeightMapRenderObjClass::isClearLineOfSight.
//
// Identity: W3DTerrainLogic vtable 0x0111D090 slot 15 (+0x3C, the TerrainLogic
// isClearLineOfSight slot the matched Weapon LOS callers use) is the 0x006BE210
// forwarder, which tail-jumps through ILT 0x00020923 to this body with
// TheTerrainRenderObject (0x012F7FE0) in ecx -- the ZH W3DTerrainLogic shape.
// BFME keeps the ZH Bresenham walk over m_map (+0x2FF4) directly, with 16-bit
// samples, drops the getMaxHeight early-out, and raises the sampled height to
// a bridge layer's surface via Pathfinder::getLayer and
// TerrainLogic::getLayerHeight.

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned short UnsignedShort;

#include <math.h>
#include <stdlib.h>

struct Coord3D { Real x, y, z; };

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

// BFME's REAL_TO_INT_FLOOR: CRT floor() then the engine's x87 round.
__forceinline Real fast_float_floor(Real f)
{
	return (Real)floor((double)f);
}

__forceinline long fast_float2long_round(Real f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))
#define __max(a,b) (((a) > (b)) ? (a) : (b))

#define MAP_XY_FACTOR 10.0f
#define MAP_HEIGHT_SCALE 0.0390625f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	Int getLayer(const Coord3D *pos);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder(void) { return m_pathfinder; }

private:
	unsigned char m_pad00[0x0C];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
// Only the getLayerHeight slot (+0x1C) is used; the others stay pure so this
// file manufactures no vtable.
class TerrainLogic
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
		Coord3D *normal = 0, Bool clip = true) const = 0;
};

extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/WorldHeightMap.h
class WorldHeightMap
{
public:
	Int getXExtent(void) { return m_width; }
	Int getYExtent(void) { return m_height; }
	Int getBorderSizeInline(void) const { return m_borderSize; }
	UnsignedShort *getDataPtr(void) { return m_data; }

private:
	char m_padding00[8];
	Int m_width;
	Int m_height;
	Int m_borderSize;
	char m_padding14[0x10];
	UnsignedShort *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/BaseHeightMap.h
class BaseHeightMapRenderObjClass
{
public:
	Bool isClearLineOfSight(const Coord3D& pos, const Coord3D& posOther) const;

private:
	char m_padding00[0x2ff4];
	WorldHeightMap *m_map;
};

Bool BaseHeightMapRenderObjClass::isClearLineOfSight(const Coord3D& pos, const Coord3D& posOther) const
{
	if (m_map == 0)
		return false;	// doh. should not happen.

	const Real MAP_XY_FACTOR_INV = 1.0f / MAP_XY_FACTOR;

	Int borderSize = m_map->getBorderSizeInline();
	Int start_x = REAL_TO_INT_FLOOR(pos.x * MAP_XY_FACTOR_INV) + borderSize;
	Int start_y = REAL_TO_INT_FLOOR(pos.y * MAP_XY_FACTOR_INV) + borderSize;
	Int end_x = REAL_TO_INT_FLOOR(posOther.x * MAP_XY_FACTOR_INV) + borderSize;
	Int end_y = REAL_TO_INT_FLOOR(posOther.y * MAP_XY_FACTOR_INV) + borderSize;
	Int delta_x = abs(end_x - start_x);			// The difference between the x's
	Int delta_y = abs(end_y - start_y);			// The difference between the y's
	Int x = start_x;												// Start x off at the first pixel
	Int y = start_y;												// Start y off at the first pixel

	Int xinc1, xinc2;
	if (end_x >= start_x)								// The x-values are increasing
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else																// The x-values are decreasing
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	Int yinc1, yinc2;
	if (end_y >= start_y)               // The y-values are increasing
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else																// The y-values are decreasing
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	Int den, num, numadd, numpixels;
	if (delta_x >= delta_y)							// There is at least one x-value for every y-value
	{
		xinc1 = 0;												// Don't change the x when numerator >= denominator
		yinc2 = 0;												// Don't change the y for every iteration
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;							// There are more x-values than y-values
	}
	else																// There is at least one y-value for every x-value
	{
		xinc2 = 0;												// Don't change the x for every iteration
		yinc1 = 0;												// Don't change the y when numerator >= denominator
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;							// There are more y-values than x-values
	}

	Real nsInv = 1.0f / numpixels;
	Real z = pos.z;
	Real dz = posOther.z - z;
	Real zinc = dz * nsInv;

	Bool sawGround = false;
	Bool result = true;
	const UnsignedShort* data = m_map->getDataPtr();
	Int xExtent = m_map->getXExtent();
	Int yExtent = m_map->getYExtent();
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		if (x < 0 ||
				y < 0 ||
				x >= xExtent-1 ||
				y >= yExtent-1)
		{
			// once we go off the map, we're done
			break;
		}

		Int layer = LAYER_GROUND;
		Coord3D cellCenter;
		if (TheAI && TheAI->pathfinder() && TheTerrainLogic)
		{
			cellCenter.x = (x - borderSize) * MAP_XY_FACTOR + MAP_XY_FACTOR / 2;
			cellCenter.y = (y - borderSize) * MAP_XY_FACTOR + MAP_XY_FACTOR / 2;
			cellCenter.z = 0.0f;
			layer = TheAI->pathfinder()->getLayer(&cellCenter);
		}

		Int idx = x + y*xExtent;
		float height = data[idx];
		height = __max(height, data[idx + 1]);
		height = __max(height, data[idx + xExtent]);
		height = __max(height, data[idx + xExtent + 1]);
		height *= MAP_HEIGHT_SCALE;

		if (layer != LAYER_GROUND)
		{
			if (sawGround)
			{
				Real layerHeight = TheTerrainLogic->getLayerHeight(cellCenter.x, cellCenter.y,
					(PathfindLayerEnum)layer, 0, true) - 20.0f;
				if (layerHeight > height)
					height = layerHeight;
			}
		}
		else
		{
			sawGround = true;
		}

		// if terrainHeight > z, we can't see, so punt.
		// add a little fudge to account for slop.
		const Real LOS_FUDGE = 0.5f;
		if (height > z + LOS_FUDGE)
		{
			result = false;
			break;
		}

		z += zinc;

		// continue with the maintenance.
		num += numadd;										// Increase the numerator by the top of the fraction
		if (num >= den)										// Check if numerator >= denominator
		{
			num -= den;											// Calculate the new numerator value
			x += xinc1;											// Change the x as appropriate
			y += yinc1;											// Change the y as appropriate
		}
		x += xinc2;												// Change the x as appropriate
		y += yinc2;												// Change the y as appropriate
	}

	return result;
}
