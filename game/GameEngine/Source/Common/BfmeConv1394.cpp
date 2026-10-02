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

// Retail calls Gen_008D2C80::bfmePush (0x008D2C80) from the VJU sequence push;
// bfmePushVJU was a stand-in spelling of that same body, so declare the
// defining owner here and call it through the defining name.
class Gen_008D2C80
{
public:
	void bfmePush(void);
};

class BfmeStackVJU
{
public:
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
		((Gen_008D2C80 *)s)->bfmePush();
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
