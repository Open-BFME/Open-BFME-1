// ?forward@BfmeGuardedForward414050@@QAEXH@Z
// partial score=0.78 date=2026-09-04
// cl: /DNDEBUG /MD /EHs-c-
//
// Open-BFME5: thiscall guarded virtual forwarder at retail 0x00414050 (32B).
// Null-checks the stack arg, loads [this+0x150] then [[that]], null-checks the
// resulting object, rewrites the stack arg, and tail-jumps vtable slot 0x68.
// Wall: MSVC keeps the arg in eax and the vptr in edx; retail keeps the arg in
// edx and the pointer chain / vptr in eax (same instruction multiset).

class BfmeVtableTarget414050
{
public:
	virtual void s00(void); virtual void s04(void); virtual void s08(void);
	virtual void s0C(void); virtual void s10(void); virtual void s14(void);
	virtual void s18(void); virtual void s1C(void); virtual void s20(void);
	virtual void s24(void); virtual void s28(void); virtual void s2C(void);
	virtual void s30(void); virtual void s34(void); virtual void s38(void);
	virtual void s3C(void); virtual void s40(void); virtual void s44(void);
	virtual void s48(void); virtual void s4C(void); virtual void s50(void);
	virtual void s54(void); virtual void s58(void); virtual void s5C(void);
	virtual void s60(void); virtual void s64(void);
	virtual void slot68(int arg);
};

class BfmeGuardedForward414050
{
public:
	void forward(int arg);

private:
	char m_pad[0x150];
	BfmeVtableTarget414050 **m_pp; // +0x150
};

// ?forward@BfmeGuardedForward414050@@QAEXH@Z
void BfmeGuardedForward414050::forward(int arg)
{
	if (!arg)
		return;
	BfmeVtableTarget414050 **pp = m_pp;
	BfmeVtableTarget414050 *target = *pp;
	if (!target)
		return;
	target->slot68(arg);
}
