// Open-BFME5 conversions.

class BfmeX1063;

// Retail calls ILT 0x00015235 -> 0x004675F0, the matched level-path builder.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8);
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
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfme250, (int)"EnableJoinGame", 0, 0, 0, 0, 0, 0);
		m_bfme3d4 |= 2;
	}
}
