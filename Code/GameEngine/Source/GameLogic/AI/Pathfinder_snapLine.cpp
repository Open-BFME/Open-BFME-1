// cl: /DNDEBUG /MD
//
// Retail 0x003E6AF0: walk a world-space segment on LAYER_GROUND and, if the
// cell iterator reports a hit, write the payload's working Coord3D back onto
// the destination.  The payload is Rva003D61C0 filled by its landed set().

typedef int Int;
typedef bool Bool;

struct Coord3D
{
	float x, y, z;
};

struct ICoord2D
{
	Int x, y;
};

enum PathfindLayerEnum
{
	LAYER_GROUND = 1
};

struct Rva003D61C0Vec
{
	Int a, b, c;
};

class Rva003D61C0
{
public:
	Rva003D61C0 &set(Int a, Int b, const Rva003D61C0Vec *p);

	Int m_00;
	Int m_04;
	Coord3D m_pos;
};

struct Rva003DE480Struct;

class Pathfinder
{
public:
	Bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	Int iterateCellsAlongLine(const ICoord2D &start, const ICoord2D &end,
		PathfindLayerEnum layer, Rva003DE480Struct *userData);
	void snapLine(const Coord3D *from, Coord3D *to);
};

// ?snapLine@Pathfinder@@QAEXPBUCoord3D@@PAU2@@Z
void Pathfinder::snapLine(const Coord3D *from, Coord3D *to)
{
	Rva003D61C0 info;
	info.set((Int)this, 4, (const Rva003D61C0Vec *)from);
	ICoord2D start;
	worldToCell(from, &start);
	ICoord2D end;
	worldToCell(to, &end);
	if (iterateCellsAlongLine(start, end, LAYER_GROUND, (Rva003DE480Struct *)&info)) {
		to->x = info.m_pos.x;
		to->y = info.m_pos.y;
		to->z = info.m_pos.z;
	}
}
