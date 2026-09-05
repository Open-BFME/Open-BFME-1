// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the bounds-checked slot accessor at retail 0x0048DE20, 92 bytes.
// Out-of-range lookups return a function-local static, whose guard bit and
// atexit registration retail carries inline.

class AsciiStringYJ
{
public:
	AsciiStringYJ(void) throw()
	{
		m_bfmeData = 0;
	}
	~AsciiStringYJ(void) throw();

private:
	char *m_bfmeData;
};

class Gen_0048DE20
{
public:
	AsciiStringYJ *bfmeAtYJ(int index);

	char m_bfmePad0000[0x303C];				// +0x0000
	int m_bfmeCount;					// +0x303C
	AsciiStringYJ *m_bfmeSlots;				// +0x3040
};

// ?bfmeAtYJ@Gen_0048DE20@@QAEPAVAsciiStringYJ@@H@Z
AsciiStringYJ *Gen_0048DE20::bfmeAtYJ(int index)
{
	if (m_bfmeSlots != 0 && index >= 0 && index < m_bfmeCount)
		return &m_bfmeSlots[index];

	static AsciiStringYJ s_bfmeEmptyYJ;

	return &s_bfmeEmptyYJ;
}
