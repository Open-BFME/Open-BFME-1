// Map a BFME movement profile to one of the nine ZoneBlock equivalency tables:
// three layer states multiplied by crusher and terrain-only variants.

typedef bool Bool;

struct PathfindMovementProfile
{
	int acceptableSurfaces;
	Bool crusher;
	Bool terrainOnly;
	unsigned char padding[2];
	int layer;

	int bfmeEquivalencyIndex(void) const;
};

// ?bfmeEquivalencyIndex@PathfindMovementProfile@@QBEHXZ
int PathfindMovementProfile::bfmeEquivalencyIndex(void) const
{
	int index = layer;
	if (index < 0)
		index = 0;
	else
		++index;

	if (crusher)
		index += 3;
	if (terrainOnly)
		index += 6;

	return index;
}
