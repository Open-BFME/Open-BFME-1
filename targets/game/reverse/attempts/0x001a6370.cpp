// ?countTrees@TerrainLogic@@QAEHPAVPolygonTrigger@@@Z
// partial score=0.8254 date=2026-09-29
// ?countTrees@TerrainLogic@@QAEHPAVPolygonTrigger@@@Z
// Retail 0x001A6370. The matched condition caller names this call countTrees.
// The typed IRegion2D extent form emits the best measured scratch shape, with
// 22 non-relocation byte differences in the extent compare.

typedef float Real;
typedef int Int;
class PolygonTrigger;


struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
	Int width( void ) const { return hi.x - lo.x; }
	Int height( void ) const { return hi.y - lo.y; }
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

// The result block passed by address to the still-unresolved 0x001A4DD0:
// the caller pre-fills m_self with its own parameter and zeroes m_result,
// and reads m_result back as this function's return value.
struct Rva001A6370Result
{
	Int m_result;
	void *m_self;
};

// Opaque view of the still-dump callee at 0x001A4DD0; ABI inferred from the
// call site only (this=caller's own this, not the parameter).
class Rva001A6370Helper
{
public:
	void rva001A4DD0(BfmeVec1263 *center, Real maxDelta, Rva001A6370Result *outResult, int paramB, int paramA);
};

class TerrainLogic
{
public:
	Int countTrees(PolygonTrigger *param);
};

// ?rvaHelper@Rva001A6370Owner@@QAEHPAX@Z
Int TerrainLogic::countTrees(PolygonTrigger *param)
{
	Rva001A6370Result result;
	result.m_result = 0;
	result.m_self = param;

	BfmeVec1263 center;
	((BfmeA1263 *)param)->bfmeGet1263(&center);

	IRegion2D bounds;
	((BfmeThingCMB *)param)->bfmeGoCMB((BfmeVec4CMB *)&bounds);

	{
		Int deltaX = bounds.width();
		Int deltaY = bounds.height();
		Int *maxDeltaPtr = &deltaY;
		if (deltaY <= deltaX)
			maxDeltaPtr = &deltaX;

		((Rva001A6370Helper *)this)->rva001A4DD0(&center, (Real)*maxDeltaPtr, &result, 0, 0);
	}

	return result.m_result;
}
