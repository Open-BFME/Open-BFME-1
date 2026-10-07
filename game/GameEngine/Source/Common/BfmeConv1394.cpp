// Open-BFME5 conversions.

class BfmeMsgVJT;

// Retail 0x007E8A80 is defined by BfmeThingUPB in BfmeConv1339.cpp.
class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *a, char *out, void *c);
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
	((BfmeThingUPB *)m)->bfmeGoUPB((void *)"startDate", m_bfmeStart, (void *)0x20);
	((BfmeThingUPB *)m_bfme00)->bfmeGoUPB((void *)"endDate", m_bfmeEnd, (void *)0x20);
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

class BfmeStackVJU;

// Retail 0x008D2E00 and 0x008D2CC0 use these defining owners.
struct BfmeThingDXH
{
	void bfmeGoDXH(void *a);
};

class BfmeA1210
{
public:
	void bfmePop1210();
};

// Callback cell at VA 0x013378A8, defined once as g_bfmeSlot28VB in
// BfmeOneHundredTwentyThree.cpp (data_rows.csv); cast to this call's shape.
extern void (__cdecl *g_bfmeSlot28VB)();

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
		((BfmeThingDXH *)s)->bfmeGoDXH(p);
	}
	switch (m_bfme00)
	{
	case 1:
		((void (__cdecl *)(void *, int))g_bfmeSlot28VB)(m_bfme18, v);
		break;
	}
	if (p)
		((BfmeA1210 *)s)->bfmePop1210();
}
