// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003EE2B0: BFME attack-query candidate test.  The query walks from
// a cell coordinate to an offset candidate, resolves the candidate's effective
// zone, and accepts it when the movement-zone check allows the transition.

typedef int Int;
typedef bool Bool;
typedef unsigned short zoneStorageType;

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
};

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
	unsigned char m_pad000[0xc9c];
	PathfindZoneManager m_zoneManager;
};

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
