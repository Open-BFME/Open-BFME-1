typedef int Int;
typedef unsigned short zoneStorageType;

struct PathfindCell
{
	unsigned char opaque[8];
	zoneStorageType zone;
	zoneStorageType nextZone;
	unsigned char tail[4];
};

class PathfindLayer
{
public:
	void bfmeApplyZone();

private:
	PathfindCell *blockOfMapCells;
	PathfindCell **layerCells;
	Int width;
	Int height;
	unsigned char middle[0x2c - 0x10];
	Int zone;
	Int nextZone;
};

void PathfindLayer::bfmeApplyZone()
{
	zone = nextZone;

	for (Int i = 0; i < width; ++i) {
		for (Int j = 0; j < height; ++j) {
			PathfindCell *cell = &layerCells[i][j];
			cell->zone = cell->nextZone;
		}
	}
}
