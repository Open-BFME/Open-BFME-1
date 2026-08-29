// Open-BFME5 conversions.

struct BfmeG1148
{
	char m_bfmePad0[0x18];
	char m_bfme18;
	char m_bfme19;
	char m_bfme1a;
	char m_bfme1b;
	char m_bfme1c;
	char m_bfmePad1[2];
	char m_bfme1f;
	char m_bfmePad2[8];
	char m_bfme28;
	char m_bfmePad3[0xf];
	char m_bfme38;
	char m_bfmePad4[0xb];
	char m_bfme44;
	char m_bfmePad5[2];
	char m_bfme47;
	char m_bfmePad6[0x10];
	char m_bfme58;
	char m_bfmePad7[0xb];
	char m_bfme64;
	char m_bfme65;
	char m_bfmePad8[2];
	int m_bfme68;
	char m_bfmePad9[4];
	char m_bfme70;
	char m_bfmePad10[0x1b];
	char m_bfme8c;
	char m_bfmePad11[0xaff];
	int m_bfmeb8c;
};

class BfmeS1148
{
public:
	int bfmeF01148(void);
	int bfmeF11148(void);
	char bfmeF21148(void);
	char bfmeF31148(void);
	char bfmeF41148(void);
	char bfmeF51148(void);
	char bfmeF61148(void);
	char bfmeF71148(void);
	char bfmeF81148(void);
	char bfmeF91148(void);
	char bfmeFa1148(void);
	char bfmeFb1148(void);
	char bfmeFc1148(void);
	char bfmeFd1148(void);
};

extern "C" BfmeG1148 *volatile g_bfmeG1148;

void bfmeGo1148(BfmeS1148 *s)
{
	int n = 2 - (int)(s->bfmeF01148() * 3 * 0.01f);

	if (n < 0)
		n = 0;
	else if (n > 2)
		n = 2;

	g_bfmeG1148->m_bfme68 = n;
	g_bfmeG1148->m_bfmeb8c = s->bfmeF11148() * 0x1d + 0x64;
	g_bfmeG1148->m_bfme64 = s->bfmeF21148();
	g_bfmeG1148->m_bfme65 = s->bfmeF31148();
	g_bfmeG1148->m_bfme28 = (char)(s->bfmeF41148() == 0);
	g_bfmeG1148->m_bfme70 = s->bfmeF51148();
	g_bfmeG1148->m_bfme58 = s->bfmeF61148();
	g_bfmeG1148->m_bfme44 = s->bfmeF71148();
	g_bfmeG1148->m_bfme38 = s->bfmeF71148();
	g_bfmeG1148->m_bfme47 = s->bfmeF81148();
	g_bfmeG1148->m_bfme8c = s->bfmeF91148();
	g_bfmeG1148->m_bfme1c = s->bfmeFa1148();
	BfmeG1148 *g = g_bfmeG1148;

	g->m_bfme1a = (char)(g->m_bfme1c == 0);
	g_bfmeG1148->m_bfme1b = s->bfmeFb1148();
	g_bfmeG1148->m_bfme1f = s->bfmeFc1148();
	g_bfmeG1148->m_bfme18 = s->bfmeFd1148();
}
