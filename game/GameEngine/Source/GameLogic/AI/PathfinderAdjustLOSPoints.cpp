// BFME's two-point LOS adjustment helper at retail 0x003DB160.
// The Weapon goal-LOS caller and the three callee ILTs identify this as the
// Pathfinder helper: convert both points to cells, run the 0x003D79C0 walk,
// and copy its adjusted x/y result back to the first point.

typedef int Int;

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

struct BfmePair1181
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

class BfmeP1181
{
public:
	void bfmeConv1181(void *point, BfmePair1181 *cell);
};

class Gen_003d6680
{
public:
	void *m(Int value);
	Int owner;
};

struct Rva003D79C0Struct : Gen_003d6680
{
	float x, y, z;
};

class Pathfinder : public BfmeP1181
{
public:
	Int iterateCellsAlongLine(const ICoord2D &startCell, const ICoord2D &destinationCell,
		PathfindLayerEnum layer, Rva003D79C0Struct *resultInfo);
	void bfmeAdjustLOSPoints(Coord3D *startPosition, Coord3D *endPosition);
};

// ?bfmeAdjustLOSPoints@Pathfinder@@QAEXPAUCoord3D@@0@Z
void Pathfinder::bfmeAdjustLOSPoints(Coord3D *startPosition, Coord3D *endPosition)
{
	Rva003D79C0Struct adjustmentResult;
	adjustmentResult.m((Int)this);

	BfmePair1181 startCell;
	BfmePair1181 endCell;
	bfmeConv1181(startPosition, &startCell);
	bfmeConv1181(endPosition, &endCell);

	if (iterateCellsAlongLine(*(ICoord2D *)&startCell,
		*(ICoord2D *)&endCell, LAYER_GROUND, &adjustmentResult))
	{
		startPosition->x = adjustmentResult.x;
		startPosition->y = adjustmentResult.y;
	}
}
