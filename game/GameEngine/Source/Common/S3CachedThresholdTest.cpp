// Retail 0x00131B70, 68 bytes, split by the ledger across its two return arms.
//
// A lazily filled cache guarded by bit 1 of the word at +0x5C: the test reads
// that word as a BYTE while the set writes it as a DWORD, which is MSVC
// narrowing a mask that fits in one byte -- the member itself is int-width.
// The value cached comes from vtable slot 0 with no arguments and lands
// through fstp, so that slot returns a float.
//
// Then the argument is added to the cache and compared against a global's
// field scaled by a constant. The scale has to be a LITERAL, not a named
// extern: with a named one MSVC loads the constant first and multiplies by
// the field, while retail loads the field and multiplies by the constant --
// which is what a literal second operand gives. Its address rides a DIR32
// relocation either way, so only the operand order is visible.
//
// fcompp puts the product in st(0) and the sum in st(1), so the flags read
// backwards and test ah,5 with jp leaves the true case as sum strictly
// greater.

typedef float Real;

class BfmeThresholdSource
{
public:
	char m_bfmeHead[0x1AC];
	Real m_bfmeLimit;						// +0x1AC
};

extern BfmeThresholdSource *TheBfmeThresholdSource;			// 0x012ED5C8
class BfmeCachedThresholdScaleHolder
{
public:
	static const Real value;
};

const Real BfmeCachedThresholdScaleHolder::value = 0.5f;

class Gen_00131b70
{
public:
	int bfmeExceeds(Real value);

private:
	virtual Real bfmeMeasure(void);					// slot 0

	char m_bfmeHead[0x54 - 0x04];
	Real m_bfmeCached;						// +0x54
	char m_bfmeMid[0x5C - 0x58];
	int m_bfmeFlags;						// +0x5C
};

// ?bfmeExceeds@Gen_00131b70@@QAEHM@Z
int Gen_00131b70::bfmeExceeds(Real value)
{
	if ((m_bfmeFlags & 2) == 0)
	{
		m_bfmeCached = bfmeMeasure();

		m_bfmeFlags |= 2;
	}

	if (value + m_bfmeCached > TheBfmeThresholdSource->m_bfmeLimit * BfmeCachedThresholdScaleHolder::value)
		return 1;

	return 0;
}
