// Open-BFME5 conversions.

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

struct BfmeBufVGD
{
	int m_bfme00;
	unsigned short m_bfme04;
};

class BfmeLayoutVGD
{
public:
	void bfmeSetVGD(const char *s, int n);
	BfmeBufVGD *m_bfmeBuf;
};

class BfmeThingVGE
{
public:
	void bfmeGoVGE(const char *s);
	char m_bfmePad[0x10];
	BfmeLayoutVGD m_bfmeStr;
};

void BfmeThingVGE::bfmeGoVGE(const char *s)
{
	BfmeLayoutVGD *p = &m_bfmeStr;
	p->bfmeSetVGD(s, s ? strlen(s) : 0);
}

class BfmeThingVGF
{
public:
	void bfmeGoVGF(const char *s);
	void bfmeGoVGG(const char *s, int i);
	char m_bfmePad[0x200];
	BfmeLayoutVGD m_bfmeStr;
	BfmeLayoutVGD m_bfmeList[64];
};

void BfmeThingVGF::bfmeGoVGF(const char *s)
{
	BfmeLayoutVGD *p = &m_bfmeStr;
	p->bfmeSetVGD(s, s ? strlen(s) : 0);
}

void BfmeThingVGF::bfmeGoVGG(const char *s, int i)
{
	BfmeLayoutVGD *p = &m_bfmeList[i];
	p->bfmeSetVGD(s, s ? strlen(s) : 0);
}

class BfmeThingVGH
{
public:
	void bfmeGoVGH(const char *s);
	char m_bfmePad[0x268];
	BfmeLayoutVGD m_bfmeStr;
};

void BfmeThingVGH::bfmeGoVGH(const char *s)
{
	if (m_bfmeStr.m_bfmeBuf && m_bfmeStr.m_bfmeBuf->m_bfme04)
		return;
	m_bfmeStr.bfmeSetVGD(s, s ? strlen(s) : 0);
}

__declspec(dllimport) unsigned __cdecl bfmeLenVGI(const unsigned short *s);

class BfmeWideVGI
{
public:
	void bfmeSetVGI(const unsigned short *s, int n);
};

class BfmeThingVGI
{
public:
	void bfmeGoVGI(BfmeWideVGI *out);
	char m_bfmePad[0x1e];
	unsigned short m_bfmeBuf[8];
};

void BfmeThingVGI::bfmeGoVGI(BfmeWideVGI *out)
{
	const unsigned short *p = m_bfmeBuf;
	out->bfmeSetVGI(p, p ? bfmeLenVGI(p) : 0);
}

class BfmeThingVGJ
{
public:
	char m_bfmePad[0x94];
	BfmeLayoutVGD m_bfmeStr;
};

struct BfmeArgVGJ
{
	int m_bfme00;
	const char *m_bfme04;
};

extern BfmeThingVGJ *g_bfmeObjVGJ;

int __cdecl bfmeGoVGJ(BfmeArgVGJ *a)
{
	const char *s = a->m_bfme04;
	BfmeLayoutVGD *p = &g_bfmeObjVGJ->m_bfmeStr;
	p->bfmeSetVGD(s, s ? strlen(s) : 0);
	return 2;
}
