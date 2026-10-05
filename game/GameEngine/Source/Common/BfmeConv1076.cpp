// Open-BFME5 conversions.

class BfmeX1076;

// TU-local view of retail 0x012F19E8 (EA's WindowManager *).  The global is
// declared under its one canonical mangled name; this view keeps the member
// this body calls and is cast at the use site.
class WindowManager;

class BfmeR1076
{
public:
	void bfmeRun1076(BfmeX1076 *a, char *b, int c, char *d, char *e, char *f, char *g, char *h);
};

extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

extern bool j_000490a8(void);
extern void j_00011464(void);
extern void j_00010762(void);

class Rva003BCB00
{
public:
	bool flag(void);
};

class BfmeThingBZF
{
public:
	void bfmeGoBZF(void);
};

class BfmeMessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot2C(void) = 0;
	virtual void slot30(void) = 0;
	virtual void appendMessage(unsigned int type) = 0;
};

class GameLogic;
class MessageStream;
// The canonical global at 0x012F1028 (EA's "TheLivingWorldLogic", defined in
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp); this TU
// only needs its address.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern GameLogic *TheGameLogic;
extern MessageStream *TheMessageStream;

#define BFME_GLOBAL_AT(TYPE, ADDRESS) (*(TYPE *)(ADDRESS))

class BfmeQ1076
{
public:
	int bfmeGo1076A(int a, char b, char c);
	void bfmeF1076(void);
	void bfmeG1076(int a);
	char m_bfmePad[0x250];
	BfmeX1076 *m_bfme250;
	char m_bfmePad1[4];
	int m_bfme258;
	int m_bfme25c;
};

int BfmeQ1076::bfmeGo1076A(int a, char b, char c)
{
	if (a != 0x15 || b != 1 || !(c & 1))
		return 0;
	if (m_bfme25c == 0 && m_bfme258 != 2)
		((BfmeR1076 *)g_rva012F19E8WindowManager)->bfmeRun1076(m_bfme250, "EscapeButtonPressed", 0, 0, 0, 0, 0, 0);
	else if (m_bfme25c != 0 && m_bfme258 == 0)
		bfmeF1076();
	else if (m_bfme25c == 0 && m_bfme258 == 2)
		bfmeG1076(0);
	return 1;
}

void BfmeQ1076::bfmeG1076(int)
{
	if (m_bfme258 != 2)
	{
		if (j_000490a8())
		{
			m_bfme258 = 2;
			return;
		}
	}

	if (!BFME_GLOBAL_AT(Rva003BCB00 *, &TheLivingWorldLogic)->flag())
	{
		BFME_GLOBAL_AT(BfmeThingBZF *, &TheGameLogic)->bfmeGoBZF();
		j_00011464();
		return;
	}

	BFME_GLOBAL_AT(BfmeMessageStream *, &TheMessageStream)->appendMessage(0x1D);
	j_00010762();
}
