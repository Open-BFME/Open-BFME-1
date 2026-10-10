// Open-BFME5 conversions.

class BfmeF1166
{
public:
	BfmeF1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3, unsigned int bitIndex4, unsigned int bitIndex5) throw();
	unsigned int m_bitWords[6];
};

class BfmeH1166
{
public:
	BfmeH1166(int tag, unsigned int bitIndex1, unsigned int bitIndex2, unsigned int bitIndex3) throw();
	unsigned int m_bitWords[6];
};

class Rva00132A20ThingMask
{
	unsigned int m_words[6];

public:
	bool rva00132a20(const Rva00132A20ThingMask &) const;
};

class BfmeObj1133
{
public:
	int bfmeGo1133(void) const;
	char m_bfmePad[0xc8];
	Rva00132A20ThingMask m_bfmeC8;
};

int BfmeObj1133::bfmeGo1133(void) const
{
	static BfmeF1166 s_bfmeA(0, 8, 9, 0xa, 0xb, 0xc);
	static BfmeH1166 s_bfmeB(0, 0x6c, 7, 0x58);

	if (m_bfmeC8.rva00132a20(reinterpret_cast<const Rva00132A20ThingMask &>(s_bfmeA)) && !m_bfmeC8.rva00132a20(reinterpret_cast<const Rva00132A20ThingMask &>(s_bfmeB)))
		return 1;

	return 0;
}