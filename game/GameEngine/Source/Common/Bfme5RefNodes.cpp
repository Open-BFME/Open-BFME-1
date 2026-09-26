// Open-BFME5 conversions: sixteen-byte nodes built by a `new` expression.

void * __cdecl operator new(unsigned int n);

// This named THREE different globals. Split by RVA; the name claims an
// address and nothing more.
extern void *g_bfmeRva010FE034Vt;
extern void *g_bfmeRva010FE04CVt;
extern void *g_bfmeRva0109FB98Vt;

struct Bfme5RefY
{
	void *m_bfmeVptr;
	int m_bfmeRefCount;
	Bfme5RefY *m_bfmeInner0;
	Bfme5RefY *m_bfmeInner1;
};

struct Bfme5RefPair
{
	Bfme5RefY *m_bfmeA;
	Bfme5RefY *m_bfmeB;
};

class Bfme5RefHolderD
{
public:
	Bfme5RefHolderD(Bfme5RefPair *s);

	Bfme5RefY *m_bfmeNode;
};

Bfme5RefHolderD::Bfme5RefHolderD(Bfme5RefPair *s)
{
	Bfme5RefY *q = (Bfme5RefY *)operator new(16);
	Bfme5RefY *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfmeRva010FE034Vt;

		Bfme5RefY *r0 = s->m_bfmeA;

		q->m_bfmeInner0 = r0;

		if (r0)
			++r0->m_bfmeRefCount;

		Bfme5RefY *r1 = s->m_bfmeB;

		q->m_bfmeInner1 = r1;

		if (r1)
			++r1->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}

class Bfme5RefHolderE
{
public:
	Bfme5RefHolderE(Bfme5RefPair *s);

	Bfme5RefY *m_bfmeNode;
};

Bfme5RefHolderE::Bfme5RefHolderE(Bfme5RefPair *s)
{
	Bfme5RefY *q = (Bfme5RefY *)operator new(16);
	Bfme5RefY *p;

	if (q) {
		q->m_bfmeRefCount = 0;
		q->m_bfmeVptr = &g_bfmeRva010FE04CVt;

		Bfme5RefY *r0 = s->m_bfmeA;

		q->m_bfmeInner0 = r0;

		if (r0)
			++r0->m_bfmeRefCount;

		Bfme5RefY *r1 = s->m_bfmeB;

		q->m_bfmeInner1 = r1;

		if (r1)
			++r1->m_bfmeRefCount;

		p = q;
	} else {
		p = 0;
	}

	m_bfmeNode = p;

	if (p)
		++p->m_bfmeRefCount;
}

struct Bfme5PushNode
{
	void *m_bfmeVptr;
	Bfme5PushNode *m_bfmeNext;
	void *m_bfmeA;
	void *m_bfmeB;
};

class Bfme5PushList
{
public:
	void bfmePushFront(void *a, void *b);

	int m_bfme00;
	Bfme5PushNode *m_bfmeHead;
	int m_bfme08;
	int m_bfmeCount;
};

void Bfme5PushList::bfmePushFront(void *a, void *b)
{
	Bfme5PushNode *q = (Bfme5PushNode *)operator new(16);
	Bfme5PushNode *n;

	if (q) {
		q->m_bfmeVptr = &g_bfmeRva0109FB98Vt;
		q->m_bfmeNext = 0;
		q->m_bfmeA = 0;
		q->m_bfmeB = 0;
		n = q;
	} else {
		n = 0;
	}

	n->m_bfmeNext = m_bfmeHead;
	m_bfmeHead = n;
	n->m_bfmeA = a;
	n->m_bfmeB = b;
	++m_bfmeCount;
}
