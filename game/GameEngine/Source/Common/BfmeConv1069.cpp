// Open-BFME5 conversions.

class BfmeX1069;

// ILT 0x00015235 -> matched BfmeLevelAN::bfmeBuildAN (0x004675F0).
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int a, int b, int c, int d, int e, int f, int g);
};

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the call through it, so the pointee stays the local BfmeLevelAN view and the
// access is cast at the use.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;

class BfmeH1069
{
public:
	void bfmeSet1069B(char a, char b);
	char m_bfmePad[0x34];
	BfmeH1069 *m_bfme34;
	char m_bfmePad2[0x19d];
	char m_bfme1d5;
	char m_bfmePad3[0x7a];
	BfmeX1069 *m_bfme250;
};

void BfmeH1069::bfmeSet1069B(char a, char b)
{
	if (!b && m_bfme1d5 == a)
		return;
	m_bfme1d5 = a;
	if (a)
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfme34->m_bfme250, (int)"CallChild", 1, (int)"EnableButtonPlayGame", 0, 0, 0, 0);
	else
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfme34->m_bfme250, (int)"CallChild", 1, (int)"DisableButtonPlayGame", 0, 0, 0, 0);
}
