// cl: /DNDEBUG /MD /Ob0
//
// Retail 0x004028E0 (55B): free cdecl helper that indexes a zone-equivalency
// table by (rawZone - firstZone) for two cells and, when the resolved zones
// differ, calls the same-TU static resolveBlockZones.

typedef int Int;
typedef unsigned short zoneStorageType;

static void resolveBlockZones(Int srcZone, Int targetZone, zoneStorageType *zoneEquivalency, Int sizeOfZE)
{
	Int i;
	if (targetZone < srcZone) {
		for (i = 0; i < sizeOfZE; i++) {
			if (zoneEquivalency[i] == (zoneStorageType)srcZone) {
				zoneEquivalency[i] = (zoneStorageType)targetZone;
			}
		}
	} else {
		for (i = 0; i < sizeOfZE; i++) {
			if (zoneEquivalency[i] == (zoneStorageType)targetZone) {
				zoneEquivalency[i] = (zoneStorageType)srcZone;
			}
		}
	}
}

// ?bfmeApplyBlockZoneRaw@@YAXGGPAGHH@Z
void bfmeApplyBlockZoneRaw(
	zoneStorageType targetRaw,
	zoneStorageType sourceRaw,
	zoneStorageType *zoneEquivalency,
	Int firstZone,
	Int sizeOfZE)
{
	unsigned source = sourceRaw;
	Int first = firstZone;
	zoneStorageType *eq = zoneEquivalency;
	unsigned target = targetRaw;

	source -= first;
	zoneStorageType srcZone = eq[source];
	target -= first;
	zoneStorageType targetZone = eq[target];

	if (targetZone == srcZone)
		return;

	resolveBlockZones((Int)srcZone, (Int)targetZone, eq, sizeOfZE);
}
