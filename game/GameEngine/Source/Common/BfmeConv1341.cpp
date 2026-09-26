// Open-BFME5 conversions.

class BfmeThingURB
{
public:
	int bfmeGoURB();
	void bfmeBumpURB();
	char m_bfmePad[4];
	int m_bfmeFlags;
};

int BfmeThingURB::bfmeGoURB()
{
	bfmeBumpURB();
	return (m_bfmeFlags & 0xff0000) == 0x30000;
}

extern char g_bfmeNameURC[];

class BfmeSrcURC
{
public:
	char bfmeFillURC(void *a, char *out, void *n);
};

class BfmeThingURC
{
public:
	BfmeThingURC(BfmeSrcURC *p);
	BfmeSrcURC *m_bfmeOwner;
	char m_bfmeText[4];
};

BfmeThingURC::BfmeThingURC(BfmeSrcURC *p)
{
	m_bfmeOwner = p;
	p->bfmeFillURC(g_bfmeNameURC, m_bfmeText, (void *)0x40);
}

unsigned __fastcall bfmeBitsURD(int fmt);

class BfmeThingURD
{
public:
	unsigned bfmeGoURD();
	char m_bfmePad[0x24];
	unsigned m_bfmeWidth;
	unsigned m_bfmeHeight;
	char m_bfmePad2[8];
	int m_bfmeMode;
	char m_bfmePad3[4];
	int m_bfmeFormat;
};

unsigned BfmeThingURD::bfmeGoURD()
{
	unsigned n = bfmeBitsURD(m_bfmeFormat) * m_bfmeHeight * m_bfmeWidth >> 3;
	if (m_bfmeMode != 1)
		return n * 2 + 0x48;
	return n + 0x48;
}
