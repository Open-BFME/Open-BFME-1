// Open-BFME5 conversions.

class BfmeX1066;

class BfmeR1066
{
public:
	void bfmeRun1066(BfmeX1066 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
	void bfmeStop1066(int a);
};

// The global at 0x012F19E8 is EA's
// `WindowManager *g_rva012F19E8WindowManager` (defined in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp); BfmeR1066 is this
// TU's view of the same object, so the uses cast.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern char g_bfmeFmtA1066[];
extern char g_bfmeFmtB1066[];
extern char g_bfmeLitA1066[];
extern char g_bfmeLitB1066[];

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

BfmeX1066 *__cdecl bfmeConv1066(BfmeH1066 *h);

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
	((BfmeR1066 *)g_rva012F19E8WindowManager)->bfmeRun1066(bfmeConv1066(this), g_bfmeFmtA1066, 0, 0, 0, 0, 0, 0);
	m_bfme25a = 1;
	if (!m_bfme25b) {
		((BfmeR1066 *)g_rva012F19E8WindowManager)->bfmeStop1066(0);
		m_bfme25b = 1;
	}
}

void BfmeH1066::bfmeGo1066B(int a)
{
	char *s = ((BfmeM1066 *)TheWritableGlobalData)->m_bfmea9f
		? g_bfmeLitA1066 : g_bfmeLitB1066;

	((BfmeR1066 *)g_rva012F19E8WindowManager)->bfmeRun1066(m_bfme250, g_bfmeFmtB1066, 1, s, 0, 0, 0, 0);
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
