class BfmeItemZF;

class BfmeHolderZF
{
public:
	unsigned char m_bfmeHeadZF[0xfc];
	BfmeItemZF *m_bfmeItemZF;
};

struct BfmeStateZF
{
	unsigned char m_bfmeBytesZF[4];
};

class BfmeSubZF
{
public:
	void bfmeGoZF(void *a, void *b, void *c, BfmeStateZF *state);
};

class BfmeOwnerZF
{
public:
	void bfmeSendZF(void *a, void *b, void *c);

	unsigned char m_bfmeHeadZF[8];
	BfmeHolderZF *m_bfmeHolderZF;
	unsigned char m_bfmeMidZF[0x1b0];
	BfmeStateZF m_bfmeStateZF;
	unsigned char m_bfmePad2ZF[0xc];
	BfmeSubZF m_bfmeSubZF;
};

void BfmeOwnerZF::bfmeSendZF(void *a, void *b, void *c)
{
	if (m_bfmeHolderZF->m_bfmeItemZF == 0)
		return;

	m_bfmeSubZF.bfmeGoZF(a, b, c, &m_bfmeStateZF);
}
