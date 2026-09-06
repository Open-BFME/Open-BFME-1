// ?bfmeCopyHW@BfmeHolderHW@@QAEAAV1@ABV1@@Z (identity unknown)
// partial score=0.95 date=2026-09-06
// 57/60 at exact size. Everything matches except +0x26: retail emits
//   lea eax,[ebx+4] ; push eax
// where MSVC emits
//   add ebx,4 ; push ebx
// i.e. retail keeps the (dead) reference parameter in ebx and MSVC clobbers
// it. Tried: helper taking const& / taking a pointer with explicit &, a
// second-base upcast (BfmeSubHW as base at +4), a user-declared operator=,
// a named reference local hoisted to the top (that one moves the prologue
// instead), the assignment before the pointer store, and a pointer local for
// `other`. All produce the identical 3-byte residue -- this is the
// argument-shuttle register-allocation class, already logged unreachable.
// The helper is the thunk at 0x0000FF29 -> 0x005C93C0 (still unclaimed).
class BfmeSrcHW
{
public:
	virtual void bfmeReleaseHW(int flag);
	virtual BfmeSrcHW *bfmeCloneHW(void);
};

class BfmeSubHW
{
public:
	BfmeSubHW &operator=(const BfmeSubHW &other);	// pin ??4BfmeSubHW@@QAEAAV0@ABV0@@Z,0x0000FF29

	int m_bfmeSubDataHW;
};

class BfmeHolderHW
{
public:
	BfmeHolderHW &bfmeCopyHW(const BfmeHolderHW &other);

	BfmeSrcHW *m_bfmePtrHW;
	BfmeSubHW m_bfmeSubHW;
};

BfmeHolderHW &BfmeHolderHW::bfmeCopyHW(const BfmeHolderHW &other)
{
	BfmeSrcHW *copy = other.m_bfmePtrHW ? other.m_bfmePtrHW->bfmeCloneHW() : 0;

	if (m_bfmePtrHW)
		m_bfmePtrHW->bfmeReleaseHW(1);

	m_bfmePtrHW = copy;
	m_bfmeSubHW = other.m_bfmeSubHW;

	return *this;
}
