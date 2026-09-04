// cl: /DNDEBUG /MD /EHsc
#include <stdlib.h>
//
// Retail 0x003EE2B0: BFME attack-query candidate test.  The query walks from
// a cell coordinate to an offset candidate, resolves the candidate's effective
// zone, and accepts it when the movement-zone check allows the transition.

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

struct PathfindMovementProfile
{
	Int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	Int layer;
};

struct BfmeCellResult
{
	Int m_field00;
	Int m_field04;
	Int m_field08;
	Int m_field0c;
	Int m_field10;
};

struct BfmeCellInfo
{
	unsigned char m_pad00[0x20];
	Int m_field20;
};

class PathfindCell
{
public:
	BfmeCellInfo *m_info;
	Int m_field04;
	unsigned short m_zone;
	unsigned short m_pad0a;
	unsigned char m_pad0c[4];
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);
	unsigned char m_pad04[0x40];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindZoneManager
{
public:
	zoneStorageType getEffectiveZone(const PathfindMovementProfile &profile,
		zoneStorageType zone) const;
};

class BfmeAttackQuery
{
public:
	void fillCellAlongLine(const ICoord2D *from, const ICoord2D *to,
		Int layer, BfmeCellResult *result);
	Bool validMovement(Int layer, Int fromZone, zoneStorageType toZone,
		const void *extra);

	Bool checkCandidate(const ICoord2D *base, Int dx, Int dy, Int unused,
		Int layer, Int fromZone, BfmeCellResult *result,
		const PathfindMovementProfile *profile, const void *extra);

private:
	unsigned char m_pad000[0x10];
	PathfindCell **m_map;
	Int m_extentLoX;
	Int m_extentLoY;
	Int m_extentHiX;
	Int m_extentHiY;
	unsigned char m_pad024[0x838];
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;
};

// ?fillCellAlongLine@BfmeAttackQuery@@QAEXPBUICoord2D@@0HPAUBfmeCellResult@@@Z
void BfmeAttackQuery::fillCellAlongLine(const ICoord2D *from,
	const ICoord2D *to, Int layer, BfmeCellResult *result)
{
	Int delta_x = abs(to->x - from->x);
	Int delta_y = abs(to->y - from->y);
	Int x = from->x;
	Int y = from->y;

	Int xinc1, xinc2;
	if (to->x >= from->x)
	{
		xinc1 = 1;
		xinc2 = 1;
	}
	else
	{
		xinc1 = -1;
		xinc2 = -1;
	}

	Int yinc1, yinc2;
	if (to->y >= from->y)
	{
		yinc1 = 1;
		yinc2 = 1;
	}
	else
	{
		yinc1 = -1;
		yinc2 = -1;
	}

	Int den, num, numadd, numpixels;
	if (delta_x >= delta_y)
	{
		xinc1 = 0;
		yinc2 = 0;
		den = delta_x;
		num = delta_x / 2;
		numadd = delta_y;
		numpixels = delta_x;
	}
	else
	{
		xinc2 = 0;
		yinc1 = 0;
		den = delta_y;
		num = delta_y / 2;
		numadd = delta_x;
		numpixels = delta_y;
	}

	for (Int curpixel = 0; curpixel <= numpixels; curpixel++)
	{
		PathfindCell *cell;
		if (layer > 1 && layer <= 15)
		{
			cell = m_layers[layer].getCell(x, y);
			if (cell != 0)
				goto examine;
		}
		cell = m_map[x] + y;
		if (cell == 0)
			return;

	examine:
		{
			BfmeCellInfo *info = cell->m_info;
			Int owner = info != 0 ? info->m_field20 : 0;
			if (owner != result->m_field04)
			{
				result->m_field08 = cell->m_zone;
				result->m_field0c = x;
				result->m_field10 = y;
				return;
			}
		}

		num += numadd;
		if (num >= den)
		{
			num -= den;
			x += xinc1;
			y += yinc1;
		}
		x += xinc2;
		y += yinc2;
	}
}

Bool BfmeAttackQuery::checkCandidate(const ICoord2D *base, Int dx, Int dy,
	Int unused, Int layer, Int fromZone, BfmeCellResult *result,
	const PathfindMovementProfile *profile, const void *extra)
{
	ICoord2D candidate = *base;
	candidate.x += dx;
	candidate.y += dy;
	fillCellAlongLine(base, &candidate, layer, result);

	if (result->m_field08 != 0)
	{
		Int effectiveZone = m_zoneManager.getEffectiveZone(
			*profile, (zoneStorageType)result->m_field08);
		if (fromZone == effectiveZone ||
			validMovement(unused, fromZone, effectiveZone, extra))
			return true;
	}
	return false;
}
