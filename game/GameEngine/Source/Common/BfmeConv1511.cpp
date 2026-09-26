// Open-BFME5 conversions.

struct BfmeThingVNH
{
	char m_bfmePad00[0x34];
	int m_bfme34;
	char m_bfmePad38[0xc];
	int m_bfme44;
};

extern BfmeThingVNH *g_bfmeThingVNH;
extern int(__cdecl *g_bfmeNowVNH)();

void bfmeSetVNH(float secs)
{
	if (g_bfmeThingVNH == 0)
		return;

	int st = g_bfmeThingVNH->m_bfme34;

	if (st == 0)
		return;
	if (st == 3)
		return;

	BfmeThingVNH *p = g_bfmeThingVNH;
	int now = g_bfmeNowVNH();

	p->m_bfme44 = now - (int)(secs * -1000.0f);
}
