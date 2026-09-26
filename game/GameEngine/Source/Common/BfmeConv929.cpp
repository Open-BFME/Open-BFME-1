// Open-BFME5 conversions.

class BfmeThing929B
{
public:
	void bfmeGo929B(void *a, void *b);
	char m_bfmePad[8];
	void (*m_bfmeFn)(void *a, void *b);
};

void BfmeThing929B::bfmeGo929B(void *a, void *b)
{
	void (*fn)(void *, void *) = m_bfmeFn;
	if (!fn)
		return;
	if (!a)
		return;
	fn(a, b);
}

extern void *g_bfme929Ptr;
extern char g_bfme929Str[];
void bfmeInit929C(char *s);

void *bfmeGo929C(void)
{
	void *p = g_bfme929Ptr;
	if (!p) {
		bfmeInit929C(g_bfme929Str);
		p = g_bfme929Ptr;
	}
	return p;
}

class BfmeNext929D
{
public:
	int bfmeNext929D(int i);
};

class BfmeThing929D
{
public:
	int bfmeGo929D(int i);
	char m_bfmePad[0x18];
	int m_bfmeVal;
};

int BfmeThing929D::bfmeGo929D(int i)
{
	if (i == 0)
		return m_bfmeVal;
	return ((BfmeNext929D *)((char *)this + 8))->bfmeNext929D(i - 1);
}

struct BfmeGlob929E
{
	char m_bfmePad[0x126c];
	void *m_bfmeP;
};

extern BfmeGlob929E *g_bfme929Glob;
void bfmeCall929E(void *p, void **out);

void bfmeGo929E(void *a)
{
	void *p = g_bfme929Glob->m_bfmeP;
	if (p)
		bfmeCall929E(p, &a);
}

struct BfmeArg929F
{
	char m_bfmePad[0x80c];
	void *m_bfmeP;
};

extern char g_bfme929Tab[];
void bfmeCall929F(void *p, char *tab, BfmeArg929F *a);

void bfmeGo929F(BfmeArg929F *a)
{
	bfmeCall929F(a->m_bfmeP, g_bfme929Tab, a);
}

struct BfmeSub929G
{
	char m_bfmePad[6];
	unsigned short m_bfmeW;
};

class BfmeThing929G
{
public:
	unsigned short bfmeGo929G();
	void bfmeInit929G();
	BfmeSub929G *m_bfmeP;
};

unsigned short BfmeThing929G::bfmeGo929G()
{
	if (m_bfmeP->m_bfmeW == 0)
		bfmeInit929G();
	return m_bfmeP->m_bfmeW;
}
