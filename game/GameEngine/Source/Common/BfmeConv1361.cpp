// Open-BFME5 conversions.

class BfmeMsgVHE
{
public:
	int bfmeGetVHE(void *k, int d);
	void bfmeSetVHE(void *k, int v);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfmePad[0xc];
	int m_bfme1c;
};

extern int g_bfmeKeyVHE;

void __stdcall bfmeCopyVHE(BfmeMsgVHE *dst, BfmeMsgVHE *src)
{
	dst->m_bfme1c = src->m_bfme1c;
	int v = src->bfmeGetVHE(&g_bfmeKeyVHE, -1);
	if (v != -1)
		dst->bfmeSetVHE(&g_bfmeKeyVHE, v);
	dst->m_bfme04 = src->m_bfme04;
	dst->m_bfme08 = src->m_bfme08;
	dst->m_bfme0c = src->m_bfme0c;
}

struct BfmeParseVHG;

__declspec(dllimport) int __cdecl bfmeAtoiVHG(const char *s);

struct BfmeFieldVHG
{
	char m_bfmePad[20];
};

class BfmeThingVHG
{
public:
	char m_bfmePad[0xb0];
	BfmeFieldVHG m_bfmeArr[64];
};

extern BfmeParseVHG g_bfmeParseVHG[];

class BfmeIniVHG
{
public:
	const char *bfmeNextTokenVHG(const char *sep);
	void bfmeInitFromVHG(void *o, const BfmeParseVHG *p);
};

void __cdecl bfmeGoVHG(BfmeIniVHG *ini, BfmeThingVHG *obj)
{
	int n = bfmeAtoiVHG(ini->bfmeNextTokenVHG(0)) - 1;
	ini->bfmeInitFromVHG(&obj->m_bfmeArr[n], g_bfmeParseVHG);
}

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

class BfmeLayoutVHH
{
public:
	void bfmeSetVHH(const char *s, int n);
	void bfmeCatVHH(const char *s, int n);
};

void __cdecl bfmeGoVHH(char d, BfmeLayoutVHH *s)
{
	char buf[2];
	s->bfmeSetVHH("CommandButtons/Command", 0x16);
	buf[0] = d + 0x31;
	buf[1] = 0;
	s->bfmeCatVHH(buf, strlen(buf));
}
