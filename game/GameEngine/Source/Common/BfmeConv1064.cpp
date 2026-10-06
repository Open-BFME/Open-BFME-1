// Open-BFME5 conversions.

class BfmeX1064;

class BfmeR1064
{
public:
	void bfmeRun1064(BfmeX1064 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

// Retail global 0x012F19E8; canonical definition in GameClient/GUI/WindowManager.cpp.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;


class AptLanLobby
{
public:
	void OnGameCreate(void);
	void bfmeSet1064B(char a);
	char bfmeChk1064(void);
	char m_bfmePad[0x250];
	BfmeX1064 *m_bfme250;
	char m_bfmePad2[0x40];
	char m_bfme294;
	char m_bfme295;
	char m_bfmePad3[0x112];
	int m_bfme3a8;
};

void AptLanLobby::OnGameCreate(void)
{
	if (m_bfme3a8 == 3) {
		if (bfmeChk1064()) {
			((BfmeR1064 *)g_rva012F19E8WindowManager)->bfmeRun1064(m_bfme250, "HostGame", 0, 0, 0, 0, 0, 0);
			m_bfme3a8 = 4;
		} else {
			m_bfme3a8 = 1;
		}
	}
}

void AptLanLobby::bfmeSet1064B(char a)
{
	if (!m_bfme294 && a == m_bfme295)
		return;
	m_bfme295 = a;
	m_bfme294 = 0;
	((BfmeR1064 *)g_rva012F19E8WindowManager)->bfmeRun1064(m_bfme250, a ? "EnableRemoveButton" : "DisableRemoveButton", 0, 0, 0, 0, 0, 0);
}

extern "C" __declspec(dllimport) int __cdecl _snprintf(char *b, unsigned int n, char *f, int a);

extern BfmeX1064 *g_bfmeV1064;
extern char *g_bfmeTbl1064[];
extern char g_bfmeFmtD1064[];

BfmeX1064 *bfmeMk1064(BfmeX1064 *a, BfmeX1064 *b);

void bfmeGo1064C(int a, int b)
{
	char buf[0x10];
	BfmeX1064 *x;

	_snprintf(buf, 0x10, g_bfmeFmtD1064, a);
	x = bfmeMk1064(g_bfmeV1064, g_bfmeV1064);
	((BfmeR1064 *)g_rva012F19E8WindowManager)->bfmeRun1064(x, "SetRegionPopupButtonState", 2, buf, g_bfmeTbl1064[b], 0, 0, 0);
}
