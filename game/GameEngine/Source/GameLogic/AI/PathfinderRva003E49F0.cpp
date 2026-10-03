// cl: /DNDEBUG /MD /Igame/GameEngine/Source/GameLogic/Object /Igame/Libraries/Source/WWVegas/WWMath
// Retail 003E49F0: 753-byte address-named Pathfinder method.
// Matched caller 003EA570 reaches ILT00005484 with Object, position and IDs.
// Native radius helper visibility permits its output slot to expire before
// the floor temporaries and loop bounds. Both this body and the 297-byte
// helper reproduce retail. The fld/fistp helper is the established x87 blocker.
// Evidence: targets/game/reverse/identity_evidence/003e49f0-radius-lifetime.md

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

extern "C" __declspec(dllimport) double __cdecl floor(double);

#include "coord3d.h"
struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };

inline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

inline float fast_float_floor(float f)
{
	return (float)floor(f);
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round(fast_float_floor(x)))

extern const Real g_pathfindCellSize;
extern const Real g_pathfindDoubleCellSize;
extern const float g_rva01075350;
extern const Real g_pathfindCellCenterBias;

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

class PathfindCellInfo
{
public:
	unsigned char m_prefix[0x14];
	ObjectID m_goalUnitID;
	ObjectID m_posUnitID;
	ObjectID m_bfme1C;
	ObjectID m_bfme20;
};

class PathfindCell
{
public:
	ObjectID getPosUnit( void ) const { ObjectID id = m_info ? m_info->m_posUnitID : INVALID_ID; return id; }
	ObjectID getBfme20( void ) const { return m_info ? m_info->m_bfme20 : INVALID_ID; }

	PathfindCellInfo *m_info;
	Int m_unused1;
	Int m_unused2;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *rva003FBB20( Int cellX, Int cellY );
	PathfindCell *getCell( Int cellX, Int cellY );

private:
	unsigned char m_body[0x44];
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40();
	virtual Bool queryObjectLayer( Object *object, Int layer );
};

extern TerrainLogic *TheTerrainLogic;

class Pathfinder
{
public:
	Int rva003E49F0( Object *obj, Coord3D *pos, void *cellIds );
	Int rva003E4680( Object *obj, Coord3D *pos, void *cellIds );
	PathfindCell *getCell003E4680( PathfindLayerEnum layer, Int cellX, Int cellY )
	{
		if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
			cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
		{
			if (layer > LAYER_GROUND && layer <= LAYER_LAST)
			{
				PathfindCell *cell = m_layers[layer].getCell( cellX, cellY );
				if (cell)
					return cell;
			}
			return &m_map[cellX][cellY];
		}
		return 0;
	}
	PathfindCell *getCell( PathfindLayerEnum layer, Int cellX, Int cellY );

protected:
	void getRadiusAndCenter( const Object *obj, Int &iRadius, Bool &center );

private:
	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_mid[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer, Int cellX, Int cellY )
{
	if (cellX >= m_extent.lo.x && cellX <= m_extent.hi.x &&
		cellY >= m_extent.lo.y && cellY <= m_extent.hi.y)
	{
		if (layer > LAYER_GROUND && layer <= LAYER_LAST)
		{
			PathfindCell *cell = m_layers[layer].rva003FBB20( cellX, cellY );
			if (cell)
				return cell;
		}
		return &m_map[cellX][cellY];
	}
	return 0;
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


Int Pathfinder::rva003E49F0( Object *obj, Coord3D *pos, void *cellIds )
{
	Int radius;
	Bool center;
	getRadiusAndCenter(obj, radius, center);
	Bool centered = center;
	Int numCellsAbove = radius;
	ICoord2D cell;
	if (centered)
	{
		numCellsAbove = radius + 1;
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f);
	}
	else
	{
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f + 0.5f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f + 0.5f);
	}

	Bool checkGround = false;
	Bool checkLayer = false;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	if (layer != LAYER_GROUND && layer < 16)
	{
		checkLayer = true;
		if (TheTerrainLogic->queryObjectLayer(obj, layer))
			checkGround = true;
	}
	else
	{
		checkGround = true;
	}

	ObjectID *ids = (ObjectID *)cellIds;
	Int numIds = 0;
	Int i, j;
	for (i = cell.x - radius - 1; i < cell.x + numCellsAbove + 1; i++)
	{
		for (j = cell.y - radius - 1; j < cell.y + numCellsAbove + 1; j++)
		{
			if (i != cell.x - radius - 1 && j != cell.y - radius - 1 &&
				i != cell.x + numCellsAbove && j != cell.y + numCellsAbove)
				continue;

			if (checkLayer)
			{
				PathfindCell *layerCell = getCell(layer, i, j);
				if (layerCell)
				{
					ObjectID id = layerCell->getPosUnit();
					if (id == INVALID_ID)
						id = layerCell->getBfme20();
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = id;
							if (numIds == 16)
								return 16;
						}
					}
				}
			}

			if (checkGround)
			{
				PathfindCell *groundCell = getCell(LAYER_GROUND, i, j);
				if (groundCell)
				{
					ObjectID id = groundCell->getPosUnit();
					if (id == INVALID_ID)
						id = groundCell->getBfme20();
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = id;
							if (numIds == 16)
								return 16;
						}
					}
				}
			}
		}
	}
	return numIds;
}


// Retail 003E4680: 693 bytes; native layer callee 003FBAB0 is distinct
// from the 003FBB20 body used above. See 003e4680-radius-lifetime.md.

Int Pathfinder::rva003E4680( Object *obj, Coord3D *pos, void *cellIds )
{
	Int radius;
	Bool center;
	getRadiusAndCenter(obj, radius, center);
	Bool centered = center;
	Int numCellsAbove = radius;
	ICoord2D cell;
	if (centered)
	{
		numCellsAbove = radius + 1;
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f);
	}
	else
	{
		cell.x = REAL_TO_INT_FLOOR(pos->x * 0.1f + 0.5f);
		cell.y = REAL_TO_INT_FLOOR(pos->y * 0.1f + 0.5f);
	}

	Bool checkGround = false;
	Bool checkLayer = false;
	PathfindLayerEnum layer = (PathfindLayerEnum)obj->getLayer();
	if (layer != LAYER_GROUND && layer < 16)
	{
		checkLayer = true;
		if (TheTerrainLogic->queryObjectLayer(obj, layer))
			checkGround = true;
	}
	else
	{
		checkGround = true;
	}

	ObjectID *ids = (ObjectID *)cellIds;
	Int numIds = 0;
	Int i, j;
	for (i = cell.x - radius; i < cell.x + numCellsAbove; i++)
	{
		for (j = cell.y - radius; j < cell.y + numCellsAbove; j++)
		{

			if (checkLayer)
			{
				PathfindCell *layerCell = getCell003E4680(layer, i, j);
				if (layerCell)
				{
					ObjectID id = layerCell->m_info ? layerCell->m_info->m_goalUnitID : 0;
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = layerCell->getPosUnit();
							if (numIds == 16)
								return 16;
						}
					}
				}
			}

			if (checkGround)
			{
				PathfindCell *groundCell = getCell003E4680(LAYER_GROUND, i, j);
				if (groundCell)
				{
					ObjectID id = groundCell->m_info ? groundCell->m_info->m_goalUnitID : 0;
					if (id != INVALID_ID && id != obj->getID())
					{
						Int k;
						for (k = 0; k < numIds; k++)
							if (ids[k] == id)
								break;
						if (k == numIds)
						{
							ids[numIds++] = id;
							if (numIds == 16)
								return 16;
						}
					}
				}
			}
		}
	}
	return numIds;
}
