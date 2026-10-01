/*
 * The byte-matched condition at 0x003248E0 calls TerrainLogic::countTrees
 * through ILT 0x0002784A and passes a PolygonTrigger pointer.
 * Retail returns four stack bytes at +0x7B. INT3 begins at +0x7E, confirming
 * the 126-byte body.
 * This source file uses a local TerrainLogic declaration because TerrainLogic.h
 * does not declare countTrees.
 * BfmeA1263 and BfmeThingCMB provide the center and cached bounds. The matched
 * Rva001A4DD0GridCount::visit method writes the count into the result block.
 */

typedef float Real;
typedef int Int;

inline const Int &maxExtent(const Int &a, const Int &b)
{
	return b > a ? b : a;
}

class PolygonTrigger;
struct Coord3D;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
	Int width(void) const { return hi.x - lo.x; }
	Int height(void) const { return hi.y - lo.y; }
};

struct BfmeVec1263
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeA1263
{
public:
	void bfmeGet1263(BfmeVec1263 *out);
};

struct BfmeVec4CMB
{
	void *m_bfmeA;
	void *m_bfmeB;
	void *m_bfmeC;
	void *m_bfmeD;
};

class BfmeThingCMB
{
public:
	void bfmeGoCMB(BfmeVec4CMB *out);
};

struct Rva001A4DD0Result
{
	Int count;
	PolygonTrigger *trigger;
};

class Rva001A4DD0GridCount
{
public:
	void visit(const Coord3D *center, Real maxDelta,
		Rva001A4DD0Result *outResult, unsigned char filter, int mode);
};

class TerrainLogic
{
public:
	Int countTrees(PolygonTrigger *param);
};

Int TerrainLogic::countTrees(PolygonTrigger *param)
{
	Rva001A4DD0Result result;
	result.count = 0;
	result.trigger = param;

	BfmeVec1263 center;
	((BfmeA1263 *)param)->bfmeGet1263(&center);

	IRegion2D bounds;
	((BfmeThingCMB *)param)->bfmeGoCMB((BfmeVec4CMB *)&bounds);

	{
		Int deltaY = bounds.height();
		Int deltaX = bounds.width();
		((Rva001A4DD0GridCount *)this)->visit(
			reinterpret_cast<const Coord3D *>(&center),
			(Real)maxExtent(deltaY, deltaX), &result, 0, 0);
	}

	return result.count;
}
