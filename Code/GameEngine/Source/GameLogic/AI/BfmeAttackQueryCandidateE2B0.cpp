// cl: /DNDEBUG /MD /EHsc
extern "C" int __cdecl abs( int n );
#pragma intrinsic(abs)
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

private:
	unsigned char m_unreconstructed[0x44];
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
	Int fillCellAlongLine(const ICoord2D *from, const ICoord2D *to,
		Int layer, BfmeCellResult *result);
	Bool validMovement(Int layer, Int fromZone, zoneStorageType toZone,
		const void *extra);

	Bool checkCandidate(const ICoord2D *base, Int dx, Int dy, Int unused,
		Int layer, Int fromZone, BfmeCellResult *result,
		const PathfindMovementProfile *profile, const void *extra);

private:
	unsigned char m_pad000[0x10];
	PathfindCell **m_map;
	struct
	{
		ICoord2D lo;
		ICoord2D hi;
	} m_extent;
	unsigned char m_beforeLayers[0x85c - 0x24];
	PathfindLayer m_layers[16];
	PathfindZoneManager m_zoneManager;

	__forceinline PathfindCell *getCell(Int layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			if (layer > 1 && layer <= 15)
			{
				PathfindCell *cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		return 0;
	}
};

// Retail body 0x003D6DC0; the checkCandidate caller reaches it through ILT
// 0x00042E01.  The body returns true when the line finds a cell whose owner
// differs from result->m_field04 and records that cell in result.
Int BfmeAttackQuery::fillCellAlongLine(const ICoord2D *from,
	const ICoord2D *to, Int layer, BfmeCellResult *result)
{
	const ICoord2D *from_ptr = from;
	const ICoord2D *to_ptr = to;
	Int to_x = to_ptr->x;
	Int x = from_ptr->x;
	Int delta_x = abs(to_x - x);
	Int y = from_ptr->y;
	Int to_y = to_ptr->y;
	Int delta_y = abs(to_y - y);

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

	if (from->x > to_x)
	{
		xinc2 = -xinc2;
		xinc1 = -1;
	}
	if (from->y > to_y)
	{
		yinc2 = -yinc2;
		yinc1 = -1;
	}

	for (Int curpixel = 0; curpixel < numpixels; curpixel++)
	{
		PathfindCell *cell = getCell(layer, x, y);
		if (cell == 0)
			return false;

		BfmeCellInfo *info = cell->m_info;
		Int owner = info != 0 ? info->m_field20 : 0;
		if (owner != result->m_field04)
		{
			result->m_field08 = cell->m_zone;
			result->m_field0c = x;
			result->m_field10 = y;
			return true;
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

	return false;
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
