// ?rvaHelper@Rva001A6370Owner@@QAEHPAX@Z
// partial score=0.82 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail 0x001A6370, 126 bytes, __thiscall taking one pointer param and
// cleaning 4 bytes (ret 4). No caller or vtable evidence names the owning
// class, so both this function and the object it operates on stay
// address-derived; landed neighbours are only address-adjacent, not proven
// siblings.
//
// Calls two already-landed opaque views of the SAME parameter object:
// BfmeA1263::bfmeGet1263 (a center-point accessor: average of two coordinate
// pairs scaled by a shared constant, BfmeConv1263.cpp) and
// BfmeThingCMB::bfmeGoCMB (a cached bounds accessor, four ints, that lazily
// refreshes before copying, BfmeConv621.cpp). It then computes the larger of
// the bounds rectangle's two extents (hi-lo per axis) and passes the center
// point, that extent as a float, and a small {int result; void *self;}
// output block to a still-unresolved dump at 0x001A4DD0 (thiscall on this
// function's OWN this, not the parameter). The result field of that output
// block, pre-set to 0, becomes this function's own return value -- read back
// after the call rather than taken from EAX, so the callee returns void and
// reports through the pointer.

typedef float Real;
typedef int Int;

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

class Rva001A6370Owner
{
public:
	Int rvaHelper(void *param);
};

// ?rvaHelper@Rva001A6370Owner@@QAEHPAX@Z
Int Rva001A6370Owner::rvaHelper(void *param)
{
	Rva001A6370Result result;
	result.m_result = 0;
	result.m_self = param;

	BfmeVec1263 center;
	((BfmeA1263 *)param)->bfmeGet1263(&center);

	BfmeVec4CMB bounds;
	((BfmeThingCMB *)param)->bfmeGoCMB(&bounds);

	int *fields = (int *)&bounds;
	Int deltaY = fields[2] - fields[0];
	Int deltaX = fields[3] - fields[1];
	Int *maxDeltaPtr = &deltaY;
	if (deltaY <= deltaX)
		maxDeltaPtr = &deltaX;

	((Rva001A6370Helper *)this)->rva001A4DD0(&center, (Real)*maxDeltaPtr, &result, 0, 0);

	return result.m_result;
}
