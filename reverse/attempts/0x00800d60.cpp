// ?go@BfmeHost800D60@@QAEXXZ
// partial score=0.92 date=2026-09-04
// cl: /GS
// FESL ECHO notify @ 0x00800D60 (227B). Sibling of bfmeDo1052/PROB.

void Rva007F93E0(void *a, void *b, void *c) throw();

class BfmeMsg800D60
{
public:
	BfmeMsg800D60(char *buf, int n) throw();
	~BfmeMsg800D60() throw();
	void addInt(const char *k, int v) throw();
	void addString(const char *k, const char *v) throw();

	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	char m_pad10[0x0c];
	unsigned int m_1c;
	int m_20;
	char m_pad24[0x0c];
	char m_30;
	char m_pad31[0x3];
};

class BfmeHost800D60
{
public:
	char m_pad00[0x8];
	int *m_08;
	char m_pad0c[0x4];
	void *m_10;
	char m_pad14[0x8];
	char m_1c[0x25];
	char m_41[0x25];
	char m_pad66[0x62];
	int m_c8;

	void go();
};

extern char g_bfmeName1052[];
extern int g_bfmeKeyCVHD;
extern char g_bfmeUgid800D60[];
extern char g_bfmeSecret800D60[];

static __forceinline char *bfmeEchoBase800D60(char *o, int *out04)
{
	*out04 = *(int *)(o + 0x290);
	return o + 0x28c;
}

void BfmeHost800D60::go()
{
	char buf[0x100];
	BfmeMsg800D60 msg(buf, 0x100);
	int v04;
	int *h = (int *)bfmeEchoBase800D60((char *)m_08[3], &v04);
	msg.m_04 = v04;
	msg.m_08 = h[2];
	msg.m_0c = h[3];
	msg.m_1c = 'ECHO';
	msg.m_20 = 0;
	msg.m_30 = 1;
	msg.addInt(g_bfmeName1052, m_c8);
	msg.addInt((const char *)&g_bfmeKeyCVHD, 1);
	if (m_1c[0])
	{
		msg.addString(g_bfmeUgid800D60, m_1c);
		msg.addString(g_bfmeSecret800D60, m_41);
	}
	Rva007F93E0(&msg, "->D", m_10);
}
