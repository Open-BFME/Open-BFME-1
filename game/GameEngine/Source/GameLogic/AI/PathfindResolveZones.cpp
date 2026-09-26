typedef unsigned short zoneStorageType;

void bfmeResolveZones(
	int sourceZone, int targetZone,
	zoneStorageType *zoneEquivalency,
	zoneStorageType *zoneListHeads,
	zoneStorageType *zoneListNext)
{
	sourceZone = zoneEquivalency[sourceZone];
	targetZone = zoneEquivalency[targetZone];

	if (sourceZone == targetZone)
		return;

	if (targetZone > sourceZone) {
		int swap = targetZone;
		targetZone = sourceZone;
		sourceZone = swap;
	}

	zoneStorageType sourceList = zoneListHeads[sourceZone];
	zoneStorageType targetList = zoneListHeads[targetZone];
	while (sourceList != 0xffff) {
		zoneEquivalency[sourceList] = targetZone;
		zoneStorageType next = zoneListNext[sourceList];
		zoneListNext[sourceList] = targetList;
		targetList = sourceList;
		sourceList = next;
	}

	zoneListHeads[targetZone] = targetList;
}
