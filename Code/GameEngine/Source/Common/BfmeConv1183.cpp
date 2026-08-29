// Open-BFME5 conversions.

class BfmeStr1183
{
public:
	void bfmeFree1183(void);
	int m_bfme00;
};

struct BfmeSlot1183
{
	BfmeStr1183 m_bfme00;
	BfmeStr1183 m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	unsigned char m_bfme10;
	char m_bfmePad[3];
};

class BfmeList1183
{
public:
	void bfmeRemove1183(BfmeSlot1183 *s);
};

class BfmeW1183
{
public:
	bool bfmeClose1183(unsigned int i);
	void bfmeHide1183(unsigned int i);
	char m_bfmePad0[0x58];
	BfmeList1183 m_bfme58;
	char m_bfmePad1[0x4c];
	BfmeSlot1183 m_bfmeA8[12];
};

bool BfmeW1183::bfmeClose1183(unsigned int i)
{
	BfmeSlot1183 *s;

	if (i >= 0xc)
		return false;

	s = &m_bfmeA8[i];

	if (s->m_bfme0c == -1)
		return false;

	if (s->m_bfme10 & 2)
		bfmeHide1183(i);

	m_bfme58.bfmeRemove1183(s);
	s->m_bfme00.bfmeFree1183();
	s->m_bfme04.bfmeFree1183();
	s->m_bfme10 &= 0xf4;
	s->m_bfme08 = 0;
	s->m_bfme0c = -1;

	return true;
}
