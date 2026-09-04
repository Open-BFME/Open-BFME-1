// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the conditional label store at retail 0x00602DB0, 127 bytes.
// The label arrives by value and is released on both arms; the second
// parameter is never read but is still cleaned up by the callee.

struct BfmeBufferXK
{
	int m_bfmeRef;						// +0x00
	short m_bfmeLength;					// +0x04
};

class AsciiStringXK
{
public:
	AsciiStringXK(const AsciiStringXK &other);
	~AsciiStringXK(void);

	void set(const AsciiStringXK &other);

protected:
	BfmeBufferXK *m_bfmeData;				// +0x00
};

class BfmeStrXK : private AsciiStringXK
{
public:
	BfmeStrXK(const AsciiStringXK &other) : AsciiStringXK(other) {}
	~BfmeStrXK(void) {}

	const BfmeBufferXK *bfmeBufferXK(void) const
	{
		return m_bfmeData;
	}

	void bfmeSetXK(const AsciiStringXK &other)
	{
		set(other);
	}
};

class Gen_00602DB0
{
public:
	bool bfmeStoreXK(AsciiStringXK value, int unused);

	char m_bfmePad00[0x0C];					// +0x00
	BfmeStrXK m_bfmeLabel;					// +0x0C
};

// ?bfmeStoreXK@Gen_00602DB0@@QAE_NVAsciiStringXK@@H@Z
bool Gen_00602DB0::bfmeStoreXK(AsciiStringXK value, int unused)
{
	const BfmeBufferXK *buffer = ((BfmeStrXK *)&value)->bfmeBufferXK();

	if (buffer == 0)
		return false;

	if (buffer->m_bfmeLength == 0)
		return false;

	BfmeStrXK *slot = &m_bfmeLabel;

	slot->bfmeSetXK(value);

	return true;
}
