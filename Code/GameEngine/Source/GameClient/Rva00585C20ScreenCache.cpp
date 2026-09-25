// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// retail RVA 0x00585C20. this->m_10 is a log id; this->m_18 a coordinate the
// global g_bfmeStateDF's vslot 9 (+0x24) tries to project to screen ints. On
// success, if the projected x/y differ from the cached this->m_40/this->m_44,
// bfmeGo1077B (0x0051B1A0, BfmeConv1077.cpp) logs the change and the cache is
// updated; identical values are a silent no-op. On projection failure, the
// cache is reset to the -1000 sentinel (and logged) unless it is already
// there. No caller, owner class, or vtable slot identifies this body, so the
// owner/coordinate layout is address-derived.
//
// Shape: the cache is a two-int pair assigned whole in each branch; the
// failure sentinel is written x first, then y.

class Gen_00609320
{
public:
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
	virtual void bfmeSlot2();
	virtual void bfmeSlot3();
	virtual void bfmeSlot4();
	virtual void bfmeSlot5();
	virtual void bfmeSlot6();
	virtual void bfmeSlot7();
	virtual void bfmeSlot8();
	virtual bool bfmeProjectToScreen(const void *coord, int *outXY);
};

extern Gen_00609320 *g_bfmeStateDF;

void bfmeGo1077B(int a, float b, float c);

struct Rva00585C20Point
{
	int x;
	int y;
};

struct Rva00585C20Param
{
	unsigned char m_head[0x10];
	int m_logId;				// +0x10
	unsigned char m_gap14[4];
	unsigned char m_coord[0x28];		// +0x18
	Rva00585C20Point m_cached;		// +0x40
};

class Rva00585C20Owner
{
public:
	void rva00585c20(Rva00585C20Param *p);
};

// retail RVA 0x00585C20
void Rva00585C20Owner::rva00585c20(Rva00585C20Param *p)
{
	int logId = p->m_logId;
	Rva00585C20Point screen;
	bool ok = g_bfmeStateDF->bfmeProjectToScreen(p->m_coord, &screen.x);

	if (ok)
	{
		if (screen.x == p->m_cached.x && screen.y == p->m_cached.y)
			return;

		bfmeGo1077B(logId, (float)screen.x, (float)screen.y);
		p->m_cached = screen;
	}
	else
	{
		if (p->m_cached.x == -1000 && screen.y == -1000)
			return;
		bfmeGo1077B(logId, -1000.0f, -1000.0f);
		screen.x = -1000;
		screen.y = -1000;
		p->m_cached = screen;
	}
}
