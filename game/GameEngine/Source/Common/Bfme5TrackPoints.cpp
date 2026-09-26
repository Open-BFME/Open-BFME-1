// Open-BFME5 conversions: paired point setters and a ref-holding constructor.

void * __cdecl operator new(unsigned int n);

extern void *g_bfme5RefVtableC;

class Gen_0093D200
{
public:
	bool bfmeSetPoint(float x, float y);
};

class Gen_0093D250
{
public:
	bool bfmeSetPoint(float x, float y);
};

class Bfme5TrackA
{
public:
	void bfmeSetPoint(float x, float y);

	char m_bfmePad0[0x14];
	Gen_0093D200 m_bfmeSecond;
	char m_bfmePad1[0xcb];
	Gen_0093D200 m_bfmeFirst;
	char m_bfmePad2[0x12b];
	char m_bfmeDirty;
};

void Bfme5TrackA::bfmeSetPoint(float x, float y)
{
	if (m_bfmeFirst.bfmeSetPoint(x, y))
		m_bfmeDirty = 1;

	if (m_bfmeSecond.bfmeSetPoint(x, y))
		m_bfmeDirty = 1;
}

class Bfme5TrackB
{
public:
	void bfmeSetPoint(float x, float y);

	char m_bfmePad0[0x14];
	Gen_0093D250 m_bfmeSecond;
	char m_bfmePad1[0xcb];
	Gen_0093D250 m_bfmeFirst;
	char m_bfmePad2[0x12b];
	char m_bfmeDirty;
};

void Bfme5TrackB::bfmeSetPoint(float x, float y)
{
	if (m_bfmeFirst.bfmeSetPoint(x, y))
		m_bfmeDirty = 1;

	if (m_bfmeSecond.bfmeSetPoint(x, y))
		m_bfmeDirty = 1;
}

struct Bfme5RefX
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	Bfme5RefX *m_bfmeInner;
};

struct Bfme5RefSource
{
	Bfme5RefX *m_bfmePtr;
};

class Bfme5RefHolderC
{
public:
	Bfme5RefHolderC(Bfme5RefSource *s);

	Bfme5RefX *m_bfmeNode;
};

Bfme5RefHolderC::Bfme5RefHolderC(Bfme5RefSource *s)
{
	Bfme5RefX *q = (Bfme5RefX *)operator new(12);
	Bfme5RefX *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfme5RefVtableC;

		Bfme5RefX *r = s->m_bfmePtr;

		q->m_bfmeInner = r;

		if (r)
			++r->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}
