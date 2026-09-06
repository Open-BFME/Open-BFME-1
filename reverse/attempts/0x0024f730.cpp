// ?bfmeGoFF@BfmeOwnerFF@@QAEXXZ (identity unknown)
// partial score=0.9 date=2026-09-06
// 31/33; the only excess is retail parking this in eax (mov eax,ecx).
// Pin: ?bfmeSendFF@@YGXHHH@Z,0x0004A12E
void __stdcall bfmeSendFF(int delta, int first, int second);

class BfmeInnerFF
{
public:
	unsigned char m_bfmeHeadFF[0x28];
	int m_bfmeStartFF;
};

class BfmeStateFF
{
public:
	unsigned char m_bfmeHeadFF[0x210];
	BfmeInnerFF *m_bfmeInnerFF;
};

class BfmeThingFF
{
public:
	unsigned char m_bfmeHeadFF[8];
	int m_bfmeTimeFF;
};

class BfmeOwnerFF
{
public:
	void bfmeGoFF(void);

	unsigned char m_bfmeHeadFF[4];
	BfmeThingFF *m_bfmeThingFF;
	BfmeStateFF *m_bfmeStateFF;
};

void BfmeOwnerFF::bfmeGoFF(void)
{
	BfmeStateFF *state = m_bfmeStateFF;
	BfmeThingFF *thing = m_bfmeThingFF;
	BfmeInnerFF *inner = state->m_bfmeInnerFF;
	int now = thing->m_bfmeTimeFF;
	int start = inner->m_bfmeStartFF;
	bfmeSendFF(now - start, 0, 0);
}
