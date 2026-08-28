typedef unsigned short zoneStorageType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
struct PathfindCell
{
	unsigned char opaque[10];
	zoneStorageType zone;
};

void bfmeResolveZones(
	int sourceZone, int targetZone,
	zoneStorageType *zoneEquivalency,
	zoneStorageType *zoneListHeads,
	zoneStorageType *zoneListNext);

void bfmeApplyZone(
	PathfindCell &targetCell, const PathfindCell &sourceCell,
	zoneStorageType *zoneEquivalency,
	zoneStorageType *zoneListHeads,
	zoneStorageType *zoneListNext)
{
	int sourceZone = sourceCell.zone;
	int targetZone = targetCell.zone;

	if (targetZone == 0) {
		targetCell.zone = sourceZone;
		return;
	}

	bfmeResolveZones(
		sourceZone, targetZone,
		zoneEquivalency, zoneListHeads, zoneListNext);
}
