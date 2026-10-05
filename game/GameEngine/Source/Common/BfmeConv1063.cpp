// Open-BFME5 conversions.

class BfmeX1063;

class BfmeR1063
{
public:
	void bfmeRun1063(BfmeX1063 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class BfmeQ1063
{
public:
	void bfmeGo1063Q(void);
	char m_bfmePad[0x250];
	BfmeX1063 *m_bfme250;
	char m_bfmePad2[0x154];
	int m_bfme3a8;
	char m_bfmePad3[0x28];
	int m_bfme3d4;
};

void BfmeQ1063::bfmeGo1063Q(void)
{
	m_bfme3a8 = 1;
	if (!(m_bfme3d4 & 2)) {
		((BfmeR1063 *)g_rva012F19E8WindowManager)->bfmeRun1063(m_bfme250, "EnableJoinGame", 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
}
