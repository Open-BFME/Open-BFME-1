// Open-BFME5 conversions.

// Callees: bfmeGo1015I (0x6C8890) ILT 0x449F4 -> 0x00720C20 Rva00720BB0Context::scan,
// ILT 0x20CC -> bfmeDo1015B; bfmeGo1015L (0x808800) tail jump -> 0x007E86C0
// Gen_007e86c0::m; bfmeGo1015M (0x8CB730) -> 0x008A48A0 BfmeM1015::bfmeFallback1015.
struct Rva00720C20Coord3D;

class Rva00720BB0Context
{
public:
	void scan(const Rva00720C20Coord3D &center, float radius, void *arg);
};

class Gen_007e86c0
{
public:
	void m(void);
};

class BfmeI1015B
{
public:
	void bfmeDo1015B(int a, int b);
};

class BfmeI1015
{
public:
	void bfmeGo1015I(int a, int b, int c);

	char m_bfmePad[0x3098];
	Rva00720BB0Context *m_bfmeA;
	BfmeI1015B *m_bfmeB;
};

void BfmeI1015::bfmeGo1015I(int a, int b, int c)
{
	if (m_bfmeA != 0)
		m_bfmeA->scan(*(const Rva00720C20Coord3D *)a, *reinterpret_cast<float *>(&b), (void *)c);

	if (m_bfmeB != 0)
		m_bfmeB->bfmeDo1015B(a, b);
}


class BfmeMgr1015
{
public:
	virtual void bfmeVM01015();
	virtual void bfmeVM11015();
	virtual void bfmeVM21015();
	virtual void bfmeFree1015(int h, int f);
};

void *bfmeGo929C(void);

class BfmeL1015
{
public:
	void bfmeGo1015L(void);

	char m_bfmePad[0x10];
	int m_bfmeCount;
	int m_bfmeH;
};

void BfmeL1015::bfmeGo1015L(void)
{
	if (m_bfmeH != 0)
		((BfmeMgr1015 *)bfmeGo929C())->bfmeFree1015(m_bfmeH, 0);

	m_bfmeH = 0;
	m_bfmeCount = 0;
	reinterpret_cast<Gen_007e86c0 *>(this)->m();
}

class BfmeSub1015
{
public:
	virtual void bfmeVS01015();
	virtual void bfmeVS11015();
	virtual void bfmeVS21015();
	virtual void bfmeVS31015();
	virtual void bfmeVS41015();
	virtual void bfmeVS51015();
	virtual void bfmeVS61015();
	virtual void bfmeVS71015();
	virtual void bfmeVS81015();
	virtual void bfmeVS91015();
	virtual int bfmeTry1015(int a, int b);
};

class BfmeM1015
{
public:
	void bfmeGo1015M(int a, int b);
	int bfmeFallback1015(int a, const char **b);

	char m_bfmePad[0x20];
	BfmeSub1015 *m_bfmeSub;
};

void BfmeM1015::bfmeGo1015M(int a, int b)
{
	if (m_bfmeSub->bfmeTry1015(a, b) == 0)
		bfmeFallback1015(a, (const char **)b);
}

// The 0x012F12CC singleton is DisplayStringManager *TheDisplayStringManager,
// defined once in DisplayStringManager.cpp.  This TU keeps its own view of
// the vtable and casts at the use.
class DisplayStringManager;

class BfmeReg1015
{
public:
	virtual void bfmeVR01015();
	virtual void bfmeVR11015();
	virtual void bfmeVR21015();
	virtual void bfmeVR31015();
	virtual void bfmeVR41015();
	virtual void bfmeVR51015();
	virtual void bfmeVR61015();
	virtual void bfmeVR71015();
	virtual void bfmeVR81015();
	virtual void bfmeVR91015();
	virtual void bfmeDrop1015(int h);
};

extern DisplayStringManager *TheDisplayStringManager;		// 0x012F12CC
static inline BfmeReg1015 *theDisplayStringManagerView()
{
	return (BfmeReg1015 *)TheDisplayStringManager;
}

class BfmeO1015
{
public:
	void bfmeGo1015O(int h);

	char m_bfmePad[0xc4];
	int m_bfmeA;
	int m_bfmeB;
};

void BfmeO1015::bfmeGo1015O(int h)
{
	if (h != 0)
		theDisplayStringManagerView()->bfmeDrop1015(h);

	m_bfmeA = 0;
	m_bfmeB = 0;
}

