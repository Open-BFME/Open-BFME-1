// ?bfmeMakeAE@@YGXPAX@Z (identity unknown)
// partial score=0.92 date=2026-09-06
// 33/37 at exact size. Same family as 0x000BE410 (see that stash for the full
// combination map). The three-part recipe -- real default ctor, INLINE copy
// ctor, destructor declared but not defined -- gives the frame slot, the
// in-place construction and the esp marker exactly.
// Store order is confirmed to be source order: writing the ctor bodies in
// reverse reverses the four stores. Putting the members in a base class
// changes nothing. The only residue is the zero register: retail
// `xor edx,edx`, MSVC `xor ecx,ecx`.
class BfmeQuadAE
{
public:
	BfmeQuadAE() { m_bfmeAAE = 0; m_bfmeBAE = 0; m_bfmeCAE = 0; m_bfmeDAE = 0; }
	BfmeQuadAE(const BfmeQuadAE &other) throw()
	{
		m_bfmeAAE = other.m_bfmeAAE;
		m_bfmeBAE = other.m_bfmeBAE;
		m_bfmeCAE = other.m_bfmeCAE;
		m_bfmeDAE = other.m_bfmeDAE;
	}
	~BfmeQuadAE();

	int m_bfmeAAE;
	int m_bfmeBAE;
	int m_bfmeCAE;
	int m_bfmeDAE;
};

void __stdcall bfmeSendAE(void *owner, BfmeQuadAE quad);	// pin at thunk 0x0000FBAF

void __stdcall bfmeMakeAE(void *owner)
{
	bfmeSendAE(owner, BfmeQuadAE());
}
