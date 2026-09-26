// ?compute@Rva001DE2A0Cell@@QBEXPAX0HPBVRva001DE2A0Params@@@Z
// partial score=0.34 date=2026-09-21
// cl: /O2 /Ob0
// Open-BFME5: retail 0x001DE2A0 (189B).
// Same product-subtract-vs-threshold shape as the landed S3FloatPredicates
// siblings (Gen_001de260::bfmeAbove: samples[index]*m_bfme0008 -
// samples[index+16]*m_bfme0004, vs m_bfme0010*m_bfme000C) but this body
// clamps the difference against BfmeZeroRange (0.0f at 0x1075350) instead
// of comparing it directly, divides by m_bfme0010, then builds two
// {1,ratio,z} stack triples and calls the still-empty stub at 0x006E6E50
// (Gen_006e6e50::m, gen_small/fun_004.cpp) twice with (a1, a2-or-ratio-20,
// 6) -- a caller-cleans call into a callee that takes no real parameters,
// so the triples and the second call's overwritten placeholder argument
// are address-derived best-effort transliteration, not a proven ABI.
//
// PARTIAL/BLOCKED candidate: identity of the owning method (BfmeCellGrid,
// VictorySystem, or a sibling) is not established -- the only caller is an
// unmatched dump (0x001B1AD0) -- and the two calls target a body that is
// itself empty in retail, giving no semantic confirmation of the argument
// layout. The vector stores look dead (their address is never passed to
// the call) and are kept only via `volatile` per the documented lever for
// interleaved constant stores retail does not fold away.

typedef float Real;
typedef int Int;

extern "C" const Real BfmeZeroRange; // 0x1075350
extern "C" const Real Rva010977E0;   // 0x10977E0, 20.0f

class Rva001DE2A0Params
{
public:
	char m_bfmeHead[0x04];
	Real m_bfme0004;
	Real m_bfme0008;
	char m_bfmeMid[0x10 - 0x0C];
	Real m_bfme0010;
};

class Rva001DE2A0Cell
{
public:
	void compute(void *a1, void *a2, Int index, const Rva001DE2A0Params *params) const;

private:
	Real m_first[16];
	Real m_second[16];
};

class Rva001DE2A0Stub
{
public:
	void call(void *a1, void *a2, int six);
};

#pragma comment(linker, "/alternatename:?call@Rva001DE2A0Stub@@QAEXPAX0H@Z=?j_000243ac@@YAXXZ")

void Rva001DE2A0Cell::compute(void *a1, void *a2, Int index,
	const Rva001DE2A0Params *params) const
{
	Rva001DE2A0Stub *stub = 0;

	Real diff = m_first[index] * params->m_bfme0008 -
		m_second[index] * params->m_bfme0004;
	Real clamped = (diff > BfmeZeroRange) ? BfmeZeroRange : diff;
	Real limited = (clamped < params->m_bfme0010) ? clamped : params->m_bfme0010;
	Real ratio = limited / params->m_bfme0010;

	struct { volatile Real x, y, z; } v1;
	v1.x = 1.0f;
	v1.y = ratio;
	v1.z = 1.0f;

	stub->call(a1, a2, 6);

	Real second = ratio - Rva010977E0;

	struct { volatile Real x, y, z; } v2;
	v2.x = 1.0f;
	v2.y = ratio;
	v2.z = 0.0f;

	stub->call(a1, *(void **)&second, 6);
}
