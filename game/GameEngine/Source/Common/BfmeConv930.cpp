// cl: /MD
#include <stdlib.h>

// Open-BFME5 conversions.

class BfmeSub911E
{
public:
	void bfmePrep911E();
};

struct BfmeB930A
{
	char m_bfmePad[8];
	void *m_bfmeP;
};

struct BfmeA930A
{
	char m_bfmePad[0x14];
	BfmeB930A *m_bfmeB;
};

class BfmeThing930A
{
public:
	void bfmeGo930A();
	BfmeA930A *m_bfmeA;
};

void BfmeThing930A::bfmeGo930A()
{
	BfmeA930A *a = m_bfmeA;
	if (!a)
		return;
	BfmeB930A *b = a->m_bfmeB;
	if (!b)
		return;
	if (!b->m_bfmeP)
		return;
	((BfmeSub911E *)b)->bfmePrep911E();
}

class BfmeGlob930C
{
public:
	virtual void bfmeSlot930C0();
	virtual void bfmeVirt930C(void *a, int f);
};

// The global this TU reads is the same storage the setter at Rva 0x009A58C0
// writes and the allocator reads; its one defining name is the tiny store's
// member, redeclared here exactly as TinyGlobalStores.cpp defines it.
class Rva009A58C0
{
public:
	static void store( int value );
	static int s_value;
};

void bfmeGo930C(void *a)
{
	BfmeGlob930C *g = (BfmeGlob930C *)Rva009A58C0::s_value;
	if (g) {
		g->bfmeVirt930C(a, 0);
		return;
	}
	free(a);
}

void bfmeFreeRC(void *p);

class BfmeOldKB
{
public:
	void bfmeRelKB();
};

class StreakRendererClass
{
public:
	void bfmeGo930D();
	BfmeOldKB *m_bfmeP;
	char m_bfmePad[0x44];
	void *m_vertexBuffer;
};

void StreakRendererClass::bfmeGo930D()
{
	bfmeFreeRC(m_vertexBuffer);
	BfmeOldKB *s = m_bfmeP;
	if (s)
		s->bfmeRelKB();
}

void bfmeCall930G(int a, int b, int n, void *p, int m, int f);

void bfmeGo930G(void *a, int n)
{
	bfmeCall930G(4, 0, n, a, n * 3, 0);
}
