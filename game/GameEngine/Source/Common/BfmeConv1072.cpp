// Open-BFME5 conversions.

class BfmeX1072;

class BfmeR1072
{
public:
	void bfmeRun1072(BfmeX1072 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern char g_bfmeFmtA1072[];
extern char g_bfmeFmtB1072[];
extern char g_bfmeFmtD1072[];
extern char g_bfmeLitA1072[];
extern unsigned char g_optByte12F4AD1;

extern "C" __declspec(dllimport) int __cdecl sprintf(char *b, char *f, int a);

class BfmeQ1072
{
public:
	void bfmeGo1072A(int a, int b);
	int bfmeGo1072B(void);
	void bfmeGo1072C(char a);
	char m_bfmePad[0x5c];
	BfmeX1072 *m_bfme5c;
	char m_bfmePad1[0x20];
	int m_bfme80[116];
	BfmeX1072 *m_bfme250;
	char m_bfmePad2[4];
	int m_bfme258;
	char m_bfmePad3[0x178];
	int m_bfme3d4;
};

void BfmeQ1072::bfmeGo1072A(int a, int b)
{
	char buf1[0x40];
	char buf2[0x40];

	sprintf(buf1, g_bfmeFmtA1072, m_bfme80[a]);
	sprintf(buf2, g_bfmeFmtA1072, b);
	((BfmeR1072 *)g_rva012F19E8WindowManager)->bfmeRun1072(m_bfme5c, g_bfmeFmtB1072, 2, buf1, buf2, 0, 0, 0);
}

int BfmeQ1072::bfmeGo1072B(void)
{
	if (m_bfme258 == 1) {
		if (g_optByte12F4AD1) {
			((BfmeR1072 *)g_rva012F19E8WindowManager)->bfmeRun1072(m_bfme250, "assignOpen", 1, g_bfmeLitA1072, 0, 0, 0, 0);
			m_bfme258 = 3;
		} else {
			((BfmeR1072 *)g_rva012F19E8WindowManager)->bfmeRun1072(m_bfme250, "assignOpen", 1, "normal", 0, 0, 0, 0);
			m_bfme258 = 2;
		}
	}
	return 1;
}

void BfmeQ1072::bfmeGo1072C(char a)
{
	if ((a & 1) && !(m_bfme3d4 & 1)) {
		((BfmeR1072 *)g_rva012F19E8WindowManager)->bfmeRun1072(m_bfme250, g_bfmeFmtD1072, 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 1;
	}
	if ((a & 2) && !(m_bfme3d4 & 2)) {
		((BfmeR1072 *)g_rva012F19E8WindowManager)->bfmeRun1072(m_bfme250, "EnableJoinGame", 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
}
