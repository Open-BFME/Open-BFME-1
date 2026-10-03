// Open-BFME5 conversions.

struct BfmeThingVNH
{
	char m_bfmePad00[0x34];
	int m_bfme34;
	char m_bfmePad38[0xc];
	int m_bfme44;
};

extern void *g_rva012F49D0;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

void bfmeSetVNH(float secs)
{
	if (g_rva012F49D0 == 0)
		return;

	int st = static_cast<BfmeThingVNH *>(g_rva012F49D0)->m_bfme34;

	if (st == 0)
		return;
	if (st == 3)
		return;

	BfmeThingVNH *p = static_cast<BfmeThingVNH *>(g_rva012F49D0);
	int now = timeGetTime();

	p->m_bfme44 = now - (int)(secs * -1000.0f);
}
