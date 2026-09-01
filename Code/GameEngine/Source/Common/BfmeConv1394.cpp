// Open-BFME5 conversions.

class BfmeMsgVJT
{
public:
	char bfmeGetStrVJT(const char *k, char *b, int n);
};

class BfmeThingVJT
{
public:
	BfmeThingVJT *bfmeInitVJT(BfmeMsgVJT *m);
	BfmeMsgVJT *m_bfme00;
	char m_bfmeStart[0x20];
	char m_bfmeEnd[0x20];
};

BfmeThingVJT *BfmeThingVJT::bfmeInitVJT(BfmeMsgVJT *m)
{
	m_bfme00 = m;
	m->bfmeGetStrVJT("startDate", m_bfmeStart, 0x20);
	m_bfme00->bfmeGetStrVJT("endDate", m_bfmeEnd, 0x20);
	return this;
}

class BfmeStackVJU
{
public:
	void bfmePushVJU();
	void bfmeSetVJU(void *p);
	void bfmePopVJU();
};

__declspec(dllimport) void __cdecl bfmeCallVJU(void *a, int b);

class BfmeThingVJU
{
public:
	void bfmeGoVJU(BfmeStackVJU *s, int v, void *p);
	int m_bfme00;
	char m_bfmePad[0x14];
	void *m_bfme18;
};

void BfmeThingVJU::bfmeGoVJU(BfmeStackVJU *s, int v, void *p)
{
	if (p)
	{
		s->bfmePushVJU();
		s->bfmeSetVJU(p);
	}
	switch (m_bfme00)
	{
	case 1:
		bfmeCallVJU(m_bfme18, v);
		break;
	}
	if (p)
		s->bfmePopVJU();
}
