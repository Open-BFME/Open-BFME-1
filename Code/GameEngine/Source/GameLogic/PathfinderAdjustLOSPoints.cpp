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
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003D79C0Struct *info);
	void bfmeAdjustLOSPoints(Coord3D *first, Coord3D *second);
};

// ?bfmeAdjustLOSPoints@Pathfinder@@QAEXPAUCoord3D@@0@Z
void Pathfinder::bfmeAdjustLOSPoints(Coord3D *first, Coord3D *second)
{
	Rva003D79C0Struct info;
	info.m((Int)this);

	BfmePair1181 firstCell;
	BfmePair1181 secondCell;
	bfmeConv1181(first, &firstCell);
	bfmeConv1181(second, &secondCell);

	if (iterateCellsAlongLine(*(ICoord2D *)&firstCell,
		*(ICoord2D *)&secondCell, LAYER_GROUND, &info))
	{
		first->x = info.x;
		first->y = info.y;
	}
}
