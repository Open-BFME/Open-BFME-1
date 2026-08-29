// Open-BFME5 conversions.

extern "C" __declspec(dllimport) void __stdcall bfmeApply1170(void *h);
extern "C" void *g_bfmeCursors1170[];

class BfmeM1170
{
public:
	void bfmeSetCursor1170(int c);
	void bfmeBase1170(int c);
	char bfmeCheck1170(void);
	char m_bfmePad0[0x4da8];
	int m_bfme4da8;
	char m_bfmePad1[0x1070];
	int m_bfme5e1c;
	int m_bfme5e20;
	char m_bfme5e24;
};

void BfmeM1170::bfmeSetCursor1170(int c)
{
	bfmeBase1170(c);

	if (m_bfme5e24 != 0)
		return;

	if (c != 0 && bfmeCheck1170() != 0)
		bfmeApply1170(g_bfmeCursors1170[m_bfme5e20 + c * 8]);
	else
		bfmeApply1170(0);

	m_bfme4da8 = c;
	m_bfme5e1c = c;
}
