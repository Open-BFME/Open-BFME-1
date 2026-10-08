struct BfmePairESF
{
	int m_bfmeAESF;
	int m_bfmeBESF;
};

class BfmeAESF;
class BfmeBESF;

class BfmeCESF
{
public:
	unsigned char m_bfmeHeadESF[0xc];
	int m_bfmeKindESF;
};

__forceinline int bfmeKindOkESF(BfmeCESF *c);

// Retail calls ILT 0x000171E8 -> 0x003D7EC0 and ILT 0x00020671 -> 0x003D4E80,
// matched as these Pathfinder members; the host below is this Pathfinder.
struct Coord3D;
struct ICoord2D;
class PathfindCell;
enum PathfindLayerEnum { LAYER_INVALID = 0 };

class Pathfinder
{
public:
	bool worldToCell(const Coord3D *pos, ICoord2D *cell);
	PathfindCell *getCell(PathfindLayerEnum layer, int x, int y);
};

class BfmeHostESF
{
public:
	char bfmeTestESF(BfmeAESF *a, BfmeBESF *b);
};

char BfmeHostESF::bfmeTestESF(BfmeAESF *a, BfmeBESF *b)
{
	BfmePairESF pair;

	Pathfinder *pathfinder = (Pathfinder *)this;

	if (pathfinder->worldToCell((const Coord3D *)a, (ICoord2D *)&pair))
		return 1;

	BfmeCESF *c = (BfmeCESF *)pathfinder->getCell((PathfindLayerEnum)(int)b,
		pair.m_bfmeAESF, pair.m_bfmeBESF);

	if (c == 0)
		return 1;

	return (char)bfmeKindOkESF(c);
}

__forceinline int bfmeKindOkESF(BfmeCESF *c)
{
	int kind = c->m_bfmeKindESF & 7;

	if (kind == 5 || kind == 1 || kind == 2)
		return 0;

	return 1;
}
