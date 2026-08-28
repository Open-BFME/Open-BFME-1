// Flatten the five non-hierarchical zone tables against table zero for each of
// BFME's twelve movement profiles. Keeping the helpers in this TU preserves
// VC7.1's retail private calling convention.

typedef int Int;
typedef unsigned short zoneStorageType;

static void __fastcall resolveZones(Int sourceZone, Int targetZone,
	zoneStorageType *zoneEquivalency, Int sizeOfZones)
{
	sourceZone = zoneEquivalency[sourceZone];
	targetZone = zoneEquivalency[targetZone];
	zoneStorageType finalZone;
	if (targetZone < sourceZone)
		finalZone = targetZone;
	else
		finalZone = sourceZone;

	for (Int i = 0; i < sizeOfZones; ++i)
	{
		zoneStorageType zone = zoneEquivalency[i];
		if (zone == targetZone || zone == sourceZone)
			zoneEquivalency[i] = finalZone;
	}
}

static void flattenZones(zoneStorageType *zoneArray,
	zoneStorageType *zoneHierarchical, Int sizeOfZones)
{
	Int i;
	for (i = 0; i < sizeOfZones; i++)
	{
		Int zone1 = zoneArray[i];
		Int zone2 = zoneHierarchical[zone1];
		zone1 = zoneArray[zone2];
		while (zone1 != zone2)
		{
			zone2 = zoneHierarchical[zone1];
			zone1 = zoneArray[zone2];
		}
		zoneArray[i] = zone2;
	}

	for (i = 0; i < sizeOfZones; i++)
	{
		Int zone1 = zoneArray[i];
		Int zone2 = zoneHierarchical[i];
		if (zone1 != zone2)
			resolveZones(zone1, zone2, zoneArray, sizeOfZones);
	}
}

#pragma pack(push, 1)
class PathfindZoneManager
{
public:
	void bfmeFlattenZones(Int start, Int end);

private:
	unsigned char m_beforeEquivalency[0x18];
	zoneStorageType m_zoneEquivalency[24000];
	unsigned char m_beforeMaxZone[0x23298 - 0x18 - 24000 * 2];
	Int m_maxZone;
	zoneStorageType *m_zoneTables[12][6];
};
#pragma pack(pop)

// ?bfmeFlattenZones@PathfindZoneManager@@QAEXHH@Z
void PathfindZoneManager::bfmeFlattenZones(Int start, Int end)
{
	Int endTable = end * 5 / 100 + 1;
	Int firstTable = start * 5 / 100 + 1;
	for (Int table = firstTable; table < endTable; ++table)
	{
		for (Int profile = 0; profile < 12; ++profile)
		{
			flattenZones(m_zoneTables[profile][table],
				m_zoneTables[profile][0], m_maxZone);
		}
	}
}
