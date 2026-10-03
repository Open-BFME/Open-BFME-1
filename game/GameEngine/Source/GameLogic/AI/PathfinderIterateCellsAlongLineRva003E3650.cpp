// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAURva003E3650Struct@@@Z
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /I.
// stlport
// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAURva003E3650Struct@@@Z
// Retail 0x003E3650: cell-space Bresenham walk with the BFME obstacle
// predicate. Evidence: identity_evidence/003e3650-visible-lookup.md.
// The real noinline GameLogic lookup exposes its read-only effects and fixes
// the bank's EBX/EBP mirror. Object uses the shared BFME layout header.

typedef int Int;
typedef int ObjectID;

extern "C" int __cdecl abs( Int n );
#pragma intrinsic(abs)

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	unsigned char m_unmodelled_008[0xc0];
	// Third word at +0xD0 is tested below; full mask starts at +0xC8.
	unsigned int m_kindOf[6];
};

#include "game/GameEngine/Source/GameLogic/Object/object.h"

#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "game/GameEngine/Source/Common/Thing/GameLogicObjectLookup.h"

extern GameLogic *TheBfmeGameLogic;

class PathfindCellInfo
{
public:
	unsigned char m_unmodelled_000[0x20];
	ObjectID m_obstacleID;
};

class PathfindCell
{
public:
	PathfindCellInfo *m_info;
	Int m_unmodelled_004;
	Int m_unmodelled_008;
	unsigned int m_packed;

	Int getRawType() const { return m_packed & 0x7; }
	ObjectID getObstacleID() const;
};

inline ObjectID PathfindCell::getObstacleID() const
{
	PathfindCellInfo *info = m_info;
	if (info != 0)
		return info->m_obstacleID;
	return 0;
}

class PathfindLayer
{
public:
	PathfindCell *getCell( Int x, Int y );

private:
	unsigned char m_unmodelled_000[0x44];
};

struct Rva003E3650Struct
{
	Object *m_found;
	ObjectID m_ignoreID;
};

static ThingTemplate *resolveObstacleTemplate( Object *object )
{
	ThingTemplate *thing = object->m_template;
	if (thing == 0)
		return 0;
	if (thing->m_nextOverride == 0)
		return (ThingTemplate *)thing;
	return (ThingTemplate *)thing->m_nextOverride->getFinalOverride();
}

class Pathfinder
{
public:
	Int iterateCellsAlongLine( const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003E3650Struct *info );
	PathfindCell *getCell( PathfindLayerEnum layer, Int x, Int y );

private:
	unsigned char m_unmodelled_000[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	unsigned char m_unmodelled_024[0x85c - 0x24];
	PathfindLayer m_layers[16];
};

inline PathfindCell *Pathfinder::getCell( PathfindLayerEnum layer,
	Int x, Int y )
{
	if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
		y >= m_extent.lo.y && y <= m_extent.hi.y)
	{
		if (layer > 1 && layer <= 15)
		{
			PathfindCell *cell = m_layers[layer].getCell( x, y );
			if (cell)
				return cell;
		}
		return &m_map[x][y];
	}
	return 0;
}

// ?iterateCellsAlongLine@Pathfinder@@QAEHABUICoord2D@@0W4PathfindLayerEnum@@PAURva003E3650Struct@@@Z
Int Pathfinder::iterateCellsAlongLine( const ICoord2D &start,
	const ICoord2D &end, PathfindLayerEnum layer,
	Rva003E3650Struct *info )
{
	Int delta_x = abs( end.x - start.x );
	Int delta_y = abs( end.y - start.y );

	Int xinc2, yinc1, xinc1, numpixels, numadd, den;
	Int yinc2, num;

	if (delta_x >= delta_y)
	{
		numpixels = delta_x + 1;
		num = 2 * delta_y - delta_x;
		numadd = delta_y << 1;
		den = 2 * (delta_y - delta_x);
		xinc2 = 1;
		yinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}
	else
	{
		numpixels = delta_y + 1;
		num = 2 * delta_x - delta_y;
		numadd = delta_x << 1;
		den = 2 * (delta_x - delta_y);
		yinc2 = 1;
		xinc2 = 0;
		yinc1 = 1;
		xinc1 = 1;
	}

	if (start.x > end.x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (start.y > end.y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	Int x = start.x;
	Int y = start.y;
	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *cell = getCell( layer, x, y );
		if (cell == 0)
			return 0;

		if (cell->getRawType() == 4)
		{
			Object *object = TheBfmeGameLogic->findObjectByID(
				cell->getObstacleID());
			if (object)
			{
				ThingTemplate *objectTemplate = resolveObstacleTemplate( object );
				if (objectTemplate->m_kindOf[2] & 2)
				{
					if (object->m_id != info->m_ignoreID)
					{
						info->m_found = object;
						return 1;
					}
				}
			}
		}

		if (num < 0)
		{
			num += numadd;
			x += xinc2;
			y += yinc2;
		}
		else
		{
			num += den;
			x += xinc1;
			y += yinc1;
		}
	}

	return 0;
}
