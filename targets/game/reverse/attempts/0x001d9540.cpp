// ??0BfmeVecCD@@QAE@ABV0@@Z (identity unknown)
// partial score=0.80 date=2026-09-07
// 65/67. This is the STLport vector<T*> COPY CONSTRUCTOR:
//     _Vector_base(x.size(), x.get_allocator());
//     _M_finish = __uninitialized_copy(x._M_start, x._M_finish, _M_start);
// The pinned callee at 0x0001D949 confirms it. Its real name is
// ??0?$_Vector_base@PBVLocomotorTemplate@@...@Z, so the element is
// `const LocomotorTemplate *` and sizeof is 4, hence the `sar esi,2`.
// Recovered: the allocator is returned BY VALUE through an sret pointer that
// lands in the dead parameter home slot (lea eax,[esp+0x10] / push eax), which
// needs a class with declared-not-defined ctor and copy ctor. A plain empty
// POD would be returned in al instead. The three-argument cdecl copy and the
// `return this` tail both match.
// Residue: register allocation. retail ebx=src, edi=this, esi=count. MSVC
// edi=src, esi=this. 28 diffs, all downstream of that.
// Tried: hoisting the count into a local before the base call. It fixes the
// first two instructions but costs 4 bytes elsewhere (69), because MSVC then
// loads begin into eax instead of `sub esi,[ebx]` straight from memory.
struct BfmeAllocCD
{
	char m_bfmePadCD;

	BfmeAllocCD();
	BfmeAllocCD(const BfmeAllocCD &other);
};

class BfmeVecCD
{
public:
	BfmeVecCD(const BfmeVecCD &src);

	BfmeAllocCD bfmeAllocCD() const;
	void bfmeBaseCD(unsigned int count, const BfmeAllocCD &alloc);

	void **m_bfmeBeginCD;
	void **m_bfmeEndCD;
};

extern "C" void **__cdecl bfmeCopyCD(void **first, void **last, void **dst);

BfmeVecCD::BfmeVecCD(const BfmeVecCD &src)
{
	bfmeBaseCD(src.m_bfmeEndCD - src.m_bfmeBeginCD, src.bfmeAllocCD());

	m_bfmeEndCD = bfmeCopyCD(src.m_bfmeBeginCD, src.m_bfmeEndCD, m_bfmeBeginCD);
}
