// Open-BFME5 conversions.

class BfmeBits1133
{
public:
	BfmeBits1133(int tag, int a, int b, int c, int d, int e) throw();
	BfmeBits1133(int tag, int a, int b, int c) throw();
	char m_bfmePad[0x1c];
};

class BfmeThing1133
{
public:
	char bfmeAny1133(const BfmeBits1133 &b) const;
};

class BfmeObj1133
{
public:
	int bfmeGo1133(void) const;
	char m_bfmePad[0xc8];
	BfmeThing1133 m_bfmeC8;
};

int BfmeObj1133::bfmeGo1133(void) const
{
	static BfmeBits1133 s_bfmeA(0, 8, 9, 0xa, 0xb, 0xc);
	static BfmeBits1133 s_bfmeB(0, 0x6c, 7, 0x58);

	if (m_bfmeC8.bfmeAny1133(s_bfmeA) && !m_bfmeC8.bfmeAny1133(s_bfmeB))
		return 1;

	return 0;
}
