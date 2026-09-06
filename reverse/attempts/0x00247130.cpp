// ?bfmeMakeAF@@YGXPAX@Z (identity unknown)
// partial score=0.94 date=2026-09-06
// 40/47 at exact size. Retracts the earlier "attempted" row: the in-place
// construction IS reachable with the three-part recipe (real default ctor,
// INLINE copy ctor, destructor declared but not defined), and that reproduces
// the frame slot, the esp marker, the xor placed before the sub, the byte
// store of 1 at +0x10 and all seven stores in source order.
// The ONLY residue is the zero register: retail `xor edx,edx` and stores
// through edx, MSVC `xor ecx,ecx` and stores through ecx (7 modrm bytes).
// Ruled out here: a thiscall caller, a cdecl callee, and the flags
// /Gr /Gz /GB /G6 /G5 /Oa /Ow. Same wall as 0x000BE410 and 0x000DEE90.
class BfmeCfgAF
{
public:
	BfmeCfgAF()
	{
		m_bfmeAAF = 0;
		m_bfmeFlagAF = 1;
		m_bfmeEAF = 0;
		m_bfmeFAF = 0;
		m_bfmeBAF = 0;
		m_bfmeCAF = 0;
		m_bfmeDAF = 0;
	}
	BfmeCfgAF(const BfmeCfgAF &other) throw()
	{
		m_bfmeAAF = other.m_bfmeAAF;
		m_bfmeBAF = other.m_bfmeBAF;
		m_bfmeCAF = other.m_bfmeCAF;
		m_bfmeDAF = other.m_bfmeDAF;
		m_bfmeFlagAF = other.m_bfmeFlagAF;
		m_bfmeEAF = other.m_bfmeEAF;
		m_bfmeFAF = other.m_bfmeFAF;
	}
	~BfmeCfgAF();

	int m_bfmeAAF;
	int m_bfmeBAF;
	int m_bfmeCAF;
	int m_bfmeDAF;
	char m_bfmeFlagAF;
	int m_bfmeEAF;
	int m_bfmeFAF;
};

void __stdcall bfmeSendAF(void *owner, BfmeCfgAF cfg);

void __stdcall bfmeMakeAF(void *owner)
{
	bfmeSendAF(owner, BfmeCfgAF());
}
