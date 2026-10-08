// Open-BFME5 conversions.

class BfmeX1066;

// Matched callee rows (callees.py, via ILT): BfmeLevelAN::bfmeBuildAN 0x004675F0,
// WindowManager::bfme_hideBackground 0x00468090, bfmeAptLevel00465CE0 0x00465CE0.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int a, int b, int c, int d, int e, int f, int g, int h);
};

class WindowManager
{
public:
	void bfme_hideBackground(bool hide);
};

class BfmeH1065;
int __cdecl bfmeAptLevel00465CE0(BfmeH1065 *h);

// The global at 0x012F19E8 is EA's
// `WindowManager *g_rva012F19E8WindowManager` (defined in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp); BfmeR1066 is this
// TU's view of the same object, so the uses cast.
extern WindowManager *g_rva012F19E8WindowManager;

extern const char g_rva01080FC0[2];

struct BfmeM1066
{
	char m_bfmePad[0xa9f];
	char m_bfmea9f;
};

// The one global at 0x012ED5C8 is EA's GlobalData *TheWritableGlobalData
// (defined in Common/GlobalData.cpp). This TU reads one byte at +0xA9F through
// a view struct, so the extern carries the canonical type and the view is cast.
class GlobalData;
extern GlobalData *TheWritableGlobalData;

class BfmeH1066;


class BfmeH1066
{
public:
	void bfmeGo1066A(int a);
	void bfmeGo1066B(int a);
	int bfmeHandle1066(int eventType, unsigned char eventCode, unsigned int flags);
	char m_bfmePad[0x250];
	BfmeX1066 *m_bfme250;
	char m_bfmePad2[4];
	char m_bfme258;
	char m_bfme259;
	char m_bfme25a;
	char m_bfme25b;
};

void BfmeH1066::bfmeGo1066A(int a)
{
	if (m_bfme25a)
		return;
	((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(
		(unsigned int)bfmeAptLevel00465CE0((BfmeH1065 *)this), (int)"Close", 0, 0, 0, 0, 0, 0);
	m_bfme25a = 1;
	if (!m_bfme25b) {
		g_rva012F19E8WindowManager->bfme_hideBackground(false);
		m_bfme25b = 1;
	}
}

void BfmeH1066::bfmeGo1066B(int a)
{
	char *s = ((BfmeM1066 *)TheWritableGlobalData)->m_bfmea9f
		? const_cast<char *>(g_rva01080FC0) : "0";

	((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(
		(unsigned int)m_bfme250, (int)"ShowDebugButtons", 1, (int)s, 0, 0, 0, 0);
	m_bfme258 = 1;
	if (m_bfme259) {
		m_bfme25a = 1;
		m_bfme259 = 0;
	}
}

int BfmeH1066::bfmeHandle1066(
	int eventType, unsigned char eventCode, unsigned int flags)
{
	if (eventType != 21)
		return 0;

	switch (eventCode) {
		case 1:
		case 28:
		case 41:
			break;
		default:
			return 0;
	}

	if (flags & 1)
		bfmeGo1066A(0);

	return 1;
}
