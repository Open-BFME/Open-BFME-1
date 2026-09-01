// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

struct BfmeRecVFA
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

int bfmeSendVFA(void *h, int a, int b, int c, int d);

class BfmeThingVFA
{
public:
	int bfmeGoVFA(BfmeRecVFA *r);
	char m_bfmePad[8];
	void *m_bfmeHandle;
	char m_bfmePad2[4];
	char m_bfmeReady;
};

int BfmeThingVFA::bfmeGoVFA(BfmeRecVFA *r)
{
	if (!m_bfmeReady)
		return 0xffffff33;
	return bfmeSendVFA(m_bfmeHandle, r->m_bfme00, r->m_bfme04, r->m_bfme08, r->m_bfme0c);
}

class BfmeChunkVFC
{
public:
	unsigned bfmeReadVFC(void *p, unsigned n);
};

class BfmeThingVFC
{
public:
	char bfmeGoVFC(BfmeChunkVFC *c);
	char m_bfmePad[0x44];
	char m_bfmeBuf[0x14];
};

char BfmeThingVFC::bfmeGoVFC(BfmeChunkVFC *c)
{
	memset(m_bfmeBuf, 0, 0x14);
	char r = 0;
	if (c->bfmeReadVFC(m_bfmeBuf, 0x14) == 0x14)
		r = 1;
	return r;
}

extern char g_bfmeEmptyVFD[];

class BfmeBufVFD
{
public:
	void bfmeAppendVFD(const char *s);
	char m_bfmePad[8];
};

struct BfmeThingVFD
{
	char m_bfmePad[8];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	char m_bfme14;
	char m_bfmePad2[3];
	int m_bfme18;
	BfmeBufVFD m_bfmeBuf;
	int m_bfme24;
	int m_bfme28;
	char m_bfmePad3[0x40];
	char m_bfme6c;
};

void __stdcall bfmeGoVFD(BfmeThingVFD *p)
{
	p->m_bfme08 = 0;
	p->m_bfme0c = 0;
	p->m_bfme10 = 0;
	p->m_bfme14 = 0;
	p->m_bfme18 = 0;
	p->m_bfmeBuf.bfmeAppendVFD(g_bfmeEmptyVFD);
	p->m_bfme24 = 0;
	p->m_bfme28 = 0;
	p->m_bfme6c = 0;
}
