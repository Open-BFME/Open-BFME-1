// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// partial score=0.12 date=2026-09-21
// small-vector swap: swaps m_start/m_finish pointers directly, and swaps
// m_capacity accounting for each side's small-buffer-optimisation slot
// (2 inline BfmeDropObjectA* at this+0xc). When either side was using its
// own inline slot, the inline bytes are rotated through a 2-element scratch
// array via the already-matched Rva008953C0Copy helper (Rva008953C0RefRangeCopy.cpp).

class BfmeDropObjectA;

extern "C" BfmeDropObjectA **__cdecl Rva008953C0Copy(
	BfmeDropObjectA **first, BfmeDropObjectA **last, BfmeDropObjectA **result);

class BfmeElemCU
{
public:
	BfmeElemCU();
	~BfmeElemCU();
	BfmeDropObjectA *m_ptr;
};

class BfmeDropObjectAVector
{
public:
	void swap(BfmeDropObjectAVector &other);

	BfmeDropObjectA **m_start;
	BfmeDropObjectA **m_finish;
	BfmeDropObjectA **m_capacity;
	BfmeDropObjectA *m_inline[2];
};

void BfmeDropObjectAVector::swap(BfmeDropObjectAVector &other)
{
	BfmeDropObjectA **t;

	t = m_start;
	m_start = other.m_start;
	other.m_start = t;

	t = m_finish;
	m_finish = other.m_finish;
	other.m_finish = t;

	BfmeDropObjectA **thisInlineAddr = (BfmeDropObjectA **)m_inline;
	BfmeDropObjectA **otherInlineAddr = (BfmeDropObjectA **)other.m_inline;

	BfmeDropObjectA **thisCap = m_capacity;
	bool thisWasInline = (thisCap == thisInlineAddr);

	BfmeDropObjectA **otherCap = other.m_capacity;
	bool otherWasInline = (otherCap == otherInlineAddr);

	if (otherWasInline)
		m_capacity = thisInlineAddr;
	else
		m_capacity = otherCap;

	if (thisWasInline)
		other.m_capacity = otherInlineAddr;
	else
		other.m_capacity = thisCap;

	if (thisWasInline || otherWasInline)
	{
		BfmeElemCU scratch[2];

		Rva008953C0Copy(
			thisInlineAddr, thisInlineAddr + 2,
			(BfmeDropObjectA **)scratch);
		Rva008953C0Copy(
			otherInlineAddr, otherInlineAddr + 2,
			thisInlineAddr);
		Rva008953C0Copy(
			(BfmeDropObjectA **)scratch, (BfmeDropObjectA **)scratch + 2,
			otherInlineAddr);
	}
}
