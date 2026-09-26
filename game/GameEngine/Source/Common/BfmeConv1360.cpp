// Open-BFME5 conversions.

class BfmeTexVHA;

void __cdecl bfmeSetTexVHA(unsigned i, BfmeTexVHA *&t);
void __cdecl bfmeDrawTriVHA(unsigned short a, unsigned short b, unsigned short c, unsigned short d);

class BfmeThingVHA
{
public:
	void bfmeDrawVHA(bool flag);
	char m_bfmePad[0x20];
	BfmeTexVHA *m_bfme20;
	char m_bfmePad2[0x14];
	unsigned short m_bfme38;
	char m_bfmePad3[2];
	unsigned short m_bfme3c;
	char m_bfmePad4[2];
	unsigned short m_bfme40;
	char m_bfmePad5[2];
	unsigned short m_bfme44;
	char m_bfmePad6[0x36];
	char m_bfme7c;
};

void BfmeThingVHA::bfmeDrawVHA(bool flag)
{
	if (!m_bfme7c)
		return;
	if (!flag)
		bfmeSetTexVHA(0, m_bfme20);
	bfmeDrawTriVHA(m_bfme38, m_bfme44, m_bfme40, m_bfme3c);
}

class BfmeMsgVHC
{
public:
	void *bfmeGetVHC(void *k, void *d);
	char bfmeGetStrVHC(void *k, char *buf, int size);
};

extern int g_bfmeKeyAVHC;
extern int g_bfmeKeyBVHC;

class BfmeThingVHC
{
public:
	BfmeThingVHC *bfmeInitVHC(BfmeMsgVHC *m);
	void bfmeBaseVHC(BfmeMsgVHC *m);
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
	void *m_bfme0c;
};

BfmeThingVHC *BfmeThingVHC::bfmeInitVHC(BfmeMsgVHC *m)
{
	bfmeBaseVHC(m);
	m_bfme08 = m->bfmeGetVHC(&g_bfmeKeyAVHC, 0);
	m_bfme0c = m->bfmeGetVHC(&g_bfmeKeyBVHC, 0);
	return this;
}

extern int g_bfmeKeyCVHD;
extern int g_bfmeKeyDVHD;

class BfmeThingVHD
{
public:
	BfmeThingVHD *bfmeInitVHD(BfmeMsgVHC *m);
	void bfmeBaseVHD(BfmeMsgVHC *m);
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
	char m_bfme0c[0x100];
};

BfmeThingVHD *BfmeThingVHD::bfmeInitVHD(BfmeMsgVHC *m)
{
	bfmeBaseVHD(m);
	m_bfme08 = m->bfmeGetVHC(&g_bfmeKeyCVHD, 0);
	m->bfmeGetStrVHC(&g_bfmeKeyDVHD, m_bfme0c, 0x100);
	return this;
}
