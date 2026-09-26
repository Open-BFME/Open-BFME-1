
// Retail frees these arrays through operator delete[] (??_V@YAXPAX@Z,
// 0x00881EF0). Without the declaration cl falls back to scalar
// operator delete for the block, which is a different body at 0x00881EB0.
void __cdecl operator delete[](void *block);
typedef int Int;
typedef unsigned short zoneStorageType;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
	public:
	~PathfindCell();
	void reset();

	public:
	unsigned char opaque[8];
	zoneStorageType zone;
	zoneStorageType nextZone;
	unsigned char tail[4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	void bfmeApplyZone();
	void bfmeReset();

private:
	PathfindCell *blockOfMapCells;
	PathfindCell **layerCells;
	Int width;
	Int height;
	Int xOrigin;
	Int yOrigin;
	unsigned char middle[0x2c - 0x18];
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

void PathfindLayer::bfmeReset()
{
	if (layerCells) {
		for (Int i = 0; i < width; ++i) {
			for (Int j = 0; j < height; ++j) {
				PathfindCell *cell = &layerCells[i][j];
				cell->reset();
			}
		}

		delete[] layerCells;
		layerCells = 0;
	}

	if (blockOfMapCells)
		delete[] blockOfMapCells;

	blockOfMapCells = 0;
	width = 0;
	height = 0;
	xOrigin = 0;
	yOrigin = 0;
}
