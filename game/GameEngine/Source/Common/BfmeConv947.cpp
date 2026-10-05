// Open-BFME5 conversions.

struct BfmeSrc947
{
	char m_bfmePad[0xc];
	int m_bfmeVal;
};

extern char g_bfme947A1[];
extern char g_bfme947A2[];
extern char g_bfme947A3[];
extern char g_bfme947A4[];
extern char g_bfme947A5[];

class BfmeThing947A
{
public:
	BfmeThing947A(void *a, BfmeSrc947 *b);
	char *volatile m_bfme00;
	void *volatile m_bfme04;
	char *volatile m_bfme08;
	char *volatile m_bfme0c;
	volatile int m_bfme10;
};

BfmeThing947A::BfmeThing947A(void *a, BfmeSrc947 *b)
{
	m_bfme04 = a;
	m_bfme08 = g_bfme947A1;
	m_bfme0c = g_bfme947A2;
	m_bfme10 = 0;
	m_bfme00 = g_bfme947A3;
	m_bfme08 = g_bfme947A4;
	m_bfme0c = g_bfme947A5;
	m_bfme10 = b->m_bfmeVal;
}

extern char g_bfme947B1[];
extern char g_bfme947B2[];
extern char g_bfme947B3[];
extern char g_bfme947B4[];
extern char g_bfme947B5[];

class BfmeThing947B
{
public:
	BfmeThing947B(void *a, BfmeSrc947 *b);
	char *volatile m_bfme00;
	void *volatile m_bfme04;
	char *volatile m_bfme08;
	char *volatile m_bfme0c;
	volatile int m_bfme10;
};

BfmeThing947B::BfmeThing947B(void *a, BfmeSrc947 *b)
{
	m_bfme04 = a;
	m_bfme08 = g_bfme947B1;
	m_bfme0c = g_bfme947B2;
	m_bfme10 = 0;
	m_bfme00 = g_bfme947B3;
	m_bfme08 = g_bfme947B4;
	m_bfme0c = g_bfme947B5;
	m_bfme10 = b->m_bfmeVal;
}

struct BfmeObj947C
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
	char m_bfmePad2[7];
	int m_bfmeVal;
};

struct BfmeAux947C
{
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeGlob947C
{
public:
	void bfmeTailB947C();
};

class BfmeAptScreenQuitMenu;
extern BfmeAptScreenQuitMenu *g_obj12F4B40;
// retail 0x012F4B58: the one identity of that address is the shell singleton
// ?TheShell@@3PAVShell@@A.  The view above is this TU's own layout of it, so
// the reference carries the defining name and the view is selected by a cast.
class Shell;
extern Shell *TheShell;
// retail 0x012F19E8: the canonical spelling is
// ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A, defined once in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU reaches the
// same address through its own BfmeGlob947C view, so it casts at the use; the
// view keeps the callee's mangled spelling
// ?bfmeTailB947C@BfmeGlob947C@@QAEXXZ.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;
void bfmeTailA947C(void);

void bfmeGo947C(void)
{
	BfmeObj947C *p = reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40);
	if (p) {
		if (p->m_bfmeFlag)
			return;
		p->m_bfmeFlag = 1;
		reinterpret_cast<BfmeObj947C * &>(g_obj12F4B40)->m_bfmeVal = 0;
		((BfmeAux947C *)TheShell)->m_bfmeFlag = 1;
		((BfmeGlob947C *)g_rva012F19E8WindowManager)->bfmeTailB947C();
	} else {
		bfmeTailA947C();
	}
}
