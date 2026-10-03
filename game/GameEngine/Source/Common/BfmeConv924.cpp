// Open-BFME5 conversions.

struct BfmeNodeLC
{
	char m_bfmeA;
	char m_bfmePad0[3];
	int m_bfmeB;
	char m_bfmePad1[4];
	unsigned int m_bfmeBits;
	unsigned short m_bfmeW;
	char m_bfmePad2[0x16];
	char m_bfmeC;
	char m_bfmePad3[3];
	int m_bfmeD;
};

class BfmeKeyLC
{
public:
	BfmeNodeLC *bfmeFindLC();
};

void bfmeGo924A(BfmeKeyLC *k, char v)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			*((char *)&o->m_bfmeBits + 3) = (v == 0);
	}
}

int bfmeGo924B(BfmeKeyLC *k)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o && o->m_bfmeA)
			return o->m_bfmeB;
	}
	return 0x64;
}

int bfmeGo924C(BfmeKeyLC *k)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o && o->m_bfmeC)
			return o->m_bfmeD;
	}
	return 0;
}

void bfmeGo924D(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = mask;
			o->m_bfmeBits = o->m_bfmeBits | m;
		}
	}
}

void bfmeGo924E(BfmeKeyLC *k, unsigned int mask)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o) {
			unsigned int m = ~mask;
			o->m_bfmeBits = o->m_bfmeBits & m;
		}
	}
}

void bfmeGo924F(BfmeKeyLC *k, unsigned short w)
{
	if (k) {
		BfmeNodeLC *o = k->bfmeFindLC();
		if (o)
			o->m_bfmeW = w;
	}
}

// The retail global at 0x012F19E8, named by its one linked-build definition
// (WindowManager *g_rva012F19E8WindowManager).  BfmeLevelAN is this TU's view
// of the pointee; the casts at the uses are pointer-size neutral.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

class LookAtTranslator;
extern LookAtTranslator *TheLookAtTranslator;
struct Rva005A6790Object
{
	int setValue(int value);
};

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8);
};

extern const char g_rva01080FC0[2];
extern char g_bfmeJpegExtendedMessage;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
class WindowLayout;
void ReleaseWindowLayout(WindowLayout *layout);

class BfmeOne924G
{
public:
	void bfmeCall924G();

	char m_bfmePad924G[0x34];
	int m_bfmeState924G;
	int m_bfmeMode924G;
	char m_bfmePad924G2[8];
	unsigned int m_bfmeTimestamp924G;
	unsigned char m_bfmeSingle924G;
	unsigned char m_bfmeHideSingle924G;
};

class BfmeTwo924G
{
public:
	virtual void bfmeSlot92400();
	virtual void bfmeSlot92401();
	virtual void bfmeSlot92402();
	virtual void bfmeSlot92403();
	virtual void bfmeSlot92404();
	virtual void bfmeTail924G();
};

extern void *g_rva012F49D0;
extern BfmeTwo924G *g_bfme924TwoG;

void bfmeGo924G(void)
{
	if (g_rva012F49D0)
		static_cast<BfmeOne924G *>(g_rva012F49D0)->bfmeCall924G();
	if (g_bfme924TwoG)
		g_bfme924TwoG->bfmeTail924G();
}

void BfmeOne924G::bfmeCall924G()
{
	int state = m_bfmeState924G;
	if (state == 2)
	{
		if (TheLookAtTranslator)
			((Rva005A6790Object *)TheLookAtTranslator)->setValue(state);

		const char *message = m_bfmeSingle924G
			? g_rva01080FC0 : &g_bfmeJpegExtendedMessage;
		int mode = m_bfmeMode924G;
		const char *button = mode == 2 ? "YesNo"
			: mode == 1 ? "OkCancel"
			: mode == 3 ? "NonInteractive" : "Ok";
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(11,
			(int)"ShowMessageBox", 2, (int)button, (int)message, 0, 0, 0);
		m_bfmeState924G = 1;
	}
	else if (state == 3)
	{
		const char *message = m_bfmeHideSingle924G
			? g_rva01080FC0 : &g_bfmeJpegExtendedMessage;
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(11,
			(int)"HideMessageBox", 1, (int)message, 0, 0, 0, 0);
		m_bfmeState924G = 0;
		m_bfmeHideSingle924G = 0;
	}
	else if (state == 4)
	{
		int mode = m_bfmeMode924G;
		const char *button = mode == 2 ? "YesNo"
			: mode == 1 ? "OkCancel"
			: mode == 3 ? "NonInteractive" : "Ok";
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(11,
			(int)"ChangeMessageBox", 1, (int)button, 0, 0, 0, 0);
		m_bfmeState924G = 1;
	}

	if (m_bfmeState924G != 0
		&& (unsigned int)timeGetTime() > m_bfmeTimestamp924G)
		ReleaseWindowLayout(0);
}
