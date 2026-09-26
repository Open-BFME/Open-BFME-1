// ?bfmeTailBOC@BfmeThingBOC@@QAEX_N@Z
// partial score=0.2 date=2026-09-21
// cl: /DNDEBUG /MD

// Retail 0x003A44A0, 165 bytes. Reached ONLY through the matched tail call
// in BfmeThingBOC::bfmeGoBOC (Code/GameEngine/Source/Common/BfmeConv502.cpp,
// retail 0x003A47C0 -> ILT 0x00020509 -> here): `bfmeTailBOC(1);` compiles
// to a plain JMP that leaves ECX (bfmeGoBOC's `this`) untouched, so this
// body reads its object through ECX like an ordinary __thiscall method even
// though the only prior declaration spells it a free `__stdcall
// bfmeTailBOC(int)` -- that declaration only describes the CALL SITE bytes
// (already matched, unaffected by anything here), not this body's real ABI.
// BfmeThingBOC::m_bfmeA/m_bfmeB (void* at +0xc/+0x10 in BfmeConv502.cpp) are
// read here both as raw ints (bfmeRunESM's two int params) and, later, as
// float bit patterns (two of the three Coord3D components built for the
// vtable-slot-7 call two dwords further in), so the owning class is the
// proven BfmeThingBOC; the method itself keeps the address-derived name
// since no source declares it.

typedef bool Bool;

class BfmeThingESM;

struct BfmePairESM
{
	BfmePairESM(int a, int b)
	{
		m_bfmeAESM = a;
		m_bfmeBESM = b;
	}

	BfmePairESM(const BfmePairESM &other) throw()
	{
		m_bfmeAESM = other.m_bfmeAESM;
		m_bfmeBESM = other.m_bfmeBESM;
	}

	~BfmePairESM();

	int m_bfmeAESM;
	int m_bfmeBESM;
};

class BfmeHostESM
{
public:
	char bfmeRunESM(int a, int b, void **out);
};

extern BfmeHostESM *g_bfmeStateDF;		// retail 0x012F7048

struct Coord3D
{
	float x, y, z;
};

#define BFME_VOID_SLOT(N) virtual void slot##N();

class BOCElement
{
public:
	BFME_VOID_SLOT(00) BFME_VOID_SLOT(01) BFME_VOID_SLOT(02)
	virtual void slot03();				// offset 0xc
	BFME_VOID_SLOT(04) BFME_VOID_SLOT(05) BFME_VOID_SLOT(06)
	virtual void slot07(Coord3D vec);	// offset 0x1c

	char m_pad[0xa8];
	float m_field0xa8;
};

#undef BFME_VOID_SLOT

class BfmeThingBOC
{
public:
	void bfmeTailBOC(Bool flag);

	unsigned char m_bfmeHead[0xc];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_pad2[0x48 - 0x14];
	BOCElement **m_begin;		// +0x48
	BOCElement **m_end;		// +0x4c
};

void BfmeThingBOC::bfmeTailBOC(Bool flag)
{
	void *outRaw = 0;
	Bool doExtra = flag;

	if (doExtra)
	{
		g_bfmeStateDF->bfmeRunESM(*(int *)&m_bfmeA, *(int *)&m_bfmeB, &outRaw);

		for (int i = 0; i < (int)(m_end - m_begin); ++i)
		{
			BOCElement *elem = m_begin[i];

			Coord3D vec;
			vec.x = *(float *)&m_bfmeA;
			vec.y = *(float *)&m_bfmeB;
			vec.z = *(float *)&outRaw + elem->m_field0xa8;
			elem->slot07(vec);

			m_begin[i]->slot03();
		}
	}
	else
	{
		for (int i = 0; i < (int)(m_end - m_begin); ++i)
			m_begin[i]->slot03();
	}
}
