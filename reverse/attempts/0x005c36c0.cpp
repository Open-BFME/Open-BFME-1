// ?bfmeComputeFH@BfmeOwnerFH@@QAE?AUBfmeVec3FH@@PAX0@Z (identity unknown)
// partial score=0.9 date=2026-09-06
// 88/91; the gap is retail mov eax,ecx plus the fld scheduling around it.
// Pins: ?bfmeCalcFH@@YG?AUBfmeVec3FH@@PAXM00@Z 0x0002F4AA,
//       ?g_bfmeGlobalFH@@3PAVBfmeGlobalFH@@A 0x00EED5C8.
// Sibling at 0x005C3630 (104B) has the same shape with the guard member at +0x1c0.
typedef float Real;

extern const Real g_bfmeK1239;
extern const Real g_bfmeK1253;

struct BfmeVec3FH
{
	BfmeVec3FH(Real x, Real y, Real z)
		: m_bfmeXFH(x), m_bfmeYFH(y), m_bfmeZFH(z) {}

	Real m_bfmeXFH;
	Real m_bfmeYFH;
	Real m_bfmeZFH;
};

class BfmeGlobalFH
{
public:
	unsigned char m_bfmeHeadFH[0xab4];
	Real m_bfmeScaleFH;
};

extern BfmeGlobalFH *g_bfmeGlobalFH;

class BfmeThingFH;

BfmeVec3FH __stdcall bfmeCalcFH(void *owner, Real scale, void *first, void *second);

class BfmeOwnerFH
{
public:
	BfmeVec3FH bfmeComputeFH(void *first, void *second);

	unsigned char m_bfmeHeadFH[0x180];
	void *m_bfmeOtherFH;
	unsigned char m_bfmeMidFH[0x40];
	BfmeThingFH *m_bfmeThingFH;
};

BfmeVec3FH BfmeOwnerFH::bfmeComputeFH(void *first, void *second)
{
	if (m_bfmeThingFH != 0)
		return bfmeCalcFH(m_bfmeOtherFH,
			(g_bfmeGlobalFH->m_bfmeScaleFH + g_bfmeK1239) * g_bfmeK1253,
			first, second);

	return BfmeVec3FH(0, 0, 0);
}
