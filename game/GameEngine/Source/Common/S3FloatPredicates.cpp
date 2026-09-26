// Two more three-way splits, both floating-point predicates whose true and
// false arms had been claimed as aliases elsewhere.
//
// 0x001DE230 forms one product from the SECOND argument and +0x08, another
// from the first and +0x04, subtracts the second from the first, and compares
// against +0x10. test ah,0x41 reads C0 and C3 together, so the branch is taken
// on less-or-equal and the true case is a strict greater.
//
// 0x001DE260 indexes a float array by its second argument, taking one element
// and the one sixteen further on -- the +0x40 displacement on the same
// eax+edx*4 -- and compares the same difference against the product of +0x10
// and +0x0C. fcompp compares the later push against the earlier, so the flags
// read backwards, and test ah,5 with jp is the strict-greater form.
//
// Both return int: mov eax,1 and xor eax,eax rather than the two-byte al
// forms.

typedef float Real;

class Gen_001de230
{
public:
	int bfmeAbove(Real first, Real second) const;

private:
	char m_bfmeHead[0x04];
	Real m_bfme0004;						// +0x04
	Real m_bfme0008;						// +0x08
	char m_bfmeMid[0x10 - 0x0C];
	Real m_bfme0010;						// +0x10
};

class Gen_001de260
{
public:
	int bfmeAbove(const Real *samples, int index) const;

private:
	char m_bfmeHead[0x04];
	Real m_bfme0004;						// +0x04
	Real m_bfme0008;						// +0x08
	Real m_bfme000C;						// +0x0C
	Real m_bfme0010;						// +0x10
};

// ?bfmeAbove@Gen_001de230@@QBEHMM@Z
int Gen_001de230::bfmeAbove(Real first, Real second) const
{
	if (second * m_bfme0008 - first * m_bfme0004 > m_bfme0010)
		return 1;

	return 0;
}

// ?bfmeAbove@Gen_001de260@@QBEHPBMH@Z
int Gen_001de260::bfmeAbove(const Real *samples, int index) const
{
	if (samples[index] * m_bfme0008 - samples[index + 16] * m_bfme0004 > m_bfme0010 * m_bfme000C)
		return 1;

	return 0;
}
